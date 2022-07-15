#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <NDL.h>

// int main(void)
// {
//   NDL_Init(0);
//   while(1){
//     printf("msec:%d\n", NDL_GetTicks());
//   }
//   return 0;
// }  

int main(void)
{
  NDL_Init(0);
  uint64_t pre;

  pre = NDL_GetTicks();
  while(1){
    if(NDL_GetTicks() - pre > 1000) {
      pre = NDL_GetTicks();
      printf("msec:%d\n", pre);
    }
  }
  return 0;
} 
