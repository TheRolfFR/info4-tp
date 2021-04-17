#ifndef __SYSTEM_H
#define __SYSTEM_H

extern volatile struct TCB_t * current_tcb;

typedef struct TCB_t {
    volatile uint32_t *stack;
    volatile struct TCB_t * next;
} TCB;

/**
 * @brief Numero SVC pour le changement de tache
 * @warning doit etre != 0
 */
#define TASK_YIELD 1

#define SVC(code) asm volatile ("svc %0" : : "I" (code) )

/**
 * @brief	Save the context of the running task in its stack (the task must
 * 			run on the PSP stack) and update the TCB "stack" field pointed
 * 			by the global variable current_tcb
 */
#define SAVE_CONTEXT()                                                     \
{                                                                          \
    __asm volatile (                                                       \
    /* get PSP */                                                          \
    "mrs r0, psp                @ psp (task stack) in r0          \n\t"    \
    /* test if floating point registers need saving */                     \
    "tst lr,#0x10                @ lr (EXC_RETURN) bit 4 == 0)    \n\t"    \
    "it eq                                                        \n\t"    \
    "vstmdbeq r0!, {s16-s31}                                      \n\t"    \
    "mov r2, lr                    @ lr (EXC_RETURN) in r2        \n\t"    \
    "mrs r3, CONTROL            @ CONTROL in r3                   \n\t"    \
    /* save all non already saved registers    on the task sp (psp) */     \
    "stmdb r0!, {r2-r11}                                          \n\t"    \
    /* get the current_tcb adress                                */        \
    "ldr r1, =current_tcb        @ r1 = &current_tcb              \n\t"    \
    "ldr r2,[r1]                  @ r2 = current_tcb              \n\t"    \
    /* store the new stack adress                                 */       \
    "str r0, [r2]                 @ *current_tcb    = r0 (task sp) \n\t"   \
    );                                                                     \
}

/**
 * @brief	Restore the context of a task. take the context from the
 * 			"stack" field of the TCB pointed by the global variable
 * 			current_tcb
 */

#define RESTORE_CONTEXT()                                                  \
{                                                                          \
    __asm volatile (                                                       \
    /* get the current_tcb adress                                 */       \
    "ldr r1, =current_tcb        @ r1 = &current_tcb              \n\t"    \
    "ldr r2,[r1]                  @ r2 = current_tcb              \n\t"    \
    /* get task stack adress                                      */       \
    "ldr r0, [r2]                @r0 (task sp) = *current_tcb    \n\t"     \
    /* restore non scratch register                                 */     \
    "ldmia r0!, {r2-r11}                                          \n\t"    \
    "mov lr, r2                                                   \n\t"    \
    "msr CONTROL, r3                                              \n\t"    \
    "isb                                                          \n\t"    \
    "tst lr,#0x10                                                 \n\t"    \
    "it eq                                                        \n\t"    \
    "vldmiaeq r0!, {s16-s31}                                      \n\t"    \
    /* restore psp         */                                              \
    "msr psp, r0                                                  \n\t"    \
    );                                                                     \
}    


/* simple save/restore context , no FPU register, no control and no exec_return
   all task in thread mode and same state (privileged or unprivileged) */
#define SAVE_CONTEXT_NO_FPU()                                             \
{                                                                         \
    __asm volatile (                                                      \
    /* get PSP */                                                         \
    "mrs r0, psp                                                 \n\t"    \
    /* save all non already saved registers    on the task sp (psp) */    \
    "stmdb r0!, {r4-r11}                                         \n\t"    \
    /* get the current_tcb adress                                 */      \
    "ldr r1, =current_tcb                                        \n\t"    \
    "ldr r2,[r1]                                                 \n\t"    \
    /* store the new stack adress                               */        \
    "str r0, [r2]                                                \n\t"    \
    );                                                                    \
}    

#define RESTORE_CONTEXT_NO_FPU()                                          \
{                                                                         \
    __asm volatile (                                                      \
    /* get the current_tcb adress                               */        \
    "ldr r1, =current_tcb                                        \n\t"    \
    "ldr r2,[r1]                                                 \n\t"    \
    /* get task stack adress                                    */        \
    "ldr r0, [r2]                                                \n\t"    \
    /* restore non scratch register                             */        \
    "ldmia r0!, {r4-r11}                                         \n\t"    \
    /* restore psp                                 */                     \
    "msr psp, r0                                                 \n\t"    \
    );                                                                    \
}    
#endif /* __SYSTEM_H */

