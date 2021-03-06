/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Library includes. */
#include "stm32f10x.h"

/* application includes. */
#include "keyboard.h"
/*-----------------------------------------------------------*/

/* KB HARDWARE defines. */
#define KEY_SCAN_TIME 		(configTICK_RATE_HZ/100)	//10mS
#define KEY_FILTER  		(configTICK_RATE_HZ/20)/KEY_SCAN_TIME
#define KEY_REPEAT_DELAY	(configTICK_RATE_HZ)/KEY_SCAN_TIME
#define KEY_REPEAT_SPEED	(configTICK_RATE_HZ/20)/KEY_SCAN_TIME
#define KEY_BUF_SIZE		8

#define KEY_PORT	GPIOB
#define KEY_LOAD	GPIO_Pin_5
#define KEY_CLR		GPIO_Pin_6
#define KEY_CLK		GPIO_Pin_7
#define KEY_SO		GPIO_Pin_8
#define KEY_SI		GPIO_Pin_9

#define KEY_OE_PORT	GPIOE
#define KEY_OE		GPIO_Pin_0

/*-----------------------------------------------------------*/
volatile uint16_t LED_Value=0;

/*-----------------------------------------------------------*/

/* The queue used to hold received characters. */
static xQueueHandle xKB_Queue;


/*-----------------------------------------------------------*/

void LED_Set(uint16_t led)
{
	LED_Value = led;
}

/*-----------------------------------------------------------*/

void KB_Delay(uint16_t delay)
{
	volatile uint16_t i;
	for(i=0;i<delay;i++);
}

void KB_PIN_Init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStructure;

	/* Enable GPIOE clock */
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);

	/* Configure pins */
	GPIO_InitStructure.GPIO_Pin 	= KEY_CLR ;
	GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_OD;
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);

	/* Configure pins */
	GPIO_InitStructure.GPIO_Pin 	= KEY_SO | KEY_CLK | KEY_LOAD;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_PP;
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin 	= KEY_SI;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_IPU;
	GPIO_Init(KEY_PORT, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin 	= KEY_OE;
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode 	= GPIO_Mode_Out_OD;
	GPIO_Init(KEY_OE_PORT, &GPIO_InitStructure);

	GPIO_SetBits(KEY_OE_PORT,KEY_OE);
	GPIO_ResetBits(KEY_PORT,KEY_CLR);
	KB_Delay(10);
	GPIO_SetBits(KEY_PORT,KEY_CLR);
	
}


/*-----------------------------------------------------------*/
uint16_t KB_Get_Scancode(void)
{
	uint16_t key=0,i;
		
	GPIO_ResetBits(KEY_OE_PORT,KEY_OE);
	GPIO_ResetBits(KEY_PORT,KEY_CLK);		
	GPIO_ResetBits(KEY_PORT,KEY_CLR);
	KB_Delay(10);
	GPIO_SetBits(KEY_PORT,KEY_CLR);
	KB_Delay(20);
	key <<= 1;
	key |= GPIO_ReadInputDataBit(KEY_PORT,KEY_SI);
		
	for(i=0;i<8;i++){
		GPIO_WriteBit(KEY_PORT,KEY_SO,(BitAction)((LED_Value>>i)&0x01));
		//KB_Delay(100);
		GPIO_ResetBits(KEY_PORT,KEY_CLK);
		KB_Delay(20);
		GPIO_SetBits(KEY_PORT,KEY_CLK);
		KB_Delay(20);
		key <<= 1;
		key |= GPIO_ReadInputDataBit(KEY_PORT,KEY_SI);
	}
	
	GPIO_ResetBits(KEY_PORT,KEY_LOAD);
	KB_Delay(100);
	GPIO_SetBits(KEY_PORT,KEY_LOAD);
	KB_Delay(40);

	if ( (LED_Value>>i) & 0x01 )
		GPIO_ResetBits(KEY_PORT,KEY_CLR);
	else
		GPIO_SetBits(KEY_PORT,KEY_CLR);
			
	if ( GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_2) == DC100V_ON ){
		GPIO_SetBits(GPIOE,GPIO_Pin_6);
		LED_Value |= LED_100V_ON;
	} else {
		GPIO_ResetBits(GPIOE,GPIO_Pin_6);
		LED_Value &= ~LED_100V_ON;
	}

	return (~key & 0x1FF);
}


/*-----------------------------------------------------------*/
unsigned portBASE_TYPE KB_Init(void)
{
	KB_PIN_Init();

	/* Create the queues used to keycode. */
	xKB_Queue = xQueueCreate( KEY_BUF_SIZE, ( portBASE_TYPE ) sizeof( uint16_t ) );
	if ( xKB_Queue == 0 ){
		return pdFALSE;
	}
	return pdTRUE;
}

/*-----------------------------------------------------------*/
void KB_scan(void)
{
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	uint16_t key;
	static uint16_t prev_key=0,break_key=0;
 	static uint8_t  key_count=0,key_filter=KEY_FILTER,key_repeat=0;
	
	unsigned portBASE_TYPE uxSavedInterruptStatus;
																				
	uxSavedInterruptStatus = portSET_INTERRUPT_MASK_FROM_ISR();	
	key = KB_Get_Scancode();
	portCLEAR_INTERRUPT_MASK_FROM_ISR( uxSavedInterruptStatus );														\
	
	if ( key == prev_key ){
		if ( key_count ++ == key_filter ){
			if ( key == 0 ){
				if ( break_key ){
					key = break_key | MSG_KEY_BREAK;
					break_key = 0;
					xQueueSendFromISR( xKB_Queue, &key, &xHigherPriorityTaskWoken );
				} else 
					key_count = 0;
			} else {
				break_key = key;
				xQueueSendFromISR( xKB_Queue, &key, &xHigherPriorityTaskWoken );
				if ( key_repeat )
					key_count = 0;
			}
		} else if (key_count >= KEY_REPEAT_DELAY){
			key_repeat = 1;
			key_count = 0;
			key_filter = KEY_REPEAT_SPEED;
		}
	} else {
		prev_key  = key;
		key_filter = KEY_FILTER;
		key_repeat = 0;
		key_count = 0;
	}
	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}

/*-----------------------------------------------------------*/
void KB_task(void)
{
	if ( (xTaskGetTickCount() % KEY_SCAN_TIME) == 0 ){
		KB_scan();
	}
}

/*-----------------------------------------------------------*/
unsigned portBASE_TYPE KB_Get(uint16_t *pcRxedkey, portTickType xBlockTime )
{
	/* Get the next key from the buffer.  Return false if no key
	are available, or arrive before xBlockTime expires. */
	if( xQueueReceive( xKB_Queue, pcRxedkey, xBlockTime ) )
		return pdTRUE;
	else
		return pdFALSE;
}

#if 0
void vApplicationTickHook(void)
{
	KB_task();
}
#endif

