#ifndef __SDB_H__
#define __SDB_H__

#include <common.h>

word_t expr(char *e, bool *success);
void new_wp(char* expr);
void show_watchpoint();
void free_wp(int NO);
bool check_watchpoint();

#endif
