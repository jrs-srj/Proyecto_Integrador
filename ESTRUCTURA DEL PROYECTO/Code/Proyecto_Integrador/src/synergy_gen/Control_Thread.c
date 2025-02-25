/* generated thread source file - do not edit */
#include "Control_Thread.h"

TX_THREAD Control_Thread;
void Control_Thread_create(void);
static void Control_Thread_func(ULONG thread_input);
static uint8_t Control_Thread_stack[1024] BSP_PLACE_IN_SECTION_V2(".stack.Control_Thread") BSP_ALIGN_VARIABLE_V2(BSP_STACK_ALIGNMENT);
void tx_startup_err_callback(void *p_instance, void *p_data);
void tx_startup_common_init(void);
TX_QUEUE control_queue;
static uint8_t queue_memory_control_queue[20];
extern bool g_ssp_common_initialized;
extern uint32_t g_ssp_common_thread_count;
extern TX_SEMAPHORE g_ssp_common_initialized_semaphore;

void Control_Thread_create(void)
{
    /* Increment count so we will know the number of ISDE created threads. */
    g_ssp_common_thread_count++;

    /* Initialize each kernel object. */
    UINT err_control_queue;
    err_control_queue = tx_queue_create (&control_queue, (CHAR *) "CONTROL_QUEUE", 1, &queue_memory_control_queue,
                                         sizeof(queue_memory_control_queue));
    if (TX_SUCCESS != err_control_queue)
    {
        tx_startup_err_callback (&control_queue, 0);
    }

    UINT err;
    err = tx_thread_create (&Control_Thread, (CHAR *) "Control_Thread", Control_Thread_func, (ULONG) NULL,
                            &Control_Thread_stack, 1024, 1, 1, 1, TX_AUTO_START);
    if (TX_SUCCESS != err)
    {
        tx_startup_err_callback (&Control_Thread, 0);
    }
}

static void Control_Thread_func(ULONG thread_input)
{
    /* Not currently using thread_input. */
    SSP_PARAMETER_NOT_USED (thread_input);

    /* Initialize common components */
    tx_startup_common_init ();

    /* Initialize each module instance. */

    /* Enter user code for this thread. */
    Control_Thread_entry ();
}
