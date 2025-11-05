/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay.h"
#include "at24c02.h"
#include "key.h"
#include "oled.h"
#include "rc522.h"
#include "rtc.h"
#include "math.h"


#include "adc.h"
#include "dma.h"

#include "rtc.h"
#include "spi.h"
#include "semphr.h"
#include "gpio.h"
#include "queue.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/* START_TASK ?? ??
 * ??: ???? ????? ???? ????
 */
#define START_TASK_PRIO         1
#define START_TASK_STACK_SIZE   128
TaskHandle_t    start_task_handler;
void start_task( void * pvParameters );

/* TASK1 ?? ??
 * ??: ???? ????? ???? ????
 */
#define TASK1_PRIO         2
#define TASK1_STACK_SIZE   128
TaskHandle_t    task1_handler;
void task1( void * pvParameters );

/* TASK2 ?? ??
 * ??: ???? ????? ???? ????
 */
#define TASK2_PRIO         6
#define TASK2_STACK_SIZE   64
TaskHandle_t    task2_handler;
void task2( void * pvParameters );

/* TASK3 ?? ??
 * ??: ???? ????? ???? ????
 */
#define TASK3_PRIO         4
#define TASK3_STACK_SIZE   128
TaskHandle_t    task3_handler;
void task3( void * pvParameters );

#define TASK4_PRIO         4
#define TASK4_STACK_SIZE   64
TaskHandle_t    task4_handler;
void task4( void * pvParameters );

#define TASK5_PRIO         7
#define TASK5_STACK_SIZE   32
TaskHandle_t    task5_handler;
void task5( void * pvParameters );


/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = osPriorityIdle,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
  QueueHandle_t semphore_handle;
/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  semphore_handle = xSemaphoreCreateBinary();
    xTaskCreate((TaskFunction_t         )   start_task,
                (char *                 )   "start_task",
                (configSTACK_DEPTH_TYPE )   START_TASK_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   START_TASK_PRIO,
                (TaskHandle_t *         )   &start_task_handler );
    vTaskStartScheduler();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
	uint8_t rdbuffer[4];
	uint8_t RxBuffer[4];
  uint8_t write_buffer[10];

	uint8_t key;
	uint8_t addr=0;
	uint8_t j=0;
  uint16_t adcx;
  uint8_t card;

  int y1=0;
  int y2=0;
  int day=0;
  int hour=0;
  int minute=0;
  int second=0;
  uint8_t mode=0;
  uint16_t t=5000;

  uint8_t index=0;
  uint16_t adc_time=600;


void start_task( void * pvParameters )
{
    taskENTER_CRITICAL();               /* ????? */
    xTaskCreate((TaskFunction_t         )   task1,
                (char *                 )   "task1",
                (configSTACK_DEPTH_TYPE )   TASK1_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK1_PRIO,
                (TaskHandle_t *         )   &task1_handler );
                
    xTaskCreate((TaskFunction_t         )   task2,
                (char *                 )   "task2",
                (configSTACK_DEPTH_TYPE )   TASK2_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK2_PRIO,
                (TaskHandle_t *         )   &task2_handler );
                
    xTaskCreate((TaskFunction_t         )   task3,
                (char *                 )   "task3",
                (configSTACK_DEPTH_TYPE )   TASK3_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK3_PRIO,
                (TaskHandle_t *         )   &task3_handler );

		
    xTaskCreate((TaskFunction_t         )   task4,
                (char *                 )   "task4",
                (configSTACK_DEPTH_TYPE )   TASK4_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK4_PRIO,
                (TaskHandle_t *         )   &task4_handler );

    xTaskCreate((TaskFunction_t         )   task5,
                (char *                 )   "task5",
                (configSTACK_DEPTH_TYPE )   TASK5_STACK_SIZE,
                (void *                 )   NULL,
                (UBaseType_t            )   TASK5_PRIO,
                (TaskHandle_t *         )   &task5_handler );                
	
   
    vTaskSuspend(task4_handler);       
    vTaskSuspend(task2_handler); 
    vTaskSuspend(task3_handler); 
          
    vTaskDelete(NULL);
    taskEXIT_CRITICAL();                /* ????? */
}

