#include <am.h>
#include <klib.h>

static Context* (*user_handler)(Event, Context*) = NULL;

Context* __am_irq_handle(Context *c) {
  if (user_handler) {
    Event ev = {0};
    // printf("--------------%p-----%d\n",c->mcause ,c->GPR1);
    switch (c->mcause) {
      // 先根据mcause判断是指令中断还是时钟中断，再用a7来判断哪种调用
      // 这里还要考虑哪些异常要给mepc加4
      case 0xb: switch(c->GPR1){ 
                  case 0 ... 19: ev.event = EVENT_SYSCALL; c->mepc +=4; break;
                  case -1: ev.event = EVENT_YIELD; c->mepc += 4; break;
                }
                break;
      default: ev.event = EVENT_ERROR; break;
    }
    c = user_handler(ev, c);
    assert(c != NULL);
  }

  return c;
}

extern void __am_asm_trap(void);

bool cte_init(Context*(*handler)(Event, Context*)) {
  // initialize exception entry
  asm volatile("csrw mtvec, %0" : : "r"(__am_asm_trap));

  // register event handler
  user_handler = handler;

  return true;
}

Context *kcontext(Area kstack, void (*entry)(void *), void *arg) {
  return NULL;
}

void yield() {
  asm volatile("li a7, -1; ecall");
}

bool ienabled() {
  return false;
}

void iset(bool enable) {
}
