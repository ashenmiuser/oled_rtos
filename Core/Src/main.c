/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
#include "main.h"
#include "cmsis_os.h"
#include "adc.h"
#include "dma.h"
#include "rtc.h"
#include "spi.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "delay.h"
#include "at24c02.h"
#include "key.h"
#include "oled.h"
#include "rc522.h"
#include "rtc.h"
#include "math.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void MX_FREERTOS_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_SPI1_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
	HAL_Delay_Init();
	iic_init();
	key_init();
	OLED_Init();
	rc522_GPIO_Init();
	MFRC_Init();//初始化
	PCD_Reset();//器件复位
	
	settime (1,2,3,8,9,10);
	

  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* Call init function for freertos objects (in cmsis_os2.c) */
  MX_FREERTOS_Init();

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

//   key=key_scan (0);

//   if(HAL_GPIO_ReadPin(KEY4_GPIO_PORT,KEY4_GPIO_PIN)==0){mode=0;}
//   if(mode==0)
//   {
// 	index=0;
	
//     OLED_Clear();
//     HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
//     HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);

// 	oled_showjiemian();
// 	// HAL_ADC_Start(&hadc1);
	
//    	adcx = adc_get_result();
// 	HAL_ADC_Start_IT(&hadc1);
// 	OLED_ShowNum(94,0,adcx*100/4096,2,OLED_8X16);
// 	OLED_ShowString(112,0,"%",OLED_8X16);
// 	OLED_ShowString(18,42,"ID",OLED_6X8);
// 	OLED_ShowNum(32,42,0,8,OLED_6X8);
// 	card=PCD_Request(PICC_REQALL, RxBuffer);
// 	PCD_Anticoll(RxBuffer);
// 	if(card==PCD_OK)
// 	{
		
// 		OLED_ClearArea(31,42,127,50);
// 		for(int i=0;i<4;i++)
// 		{
// 			OLED_ShowHexNum(32+i*12,42,RxBuffer[i],2,OLED_6X8);
// 		}
// 		OLED_Update();
// 		if(check(RxBuffer)){HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);}
// 		delay_ms(900);
// 		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
// 		for(uint8_t i=0;i<4;i++)
// 		{
// 			at24c02_write_one_byte(i+j,RxBuffer[i]);	
// 		}
// 		addr=j;
// 		j=j+4;
// 		if(j>255){j=j%256;}
// 	}
// 	OLED_Update();
// 	if(HAL_GPIO_ReadPin(KEY1_GPIO_PORT,KEY1_GPIO_PIN)==0)
// 	{
// 		mode=3;		
// 		OLED_Clear();
// 		OLED_ShowString(30,20,"clear",OLED_8X16);
// 		OLED_Update();
// 	}
//     if(HAL_GPIO_ReadPin(KEY2_GPIO_PORT,KEY2_GPIO_PIN)==0)
// 	{
// 		mode=1;
// 		OLED_Clear();
// 		OLED_ShowString(30,20,"set time?",OLED_8X16);
// 		OLED_Update();
// 		delay_ms(300);
// 	}
// 	if(HAL_GPIO_ReadPin(KEY3_GPIO_PORT,KEY3_GPIO_PIN)==0)
// 	{
// 		mode=2;
// 		OLED_Clear();
// 		OLED_ShowString(0,20,"look history?",OLED_8X16);
// 		OLED_Update();
// 		delay_ms(300);
// 	}
// 	// if(ty==0){adc_time--;}
// 	// if(adc_time==0){HAL_ADC_Start_IT(&hadc1);adc_time=6000;}
//   }
//   if(mode==1)
//   {
// 	if(key==KEY1_PRES)
// 	{
// 	t=5000;
// 	OLED_ShowString(30,0,"set time",OLED_8X16);
// 	OLED_ClearArea(30,20,127,36);
// 	  OLED_Update();
// 	  index++;
// 	  index=index%7;
// 	  if(index==1){OLED_ClearArea(0,40,127,63);OLED_ShowString(20,42,"year",OLED_6X8);OLED_Update();}
// 	  if(index==2){OLED_ClearArea(0,40,127,63);OLED_ShowString(20,42,"month",OLED_6X8);OLED_Update();}
// 	  if(index==3){OLED_ClearArea(0,40,127,63);OLED_ShowString(20,42,"day",OLED_6X8);OLED_Update();}
// 	  if(index==4){OLED_ClearArea(0,40,127,63);OLED_ShowString(20,42,"hour",OLED_6X8);OLED_Update();}
// 	  if(index==5){OLED_ClearArea(0,40,127,63);OLED_ShowString(20,42,"minute",OLED_6X8);OLED_Update();}
// 	  if(index==6){OLED_ClearArea(0,40,127,63);OLED_ShowString(20,42,"second",OLED_6X8);OLED_Update();}

