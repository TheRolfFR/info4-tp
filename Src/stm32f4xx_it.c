/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"   
#include "system.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

// System Handler Control and State Register here for debug purpose
#define SYSHND_CTRL (*(volatile unsigned int*)  (0xE000ED24u))
// Memory Management Fault Status Register
#define NVIC_MFSR   (*(volatile unsigned char*) (0xE000ED28u))
// Bus Fault Status Register
#define NVIC_BFSR   (*(volatile unsigned char*) (0xE000ED29u))
// Usage Fault Status Register
#define NVIC_UFSR   (*(volatile unsigned short*)(0xE000ED2Au))
// Hard Fault Status Register
#define NVIC_HFSR   (*(volatile unsigned int*)  (0xE000ED2Cu))
// Debug Fault Status Register
#define NVIC_DFSR   (*(volatile unsigned int*)  (0xE000ED30u))
// Bus Fault Manage Address Register
#define NVIC_BFAR   (*(volatile unsigned int*)  (0xE000ED38u))
// Auxiliary Fault Status Register
#define NVIC_AFSR   (*(volatile unsigned int*)  (0xE000ED3Cu))

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint32_t scheduler = 0;
volatile struct TCB_t * current_tcb;
/* Private function prototypes -----------------------------------------------*/
void SVC_C (uint32_t * stack, uint32_t svc_number);
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
	// for debug purpose
	uint32_t x,y,z;
	x = SCB->HFSR;
	y = SCB->CFSR;
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
	// for debug purpose
	uint32_t x;
	x = SCB->CFSR;

  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
	uint32_t x;
	x = SCB->CFSR;
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
	// for debug purpose
	uint32_t x;
	x = SCB->CFSR;
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}


/**
  * @brief  This function handles SVCall exception. It get the SVC number
  * 		and call SVC_C with the stack address and the SVC number in
  * 		r0 and r1
  * 		declared naked to avoid
  * 		entry and exit code added by the compiler (push some registers
  * 		on the stack, and restore them, return to the caller, ...).
  * 		note :  C code should not be used in a naked function
  * 		        as its behavior is unpredictable
  * @param  None
  * @retval None
  */
__attribute__( ( naked ) ) void SVC_Handler(void)
{
__asm volatile(
    /* get argument of svc */
	"tst lr,#4	@test bit 2 of EXC_RETURN to get the stack                \n\t"
	"ite eq \n\t"
	"mrseq r0, msp 	@ if 0, the stack is msp                               \n\t"
	"mrsne r0, psp  @ if 1, the stack is psp                               \n\t"
	"ldr r1, [r0, #24] @get the return address (instruction after the svc) \n\t"
	"ldrb r1, [r1, #-2] @ first byte of the SVC instruction = svc number   \n\t"
 	/* r0 is the stack frame address, r1 is the SVC number	*/
	/* a C function can be called with this parameters with a simple b */
	/* b SVC_C with SVC_C (uint32_t * stack, uint32_t svc_number) */
	"cmp r1,#0															   \n\t"
	"it ne																   \n\t"
	"bne SVC_C @call service if not 0, return from interrupt done in SVC_C \n\t"
    /* 0 : start scheduler and restore context  */
    "ldr r0, =scheduler    @ get sheduler variable address                 \n\t"
    "mov r1,#1                                                             \n\t"
    "str r1,[r0]    /*set sheduler variable to 1 */                        \n\t"
    );
    /* restore context */
	RESTORE_CONTEXT();
    /* return from interrupt in PSP mode */
    __asm volatile(
        "bx lr                                                             \n\t"
 	);
}

/**
  * @brief  This function is called by SVC_Handler, declared naked to avoid
  * 		entry and exit code added by the compiler (push some registers
  * 		on the stack and restore them ...).
  * 		note :  C code should not be used as its behavior is unpredictable
  * 		but should work as it is really simple code
  * @param  pointer to the task stack
  * @param  SVC number
  * @retval None
  */
void SVC_C (uint32_t * stack, uint32_t svc_number)
{
	switch(svc_number){
		case 0 :	// start scheduler, already implemented in SVC_Handler
			/* what is done in SVC_Handler is : set the global variable
			 * scheduler to enable task switching and
			 * restore the context of the first task to start :
			 */
//			scheduler = 1;
//			RESTORE_CONTEXT();
			break;
		// other service number can be implemented in here :
		case 1 :
			break;
		case 2 :
			break;
		default :
			break;
	}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  *
  * 		if a contexte switch is requested (global variable sheduler set),
  * 		it save the context of the running task in its own stack, change
  * 		the TCB and restore the new task
  *
  * 		declared with attribute "naked" to avoid entry and exit code added
  * 		by the compiler. naked function should not used C code as its
  * 		behavior is unpredictable
  * @param  None
  * @retval None
  */
__attribute__( ( naked ) ) void PendSV_Handler(void)
{
	/* test if a context switch must be done
	 * if (scheduler == 0)
	 * 		return;
	 */
	__asm volatile(
		"ldr r0, =scheduler    @ get scheduler variable address        \n\t"
		"ldr r1, [r0]          @ get scheduler value (in r1)           \n\t"
		"cmp r1, #1            @ comp scheduler variable to 1          \n\t"
		"it ne                 @ if not equal                          \n\t"
		"bxne lr               @ return from exception                 \n\t"
	);

	/* Save the context of the current task in its stack and update SP */
	SAVE_CONTEXT();

/* ASM equivalent to the following C instructions :
	if (scheduler == 1)
		current_tcb = current_tcb->next;

	__asm volatile(
		"ldr r0, =scheduler    @ get scheduler variable address        \n\t"
		"ldr r1, [r0]          @ get scheduler value (in r1)           \n\t"
		"cmp r1, #1            @ comp scheduler variable to 1          \n\t"
		"itttt eq                                                      \n\t"
		"ldreq r3, =current_tcb  @ r3 <- &current_tcb                  \n\t"
		"ldreq r1, [r3]          @ r1 <- current_tcb                   \n\t"
		"ldreq r2, [r1,#4]       @ r2 <- current_tcb->next             \n\t"
		"streq r2, [r3]          @ current_tcb <- r2                   \n\t"
	);
*/
	__asm volatile(
		"ldr r3, =current_tcb  @ r3 <- &current_tcb                  \n\t"
		"ldr r1, [r3]          @ r1 <- current_tcb                   \n\t"
		"ldr r2, [r1,#4]       @ r2 <- current_tcb->next             \n\t"
		"str r2, [r3]          @ current_tcb <- r2                   \n\t"
	);

	/* restore context */
	RESTORE_CONTEXT();

	/* return from exception (it is a "naked function, it must be done
	 * explicitely with bx lr"
	 */
	__asm volatile("bx lr \n\t");
}


void SysTick_Handler(void)
{

}

