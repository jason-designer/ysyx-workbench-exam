#include <common.h>

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();


int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

  /* Start engine. */
  engine_start();

  /* free pointer */
  // free ftrace
  typedef struct{
    char* name;
    uint64_t addr_start;
    uint64_t addr_end;
  }func_info;
  extern func_info* fc;
  extern int func_num;
  for(int i = 0; i < func_num; i++) free(fc[i].name);
  free(fc);
  extern FILE* ftrace_fp;
  fclose(ftrace_fp);
  /* */
  return is_exit_status_bad();
}