// 	  if(index==0)
// 	  {
// 	  settime(y1,y2,day,hour,minute,second);
// 	  mode=0;
// 	  delay_ms(200);
// 	  }


// 	  }
// 	if(key==KEY2_PRES)
// 	  {
// 	  t=5000;
// 		if(index==1)
// 		{
// 		  y1++;
// 		  if(y1>99){y1=y1%100;}
// 		  OLED_ClearArea(0,40,127,63);
// 		  OLED_ShowString(20,42,"year",OLED_6X8);
// 		  OLED_ShowNum(48,42,2000 + y1,4,OLED_6X8);
// 		  OLED_Update();
// 		}
// 		if(index==2)
// 		{      
// 		  y2++;
// 		  if(y2>12){y2=y2%13;y2++;}
// 		  OLED_ClearArea(0,40,127,63);
// 		  OLED_ShowString(20,42,"month-",OLED_6X8);    
// 		  OLED_ShowNum(57,42,y2,2,OLED_6X8);  
// 		  OLED_Update();

// 		}
// 		if(index==3)
// 		{		  
// 		//   day++;
// 		  if(rtc_is_leap_year(y1))
// 		  {
// 			if(y2==1|y2==3|y2==5|y2==7|y2==8|y2==10|y2==12){day=day%31;day++;}
// 			else if(y2==4|y2==6|y2==9|y2==11){day=day%30;day++;}
// 			else{day=day%29;day++;}
// 		  }
// 		  else
// 		  {
// 			if(y2==1|y2==3|y2==5|y2==7|y2==8|y2==10|y2==12){day=day%31;day++;}
// 			else if(y2==4|y2==6|y2==9|y2==11){day=day%30;day++;}
// 			else{day=day%28;day++;}
// 		  }
// 		  OLED_ClearArea(0,40,127,63);
// 		  OLED_ShowString(20,42,"day-",OLED_6X8);    
// 		  OLED_ShowNum(45,42,day,2,OLED_6X8);  
// 		  OLED_Update();

// 		}
// 		if(index==4)
// 		{
// 		  hour++;
// 		  if(hour>23){hour=hour%24;}
// 		  OLED_ClearArea(0,40,127,63);
// 		  OLED_ShowString(20,42,"hour-",OLED_6X8);    
// 		  OLED_ShowNum(51,42,hour,2,OLED_6X8);  
// 		  OLED_Update();

// 		}
// 		if(index==5)
// 		{
// 		  minute++;
// 		  if(minute>59){minute=minute%60;}
// 		  OLED_ClearArea(0,40,127,63);
// 		  OLED_ShowString(20,42,"minute-",OLED_6X8);    
// 		  OLED_ShowNum(63,42,minute,2,OLED_6X8);  
// 		  OLED_Update();
		  
// 		}
// 		if(index==6)
// 		{
// 		  second++;
// 		  if(second>59){second=second%60;}
// 		  OLED_ClearArea(0,40,127,63);
// 		  OLED_ShowString(20,42,"second-",OLED_6X8);    
// 		  OLED_ShowNum(63,42,second,2,OLED_6X8);  
// 		  OLED_Update();

// 		}
		
// 	  }
// 	if(key==KEY3_PRES)
// 	  {
// 	  t=5000;
// 		if(index==1)
// 		{
// 		  if(y1>99){y1=y1%100;}		  
// 		  else if (y1==0){y1=99;}
// 		  else {y1--;}

// 		  OLED_ClearArea(0,40,127,63);
// 		  OLED_ShowString(20,42,"year",OLED_6X8);
// 		  OLED_ShowNum(48,42,2000 + y1,4,OLED_6X8);
// 		  OLED_Update();
// 		}
// 		if(index==2)
// 		{      
// 		  if(y2>12){y2=y2%13;y2++;}		  
// 		  else if(y2==1){y2=12;}
// 		  else {y2--;}

// 		  OLED_ClearArea(0,40,127,63);
// 		  OLED_ShowString(20,42,"month-",OLED_6X8);    
// 		  OLED_ShowNum(57,42,y2,2,OLED_6X8);  
// 		  OLED_Update();

// 		}
// 		if(index==3)
// 		{		  
// 		  day--;
// 		  if(rtc_is_leap_year(y1))
// 		  {
// 			if(y2==1|y2==3|y2==5|y2==7|y2==8|y2==10|y2==12){if(day==0){day=31;}}
// 			else if(y2==4|y2==6|y2==9|y2==11){if(day==0){day=30;}}
// 			else{if(day==0){day=29;}}
// 		  }
// 		  else
// 		  {
// 			if(y2==1|y2==3|y2==5|y2==7|y2==8|y2==10|y2==12){if(day==0){day=31;}}
// 			else if(y2==4|y2==6|y2==9|y2==11){if(day==0){day=30;}}
// 			else{if(day==0){day=28;}}
// 		  }
// 		  OLED_ClearArea(0,40,127,63);
// 		  OLED_ShowString(20,42,"day-",OLED_6X8);    
// 		  OLED_ShowNum(45,42,day,2,OLED_6X8);  
// 		  OLED_Update();

