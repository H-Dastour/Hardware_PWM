#pragma once
/**
  ******************************************************************************
  * @file    Hardware_PWM.hpp
  * @author  H.Dastour
  * @brief   Header file of Hardware_PWM class.
  ******************************************************************************
**/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef Hardware_PWM_HPP
#define Hardware_PWM_HPP

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Macros --------------------------------------------------------------------*/
/* Constants -----------------------------------------------------------------*/

/**
  * @brief  Hardware PWM controller Class. Version 1
  */
namespace Hardware_PWM_Ver1
{
	/* Types ---------------------------------------------------------------------*/
	typedef struct
	{
		bool Channel1;
		bool Channel2;
		bool Channel3;
		bool Channel4;
	}PWM_Channels;

	/* Class ---------------------------------------------------------------------*/
	class Hardware_PWM
	{
	public:
		Hardware_PWM(TIM_HandleTypeDef* _pxTimer, PWM_Channels* _pxUsed_Channels, uint32_t _ulFrequency, bool _xTimerIs32bit);
		~Hardware_PWM(void);

		void Start_PWM(uint8_t _ucChannel, double _DutyCycle);
		void Stop_PWM(uint8_t _ucChannel);
		void Start_All_PWM(double _DutyCycle);
		void Stop_All_PWM(void);
		void Change_DutyCycle(uint8_t _ucChannel, double _DutyCycle);
		void Change_Frequency(uint32_t _ulNewFrequency);


	private:
		TIM_HandleTypeDef* pxTimer;		//This pointer saves the address of timer handle variable
		PWM_Channels* pxUsed_Channels;	//This pointer saves the address of channels status variable
		bool xTimerIs32bit;				//This variable specifies the used timer is 32 bit or 16 bit
		uint64_t ulTimer_Prescaler;		//This variable saves the prescaler value
		uint32_t ulTimer_Period;		//This variable saves the period value

		void Timer_Init(void);
		void Timer_Calculator(uint32_t _ulFrequency);
		uint32_t Timer_Get_Frequency(void);
	};
}

#endif /* Hardware_PWM_HPP */
/*****************************END OF FILE*****************************/