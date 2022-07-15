#include <fs.h>

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);

typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  ReadFn read;
  WriteFn write;
  size_t open_offset;
} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_FB, FD_FBINFO, FD_KB};

size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  [FD_STDIN]  = {"stdin", 0, 0, invalid_read, invalid_write},
  [FD_STDOUT] = {"stdout", 0, 0, invalid_read, serial_write},
  [FD_STDERR] = {"stderr", 0, 0, invalid_read, serial_write},
  [FD_FB]     = {"/dev/fb", 0, 0, invalid_read, fb_write},
  [FD_FBINFO] = {"/proc/dispinfo", 0, 0, dispinfo_read, invalid_write},
  [FD_KB]     = {"/dev/events", 0, 0, events_read, invalid_write},
#include "files.h"
};

void init_fs() {
  // TODO: initialize the size of /dev/fb
  int file_number = sizeof(file_table) /sizeof(file_table[0]);
  for(int i = 0; i < file_number; i++){
    file_table[i].open_offset = 0;
  }
}

int fs_open(const char *pathname, int flags, int mode){
  int i, file_number;
  file_number = sizeof(file_table) /sizeof(file_table[0]);
  //Logm("file total num = %d  --------------", file_number);
  for(i = 0; i < file_number; i++){
    if(strcmp(pathname, file_table[i].name) == 0) break;
  }
  if(i >= file_number){
    printf("can't find %s\n",pathname);
    assert(i < file_number);
  }
  //Logm("fs_open fail, can't find this file !");
  //if(i < file_number) return -1;
  file_table[i].open_offset = 0;
  //Logm("open num = %d  --------------", i);
  return i;
}

size_t fs_read(int fd, void *buf, size_t len){
  if(file_table[fd].read == NULL){
    if(file_table[fd].open_offset < 0){
      Logm("fs_read open_offset out of bound!fd=%d, name=%s, len=%d, open_offset=%d",fd,file_table[fd].name,len,file_table[fd].open_offset);
      assert(0);//为处理open_offset < 0的情况
    }
    if(file_table[fd].open_offset >= file_table[fd].size){
      return 0;
    }
    if(file_table[fd].open_offset + len <= file_table[fd].size){    // 没有超过文件大小
      size_t res = ramdisk_read(buf, file_table[fd].open_offset + file_table[fd].disk_offset, len);
      file_table[fd].open_offset += res;
      return res;
    }
    else{                                                           // 超过文件大小
      size_t offset = file_table[fd].open_offset + file_table[fd].disk_offset;
      size_t length = file_table[fd].size - file_table[fd].open_offset;
      size_t res = ramdisk_read(buf, offset, length);
      file_table[fd].open_offset += res;
      return res;
    }
  }
  else{
    return file_table[fd].read(buf, file_table[fd].open_offset, len);
  }
}

size_t fs_write(int fd, const void *buf, size_t len){
  if(file_table[fd].write == NULL){   //普通文件
    if(file_table[fd].open_offset < 0 || file_table[fd].open_offset >= file_table[fd].size){
      //Logm("fs_write open_offset out of bound!fd=%d, len=%d, open_offset=%d",fd,len,file_table[fd].open_offset);
      assert(0);
    }
    size_t res = ramdisk_write(buf, file_table[fd].open_offset + file_table[fd].disk_offset, len);
    file_table[fd].open_offset += len;
    return res;
  }
  else{
    return file_table[fd].write(buf, file_table[fd].open_offset, len); //串口忽略offset
  }
}

size_t fs_lseek(int fd, size_t offset, int whence){
  //size_t pre_open_offset = file_table[fd].open_offset;
  if(fd == FD_STDIN || fd == FD_STDOUT || fd == FD_STDERR) assert(0);
  switch(whence){
    case SEEK_SET: file_table[fd].open_offset =  offset; break;
    case SEEK_CUR: file_table[fd].open_offset += offset; break;
    case SEEK_END: file_table[fd].open_offset =  file_table[fd].size + offset; break;
  }
  //Logm("fd = %d, offset = %d, whence = %d, pre open_offset = %d, next open_offset = %d\n", fd, offset, whence, pre_open_offset, file_table[fd].open_offset);
  // if(file_table[fd].open_offset < 0 || file_table[fd].open_offset > file_table[fd].size){
  //   Logm("fs_lseek open_offset out of bound!");
  //   Logm("fd = %d, offset = %d, whence = %d, open_offset = %d\n", fd, offset, whence, file_table[fd].open_offset);
  //   assert(0);
  // }
  return file_table[fd].open_offset;
}

int fs_close(int fd){
  //if(fd == FD_STDIN || fd == FD_STDOUT || fd == FD_STDERR) assert(0);
  file_table[fd].open_offset = 0;
  return 0;
}