/* ??????LED0?500ms???? */
void task1( void * pvParameters )
{
  // vTaskSuspend(StartDefaultTask);
  
		vTaskSuspend(task3_handler);
    while(1)
    {
    key=key_scan(0);
    if(mode==0)
      {
      index=0;
      OLED_Clear();
      HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
      HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);

      oled_showjiemian();
      // HAL_ADC_Start(&hadc1);

      adcx = adc_get_result();
      HAL_ADC_Start_IT(&hadc1);
      OLED_ShowNum(94,0,adcx*100/4096,2,OLED_8X16);
      OLED_ShowString(112,0,"%",OLED_8X16);
      OLED_ShowString(18,42,"ID",OLED_6X8);
      OLED_ShowNum(32,42,0,8,OLED_6X8);
       card=PCD_Request(PICC_REQALL, RxBuffer);
    PCD_Anticoll(RxBuffer);
    if(card==PCD_OK)
    {
       if(semphore_handle != NULL)
            {
                 xSemaphoreGive(semphore_handle);
            }


    }
	    OLED_Update();
      if(key==KEY1_PRES)
      {
      mode=3;		
      OLED_Clear();
      OLED_ShowString(30,20,"clear",OLED_8X16);
      OLED_Update();
      delay_ms(500);
      vTaskResume(task4_handler);
      }
      if(key==KEY2_PRES)
      {
      mode=1;
      OLED_Clear();
      OLED_ShowString(30,20,"set time?",OLED_8X16);
      OLED_Update();
      vTaskResume(task3_handler);
      }
      if(key==KEY3_PRES)
      {
        mode=2;
        OLED_Clear();
        OLED_ShowString(0,20,"look history?",OLED_8X16);
        OLED_Update();
        vTaskResume(task2_handler);
      } 
      }
	  vTaskDelay(1);
    }

}

/* ??????LED1?500ms???? */
void task2( void * pvParameters )
{
    while(1)
    {
      key=key_scan(0);
      if(mode==2)
      {

      if(key==KEY1_PRES)
      {
      t=5000;
      OLED_Clear();
      OLED_ShowString(30,1,"card ID",OLED_8X16);
      for(int i=0;i<4;i++)
      {
      OLED_ShowHexNum(32+i*18,25,at24c02_read_one_byte(addr+i),2,OLED_6X8);
      }
      OLED_ShowNum(3,40,2000+at24c02_read_one_byte(addr+4),4,OLED_6X8);
      for(int i=0;i<5;i++){
      OLED_ShowNum(29+i*14,40,at24c02_read_one_byte(addr+5+i),2,OLED_6X8);
      }
      OLED_Update();	
      }
      if(key==KEY2_PRES)
      {
      t=5000;
      OLED_ClearArea(0,25,127,33);
      addr=addr+10;

      for(int i=0;i<4;i++)
      {
      OLED_ShowHexNum(32+i*18,25,at24c02_read_one_byte(addr+i),2,OLED_6X8);
      }
      OLED_ShowNum(3,40,2000+at24c02_read_one_byte(addr+4),4,OLED_6X8);
      for(int i=0;i<5;i++){
      OLED_ShowNum(29+i*14,40,at24c02_read_one_byte(addr+5+i),2,OLED_6X8);
      }OLED_Update();

      }
      if(key==KEY3_PRES)
      {
      t=5000;
      OLED_ClearArea(0,25,127,33);
      addr=addr-10;

      for(int i=0;i<4;i++)
      {
      OLED_ShowHexNum(32+i*18,25,at24c02_read_one_byte(addr+i),2,OLED_6X8);
      }
      OLED_ShowNum(3,40,2000+at24c02_read_one_byte(addr+4),4,OLED_6X8);
      for(int i=0;i<5;i++){
      OLED_ShowNum(29+i*14,40,at24c02_read_one_byte(addr+5+i),2,OLED_6X8);
      }OLED_Update();

      }
      if(t!=0){t--;delay_ms(1);}
      else
      {    
        mode=0;
        t=5000;
        vTaskSuspend(task2_handler);
      }
      if(key==KEY4_PRES)
        {		
        mode=0;
        vTaskSuspend(task2_handler);
        }
      }
    }
}

