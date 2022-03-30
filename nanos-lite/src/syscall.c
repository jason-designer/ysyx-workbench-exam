#include <common.h>
#include <fs.h>
#include "syscall.h"

#include<sys/time.h>
#include<unistd.h>
#include <proc.h>



// int do_sys_write(int fd, char *buf, size_t count){
//   if(fd == 1 || fd == 2) {
//     for(int i=0; i<count; i++) putch(buf[i]);
//     return count;
//   }
//   else return -1;
// }

int do_sys_gettimeofday(struct timeval *ptimeval, void *ptimezone){
  uint64_t us = io_read(AM_TIMER_UPTIME).us;
  ptimeval->tv_sec = us / 1000000;
  ptimeval->tv_usec = us; 
  return 0;
}

void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  uintptr_t ret = 0;

  switch (a[0]) {
    case SYS_exit:  printf("-> SYS_exit happen, exit status = %d \n",a[1]); 
                    halt(0); ret = 0; 
                    break;  
    case SYS_yield: printf("-> SYS_yield happen \n"); 
                    yield(); ret = 0; 
                    break; 
    case SYS_open:  //printf("-> SYS_open happen \n"); 
                    ret = fs_open((const char *)a[1], (int)a[2], (int)a[3]); 
                    break;  
    case SYS_read:  //printf("-> SYS_read happen \n"); 
                    ret = fs_read((int)a[1], (void *)a[2], (size_t)a[3]); 
                    break;
    case SYS_write: //printf("-> SYS_write happen \n"); 
                    ret = fs_write((int)a[1], (char *)a[2], (size_t)a[3]); 
                    break;  
    case SYS_close: //printf("-> SYS_close happen \n"); 
                    ret = fs_close((int)a[1]); 
                    break;
    case SYS_lseek: //printf("-> SYS_lseek happen \n"); 
                    ret = fs_lseek((int)a[1], (size_t)a[2], (int)a[3]); 
                    break;
    case SYS_brk:   //printf("-> SYS_brk happen \n");  
                    ret = 0;
                    break;
    case SYS_execve://printf("-> SYS_execve happen \n"); 
                    naive_uload(NULL, (const char *)a[1]);
                    ret = 0;
                    break;
    case SYS_gettimeofday:   
                    //printf("-> SYS_gettimeofday happen \n");  
                    ret = do_sys_gettimeofday((struct timeval *)a[1], (void *)a[2]);
                    break;
                 
    default:        panic("Unhandled syscall ID = %d", a[0]);
  }
  c->GPRx = ret;
}
