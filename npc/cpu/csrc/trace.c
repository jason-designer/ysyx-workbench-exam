#include"trace.h"


CPU_Commit_Info commit_info = {.commit = false, .pc = 0, .inst = 0};
void commit_info_read(unsigned char commit, long long pc, int inst){
    commit_info.commit = commit;
    commit_info.pc = pc;
    commit_info.inst = inst;
}