// 		}
// 		if(index==4)
// 		{		  
// 		if(hour>23){hour=hour%24;}
// 		  else if(hour==0){hour=23;}
// 		  else{hour--;}
// 		  OLED_ClearArea(0,40,127,63);
// 		  OLED_ShowString(20,42,"hour-",OLED_6X8);    
// 		  OLED_ShowNum(51,42,hour,2,OLED_6X8);  
// 		  OLED_Update();

// 		}
// 		if(index==5)
// 		{
// 		  if(minute>59){minute=minute%60;}
// 		  else if(minute==0){minute=59;}
// 		  else{minute--;}
// 		  OLED_ClearArea(0,40,127,63);
// 		  OLED_ShowString(20,42,"minute-",OLED_6X8);    
// 		  OLED_ShowNum(63,42,minute,2,OLED_6X8);  
// 		  OLED_Update();
		  
// 		}
// 		if(index==6)
// 		{
// 		if(second>59){second=second%60;}
// 		  else if(second==0){second=59;}
// 		  else{second--;}
		  
// 		  OLED_ClearArea(0,40,127,63);
// 		  OLED_ShowString(20,42,"second-",OLED_6X8);    
// 		  OLED_ShowNum(63,42,second,2,OLED_6X8);  
// 		  OLED_Update();

// 		}
		
// 	  }
// 	  if(t!=0){	t--;delay_ms(1);}
// 	  else {mode=0;index=0;t=5000;}
	
//   }
//   if(mode==2)
//   {

// 	if(key==KEY1_PRES)
// 	{
// 		t=5000;
// 		OLED_Clear();
// 		OLED_ShowString(30,1,"card ID",OLED_8X16);
// 		for(int i=0;i<4;i++)
// 		{
// 		rdbuffer[i]=at24c02_read_one_byte(addr+i);
// 		}
// 		for(int i=0;i<4;i++)
// 		{
// 		OLED_ShowHexNum(32+i*18,25,rdbuffer[i],2,OLED_6X8);
// 		}
// 		OLED_Update();	
// 	}
// 	if(key==KEY2_PRES)
// 	{
// 		t=5000;
// 		OLED_ClearArea(0,25,127,33);
// 		addr=addr+4;

// 		for(int i=0;i<4;i++)
// 		{
// 		rdbuffer[i]=at24c02_read_one_byte(addr+i);
// 		}
// 		for(int i=0;i<4;i++)
// 		{
// 		OLED_ShowHexNum(32+i*18,25,rdbuffer[i],2,OLED_6X8);
// 		}OLED_Update();

// 	}
// 	if(key==KEY3_PRES)
// 	{
// 		t=5000;
// 		OLED_ClearArea(0,25,127,33);
// 		addr=addr-4;

// 		for(int i=0;i<4;i++)
// 		{
// 		rdbuffer[i]=at24c02_read_one_byte(addr+i);
// 		}
// 		for(int i=0;i<4;i++)
// 		{
// 		OLED_ShowHexNum(32+i*18,25,rdbuffer[i],2,OLED_6X8);
// 		}OLED_Update();

// 	}
// 	if(t!=0){t--;delay_ms(1);}
// 	else{mode=0;t=5000;}
//   }
//   if(mode==3)
//   {

// 	if(HAL_GPIO_ReadPin(KEY2_GPIO_PORT,KEY2_GPIO_PIN)==0&
// 	HAL_GPIO_ReadPin(KEY3_GPIO_PORT,KEY3_GPIO_PIN)==0)
// 	{	
		
// 		for(int i=0;i<256;i++)
// 		{at24c02_write_one_byte(i,0);delay_ms(5);}
// 		mode=0;		
// 		OLED_Clear();
// 		OLED_ShowString(30,20,"done",OLED_8X16);
// 		OLED_Update();
// 		delay_ms(3000);
// 	}
//   }



	
  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

uint8_t check(uint8_t* mima)
{
	int8_t temp=0;
	uint8_t code[4]={0x33,0x64,0x14,0x2A};
	for(int i=0;i<4;i++)
	{
	if(code[i]==*(mima+i))
	{
		temp++;
	}
	}
	if(temp==4)
	{return 1;}
	else 
	{return 0;}
}
/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM4 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM4) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