/* ????????KEY0???KEY0??task1 */
void task3( void * pvParameters )
{

  while(1)
  {

  key=key_scan(0);
  if(mode==1)
  {
	if(key==KEY1_PRES)
	{
	t=5000;
	OLED_ShowString(30,0,"set time",OLED_8X16);
	OLED_ClearArea(30,20,127,36);
	  OLED_Update();
	  index++;
	  index=index%7;
	  if(index==1){OLED_ClearArea(0,40,127,63);OLED_ShowString(20,42,"year",OLED_6X8);OLED_Update();}
	  if(index==2){OLED_ClearArea(0,40,127,63);OLED_ShowString(20,42,"month",OLED_6X8);OLED_Update();}
	  if(index==3){OLED_ClearArea(0,40,127,63);OLED_ShowString(20,42,"day",OLED_6X8);OLED_Update();}
	  if(index==4){OLED_ClearArea(0,40,127,63);OLED_ShowString(20,42,"hour",OLED_6X8);OLED_Update();}
	  if(index==5){OLED_ClearArea(0,40,127,63);OLED_ShowString(20,42,"minute",OLED_6X8);OLED_Update();}
	  if(index==6){OLED_ClearArea(0,40,127,63);OLED_ShowString(20,42,"second",OLED_6X8);OLED_Update();}

	  if(index==0)
	  {
	  settime(y1,y2,day,hour,minute,second);
	  mode=0;
    delay_ms(300);
    vTaskSuspend(task3_handler);

	  }


	  }
	if(key==KEY2_PRES)
	  {
	  t=5000;
		if(index==1)
		{
		  y1++;
		  if(y1>99){y1=y1%100;}
		  OLED_ClearArea(0,40,127,63);
		  OLED_ShowString(20,42,"year",OLED_6X8);
		  OLED_ShowNum(48,42,2000 + y1,4,OLED_6X8);
		  OLED_Update();
		}
		if(index==2)
		{      
		  y2++;
		  if(y2>12){y2=y2%13;y2++;}
		  OLED_ClearArea(0,40,127,63);
		  OLED_ShowString(20,42,"month-",OLED_6X8);    
		  OLED_ShowNum(57,42,y2,2,OLED_6X8);  
		  OLED_Update();

		}
		if(index==3)
		{		  
		//   day++;
		  if(rtc_is_leap_year(y1))
		  {
			if(y2==1|y2==3|y2==5|y2==7|y2==8|y2==10|y2==12){day=day%31;day++;}
			else if(y2==4|y2==6|y2==9|y2==11){day=day%30;day++;}
			else{day=day%29;day++;}
		  }
		  else
		  {
			if(y2==1|y2==3|y2==5|y2==7|y2==8|y2==10|y2==12){day=day%31;day++;}
			else if(y2==4|y2==6|y2==9|y2==11){day=day%30;day++;}
			else{day=day%28;day++;}
		  }
		  OLED_ClearArea(0,40,127,63);
		  OLED_ShowString(20,42,"day-",OLED_6X8);    
		  OLED_ShowNum(45,42,day,2,OLED_6X8);  
		  OLED_Update();

		}
		if(index==4)
		{
		  hour++;
		  if(hour>23){hour=hour%24;}
		  OLED_ClearArea(0,40,127,63);
		  OLED_ShowString(20,42,"hour-",OLED_6X8);    
		  OLED_ShowNum(51,42,hour,2,OLED_6X8);  
		  OLED_Update();

		}
		if(index==5)
		{
		  minute++;
		  if(minute>59){minute=minute%60;}
		  OLED_ClearArea(0,40,127,63);
		  OLED_ShowString(20,42,"minute-",OLED_6X8);    
		  OLED_ShowNum(63,42,minute,2,OLED_6X8);  
		  OLED_Update();
		  
		}
		if(index==6)
		{
		  second++;
		  if(second>59){second=second%60;}
		  OLED_ClearArea(0,40,127,63);
		  OLED_ShowString(20,42,"second-",OLED_6X8);    
		  OLED_ShowNum(63,42,second,2,OLED_6X8);  
		  OLED_Update();

		}
		
	  }
	if(key==KEY3_PRES)
	  {
	  t=5000;
		if(index==1)
		{
		  if(y1>99){y1=y1%100;}		  
		  else if (y1==0){y1=99;}
		  else {y1--;}

		  OLED_ClearArea(0,40,127,63);
		  OLED_ShowString(20,42,"year",OLED_6X8);
		  OLED_ShowNum(48,42,2000 + y1,4,OLED_6X8);
		  OLED_Update();
		}
		if(index==2)
		{      
		  if(y2>12){y2=y2%13;y2++;}		  
		  else if(y2==1){y2=12;}
		  else {y2--;}

		  OLED_ClearArea(0,40,127,63);
		  OLED_ShowString(20,42,"month-",OLED_6X8);    
		  OLED_ShowNum(57,42,y2,2,OLED_6X8);  
		  OLED_Update();

		}
		if(index==3)
		{		  
		  day--;
		  if(rtc_is_leap_year(y1))
		  {
			if(y2==1|y2==3|y2==5|y2==7|y2==8|y2==10|y2==12){if(day==0){day=31;}}
			else if(y2==4|y2==6|y2==9|y2==11){if(day==0){day=30;}}
			else{if(day==0){day=29;}}
		  }
		  else
		  {
			if(y2==1|y2==3|y2==5|y2==7|y2==8|y2==10|y2==12){if(day==0){day=31;}}
			else if(y2==4|y2==6|y2==9|y2==11){if(day==0){day=30;}}
			else{if(day==0){day=28;}}
		  }
		  OLED_ClearArea(0,40,127,63);
		  OLED_ShowString(20,42,"day-",OLED_6X8);    
		  OLED_ShowNum(45,42,day,2,OLED_6X8);  
		  OLED_Update();

		}
		if(index==4)
		{		  
		if(hour>23){hour=hour%24;}
		  else if(hour==0){hour=23;}
		  else{hour--;}
		  OLED_ClearArea(0,40,127,63);
		  OLED_ShowString(20,42,"hour-",OLED_6X8);    
		  OLED_ShowNum(51,42,hour,2,OLED_6X8);  
		  OLED_Update();

		}
		if(index==5)
		{
		  if(minute>59){minute=minute%60;}
		  else if(minute==0){minute=59;}
		  else{minute--;}
		  OLED_ClearArea(0,40,127,63);
		  OLED_ShowString(20,42,"minute-",OLED_6X8);    
		  OLED_ShowNum(63,42,minute,2,OLED_6X8);  
		  OLED_Update();
		  
		}
		if(index==6)
		{
		if(second>59){second=second%60;}
		  else if(second==0){second=59;}
		  else{second--;}
		  
		  OLED_ClearArea(0,40,127,63);
		  OLED_ShowString(20,42,"second-",OLED_6X8);    
		  OLED_ShowNum(63,42,second,2,OLED_6X8);  
		  OLED_Update();

		}
		
	  }
	  if(t!=0){	t--;delay_ms(1);}
	  else 
    {
    mode=0;
    t=5000;
    vTaskSuspend(task3_handler);
    }
    if(key==KEY4_PRES)
    {
      mode=0;
      vTaskSuspend(task3_handler);
    }
  }
      
 }
}


