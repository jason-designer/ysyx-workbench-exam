#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <NDL.h>

// int main(void)
// {
//   struct timeval tv;
//   int sec = 1;
//   while(1){
//     do{
//       gettimeofday(&tv, NULL);
//     }while(tv.tv_sec < sec);
//     printf("sec:%ld  usec:%ld\n", tv.tv_sec, tv.tv_usec);
//     sec++;
//   }
//   return 0;
// }  

int main(void)
{
  NDL_Init(0);
  int sec = 1;
  while(1){
    while(NDL_GetTicks()/1000 < sec);
    printf("sec:%d  msec:%d\n", sec, NDL_GetTicks());
    sec++;
  }
  return 0;
}  