void task4( void * pvparameters)
{
t=5000;
  while(1)
  {
    key=key_scan(0);
     if(mode==3)
  {
  if(key==KEY1_PRES)
  {
    OLED_Clear();
    OLED_ShowString(20,20,"key2or3",OLED_6X8);
    OLED_Update();

  }
	if(HAL_GPIO_ReadPin(KEY2_GPIO_PORT,KEY2_GPIO_PIN)==0|
	HAL_GPIO_ReadPin(KEY3_GPIO_PORT,KEY3_GPIO_PIN)==0)
	{	
		for(int i=0;i<256;i++)
		{at24c02_write_one_byte(i,0);delay_us(5);}	
		OLED_Clear();
		OLED_ShowString(30,20,"done",OLED_8X16);
		OLED_Update();
		
	}
   if(t!=0){t--;delay_ms(1);}
	  else
    {
    mode=0;
    t=5000;
    vTaskSuspend(task4_handler);
    }
  if(key==KEY4_PRES)
    {
      mode=0;
      vTaskSuspend(task4_handler);
    }
  }
  }
}


void task5( void * pvParameters )
{

    BaseType_t err;
    while(1)
    {
      err = xSemaphoreTake(semphore_handle,portMAX_DELAY); /* 获取信号量并死等 */
      if(err == pdTRUE)
      {
          OLED_ClearArea(31,42,127,50);
          for(int i=0;i<4;i++)
          {
          OLED_ShowHexNum(32+i*12,42,RxBuffer[i],2,OLED_6X8);
          }
          OLED_Update();
          if(check(RxBuffer)){HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);}
          
          for(uint8_t i=0;i<4;i++)
          {
          write_buffer[i]=RxBuffer[i];
          }
          write_buffer[4]=Date.Year;
          write_buffer[5]=Date.Month;
          write_buffer[6]=Date.Date;
          write_buffer[7]=sTime.Hours;
          write_buffer[8]=sTime.Minutes;
          write_buffer[9]=sTime.Seconds;
          addr=at24c02_write_ten_byte(j,write_buffer);
          j=j+10;
          if(j>249){j=0;}
          OLED_Update();
		  delay_ms(500);
		  vTaskDelay(30);
          HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
      }
        
    }

}

/* USER CODE END Application */


