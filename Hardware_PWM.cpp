/**
  ******************************************************************************
  * @file    Hardware_PWM.cpp
  * @author  Hadi Dastour
  *	@version 1.0.0	
  * @brief   Hardware PWM controller class.
  *          This file provides firmware functions to manage a hardware PWM
  *          of a Timer.
  * @support Email: Hadi.Dastoor@gmail.com		
  *			 Github: https://github.com/H-Dastour
  ******************************************************************************
**/

/* Includes ------------------------------------------------------------------*/
#include "Hardware_PWM.hpp"

/**
  * @brief  Hardware PWM controller Class. Version 1
  */
namespace Hardware_PWM_Ver1
{
	/* Variables -----------------------------------------------------------------*/
	/* Functions Definitions -----------------------------------------------------*/
	/**
	  * @brief  Constructor function
	  * @param  _pxTimer: The address of timer handle variable
	  *			_pxUsed_Channels: The address of PWM channel status variable
	  *			_pxTimerSpecs_Data: All timer specifications. Frequency according to Hz
	  *														  DeadTime value according to nS
	  * @retval None
	  */
	Hardware_PWM::Hardware_PWM(TIM_HandleTypeDef* _pxTimer, PWM_Channels* _pxUsed_Channels, TimerSpecs_Type* _pxTimerSpecs_Data)
	{
		/****************************** Initial Values ******************************/
		this->pxTimer = _pxTimer;
		this->pxUsed_Channels = _pxUsed_Channels;
		this->pxTimerSpecs_Data = _pxTimerSpecs_Data;
		this->ulTimer_Prescaler = 0;
		this->ulTimer_Period = 0;

		this->Timer_Calculator(this->pxTimerSpecs_Data->_ulFrequency);
		this->Timer_Init();
		this->Stop_All_PWM();
	}

	/**
	  * @brief  Destructor Function
	  * @param  None
	  * @retval None
	  */
	Hardware_PWM::~Hardware_PWM(void)
	{

	}

	/**
	  * @brief  This function Starts PWM signal 
	  * @param  _ucChannel: The channel number of timer. It can be TIM_CHANNEL_1,2,3,4
	  *			DutyCycle: Dutycycle value according to percent.
	  * @retval None
	  */
	void Hardware_PWM::Start_PWM(uint8_t _ucChannel, double _DutyCycle)
	{
		switch (_ucChannel)
		{
		case TIM_CHANNEL_1:
			if (this->pxUsed_Channels->Channel1 == SingleMode)	//Check the channel status
			{
				this->pxTimer->Instance->CCR1 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
				HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_1);	//Start the PWM channel 1
			}
			else if (this->pxUsed_Channels->Channel1 == ComplementMode)
			{
				this->pxTimer->Instance->CCR1 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
				HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_1);	//Start the PWM channel 1
				HAL_TIMEx_PWMN_Start(this->pxTimer, TIM_CHANNEL_1);	//Start the PWMN channel 1
			}
			break;

		case TIM_CHANNEL_2:
			if (this->pxUsed_Channels->Channel2 == SingleMode)	//Check the channel status
			{
				this->pxTimer->Instance->CCR2 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
				HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_2);	//Start the PWM channel 2
			}
			else if (this->pxUsed_Channels->Channel2 == ComplementMode)
			{
				this->pxTimer->Instance->CCR2 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
				HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_2);	//Start the PWM channel 2
				HAL_TIMEx_PWMN_Start(this->pxTimer, TIM_CHANNEL_2);	//Start the PWMN channel 2
			}
			break;

		case TIM_CHANNEL_3:	
			if (this->pxUsed_Channels->Channel3 == SingleMode)	//Check the channel status
			{
				this->pxTimer->Instance->CCR3 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
				HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_3);	//Start the PWM channel 3
			}
			else if (this->pxUsed_Channels->Channel3 == ComplementMode)
			{
				this->pxTimer->Instance->CCR3 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
				HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_3);	//Start the PWM channel 3
				HAL_TIMEx_PWMN_Start(this->pxTimer, TIM_CHANNEL_3);	//Start the PWMN channel 3
			}
			break;

		case TIM_CHANNEL_4:
			if (this->pxUsed_Channels->Channel4 == SingleMode)	//Check the channel status
			{
				this->pxTimer->Instance->CCR4 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
				HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_4);	//Start the PWM channel 4
			}
			else if (this->pxUsed_Channels->Channel4 == ComplementMode)
			{
				this->pxTimer->Instance->CCR4 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
				HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_4);	//Start the PWM channel 4
				HAL_TIMEx_PWMN_Start(this->pxTimer, TIM_CHANNEL_4);	//Start the PWMN channel 4
			}
			break;
		}
	}

	/**
	  * @brief  This function stops a PWM channel
	  * @param  _ucChannel: The channel number of timer. It can be TIM_CHANNEL_1,2,3,4
	  * @retval None
	  */
	void Hardware_PWM::Stop_PWM(uint8_t _ucChannel)
	{
		switch (_ucChannel)
		{
		case TIM_CHANNEL_1:
			if (this->pxUsed_Channels->Channel1 == SingleMode)	//Check the channel status
			{
				HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_1);	//Stop the PWM channel 1
			}
			else if (this->pxUsed_Channels->Channel1 == ComplementMode)
			{
				HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_1);		//Stop the PWM channel 1
				HAL_TIMEx_PWMN_Stop(this->pxTimer, TIM_CHANNEL_1);	//Stop the PWMN channel 1
			}
			break;

		case TIM_CHANNEL_2:
			if (this->pxUsed_Channels->Channel2 == SingleMode)	//Check the channel status
			{
				HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_2);	//Stop the PWM channel 2
			}
			else if (this->pxUsed_Channels->Channel2 == ComplementMode)
			{
				HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_2);		//Stop the PWM channel 2
				HAL_TIMEx_PWMN_Stop(this->pxTimer, TIM_CHANNEL_2);	//Stop the PWMN channel 2
			}
			break;

		case TIM_CHANNEL_3:
			if (this->pxUsed_Channels->Channel3 == SingleMode)	//Check the channel status
			{
				HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_3);	//Stop the PWM channel 3
			}
			else if (this->pxUsed_Channels->Channel3 == ComplementMode)
			{
				HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_3);		//Stop the PWM channel 3
				HAL_TIMEx_PWMN_Stop(this->pxTimer, TIM_CHANNEL_3);	//Stop the PWMN channel 3
			}
			break;

		case TIM_CHANNEL_4:
			if (this->pxUsed_Channels->Channel4 == SingleMode)	//Check the channel status
			{
				HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_4);	//Stop the PWM channel 4
			}
			else if (this->pxUsed_Channels->Channel4 == ComplementMode)
			{
				HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_4);		//Stop the PWM channel 4
				HAL_TIMEx_PWMN_Stop(this->pxTimer, TIM_CHANNEL_4);	//Stop the PWMN channel 4
			}
			break;
		}
	}

	/**
	  * @brief  This function starts all PWM channels with a dutycycle value
	  * @param  DutyCycle: Dutycycle value according to percent.
	  * @retval None
	  */
	void Hardware_PWM::Start_All_PWM(double _DutyCycle)
	{
		if (this->pxUsed_Channels->Channel1 == SingleMode)	//Check the channel status
		{
			this->pxTimer->Instance->CCR1 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
			HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_1);	//Start the PWM channel 1
		}
		else if (this->pxUsed_Channels->Channel1 == ComplementMode)
		{
			this->pxTimer->Instance->CCR1 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
			HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_1);	//Start the PWM channel 1
			HAL_TIMEx_PWMN_Start(this->pxTimer, TIM_CHANNEL_1);	//Start the PWMN channel 1
		}

		if (this->pxUsed_Channels->Channel2 == SingleMode)	//Check the channel status
		{
			this->pxTimer->Instance->CCR2 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
			HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_2);	//Start the PWM channel 2
		}
		else if (this->pxUsed_Channels->Channel2 == ComplementMode)
		{
			this->pxTimer->Instance->CCR2 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
			HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_2);	//Start the PWM channel 2
			HAL_TIMEx_PWMN_Start(this->pxTimer, TIM_CHANNEL_2);	//Start the PWMN channel 2
		}

		if (this->pxUsed_Channels->Channel3 == SingleMode)	//Check the channel status
		{
			this->pxTimer->Instance->CCR3 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
			HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_3);	//Start the PWM channel 3
		}
		else if (this->pxUsed_Channels->Channel3 == ComplementMode)
		{
			this->pxTimer->Instance->CCR3 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
			HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_3);	//Start the PWM channel 3
			HAL_TIMEx_PWMN_Start(this->pxTimer, TIM_CHANNEL_3);	//Start the PWMN channel 3
		}

		if (this->pxUsed_Channels->Channel4 == SingleMode)	//Check the channel status
		{
			this->pxTimer->Instance->CCR4 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
			HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_4);	//Start the PWM channel 4
		}
		else if (this->pxUsed_Channels->Channel4 == ComplementMode)
		{
			this->pxTimer->Instance->CCR4 = (uint32_t)(this->ulTimer_Period * (_DutyCycle / 100.0));	//Set the Capture Compare Register value
			HAL_TIM_PWM_Start(this->pxTimer, TIM_CHANNEL_4);	//Start the PWM channel 4
			HAL_TIMEx_PWMN_Start(this->pxTimer, TIM_CHANNEL_4);	//Start the PWMN channel 4
		}
	}

	/**
	  * @brief  This function stops all PWM channels
	  * @param  None
	  * @retval None
	  */
	void Hardware_PWM::Stop_All_PWM(void)
	{
		if (this->pxUsed_Channels->Channel1 == SingleMode)	//Check the channel status
		{
			HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_1);	//Stop the PWM channel 1
		}
		else if (this->pxUsed_Channels->Channel1 == ComplementMode)
		{
			HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_1);		//Stop the PWM channel 1
			HAL_TIMEx_PWMN_Stop(this->pxTimer, TIM_CHANNEL_1);	//Stop the PWMN channel 1
		}

		if (this->pxUsed_Channels->Channel2 == SingleMode)	//Check the channel status
		{
			HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_2);	//Stop the PWM channel 2
		}
		else if (this->pxUsed_Channels->Channel2 == ComplementMode)
		{
			HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_2);		//Stop the PWM channel 2
			HAL_TIMEx_PWMN_Stop(this->pxTimer, TIM_CHANNEL_2);	//Stop the PWMN channel 2
		}

		if (this->pxUsed_Channels->Channel3 == SingleMode)	//Check the channel status
		{
			HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_3);	//Stop the PWM channel 3
		}
		else if (this->pxUsed_Channels->Channel3 == ComplementMode)
		{
			HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_3);		//Stop the PWM channel 3
			HAL_TIMEx_PWMN_Stop(this->pxTimer, TIM_CHANNEL_3);	//Stop the PWMN channel 3
		}

		if (this->pxUsed_Channels->Channel4 == SingleMode)	//Check the channel status
		{
			HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_4);	//Stop the PWM channel 4
		}
		else if (this->pxUsed_Channels->Channel4 == ComplementMode)
		{
			HAL_TIM_PWM_Stop(this->pxTimer, TIM_CHANNEL_4);		//Stop the PWM channel 4
			HAL_TIMEx_PWMN_Stop(this->pxTimer, TIM_CHANNEL_4);	//Stop the PWMN channel 4
		}
	}

	/**
	  * @brief  This function changes the dutycycle of a channel
	  * @param  Channel: The channel number of timer. It can be TIM_CHANNEL_1,2,3,4
	  *			DutyCycle: Dutycycle value according to percent.
	  * @retval None
	  */
	void Hardware_PWM::Change_DutyCycle(uint8_t _ucChannel, double _DutyCycle)
	{
		this->Start_PWM(_ucChannel, _DutyCycle);
	}

	/**
	  * @brief  This function changes the PWM frequency.
	  *			Be carefule, after this function you should start your channels with specific dutycycle.
	  * @param  _ulNewFrequency: PWM frequency according to Hz
	  * @retval None
	  */
	void Hardware_PWM::Change_Frequency(uint32_t _ulNewFrequency)
	{
		this->Stop_All_PWM();	//At first, stop all channels
		this->pxTimerSpecs_Data->_ulFrequency = _ulNewFrequency;		//Save the new timer frequency
		this->Timer_Calculator(this->pxTimerSpecs_Data->_ulFrequency);	//Choose the best values for timer period and timer prescaler
		this->Timer_Init();		//Initialize the timer
	}

	/**
	  * @brief  This function initializes the timer
	  * @param  None
	  * @retval None
	  */
	void Hardware_PWM::Timer_Init(void)
	{
		TIM_ClockConfigTypeDef sClockSourceConfig = { 0 };
		TIM_MasterConfigTypeDef sMasterConfig = { 0 };
		TIM_OC_InitTypeDef sConfigOC = { 0 };
		TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = { 0 };

		this->pxTimer->Instance = TIM1;
		this->pxTimer->Init.Prescaler = this->ulTimer_Prescaler;
		this->pxTimer->Init.CounterMode = TIM_COUNTERMODE_UP;
		this->pxTimer->Init.Period = this->ulTimer_Period;
		this->pxTimer->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
		this->pxTimer->Init.RepetitionCounter = 0;
		this->pxTimer->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
		if (HAL_TIM_Base_Init(this->pxTimer) != HAL_OK)
		{
			Error_Handler();
		}
		sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
		if (HAL_TIM_ConfigClockSource(this->pxTimer, &sClockSourceConfig) != HAL_OK)
		{
			Error_Handler();
		}
		if (HAL_TIM_PWM_Init(this->pxTimer) != HAL_OK)
		{
			Error_Handler();
		}
		if (HAL_TIM_OC_Init(this->pxTimer) != HAL_OK)
		{
			Error_Handler();
		}
		sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
		sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
		if (HAL_TIMEx_MasterConfigSynchronization(this->pxTimer, &sMasterConfig) != HAL_OK)
		{
			Error_Handler();
		}
		sConfigOC.OCMode = TIM_OCMODE_PWM1;
		sConfigOC.Pulse = 0;
		sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
		sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
		sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
		sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
		sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
		if (HAL_TIM_PWM_ConfigChannel(this->pxTimer, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
		{
			Error_Handler();
		}
		if (HAL_TIM_PWM_ConfigChannel(this->pxTimer, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
		{
			Error_Handler();
		}
		sConfigOC.OCMode = TIM_OCMODE_TIMING;
		if (HAL_TIM_OC_ConfigChannel(this->pxTimer, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
		{
			Error_Handler();
		}
		sConfigOC.OCMode = TIM_OCMODE_PWM1;
		if (HAL_TIM_PWM_ConfigChannel(this->pxTimer, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
		{
			Error_Handler();
		}
		sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
		sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
		sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
		sBreakDeadTimeConfig.DeadTime = this->Timer_DeadTime_Calculator();
		sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
		sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
		sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
		if (HAL_TIMEx_ConfigBreakDeadTime(this->pxTimer, &sBreakDeadTimeConfig) != HAL_OK)
		{
			Error_Handler();
		}
		HAL_TIM_MspPostInit(this->pxTimer);
	}

	/**
	  * @brief  This function chooses the best value of timer period and timer prescaler according to PWM frequency and timer resolution
	  * @param  _ulFrequency: The frequency of PWM signal according to Hz
	  * @retval None
	  */
	void Hardware_PWM::Timer_Calculator(uint32_t _ulFrequency)
	{
		uint32_t Timer_Clock = this->Timer_Get_Frequency();

		this->ulTimer_Prescaler = 0;			//Set the initial value

		if (_ulFrequency < (Timer_Clock / 10))	//Limit the maximum frequency
		{
			if (this->pxTimerSpecs_Data->_xTimerIs32bit == true)	//The entered timer is 32 bit
			{
				do
				{
					this->ulTimer_Period = Timer_Clock / ((this->ulTimer_Prescaler + 1) * (_ulFrequency));	//Calculate the timer period value
					this->ulTimer_Prescaler++;				//Increse the prescaler value
				} while (this->ulTimer_Period > 0xFFFFFFFF);//Check the timer period value
				this->ulTimer_Prescaler--;	//Because of timer
				this->ulTimer_Period--;		//Because of timer
			}
			else	//The entered timer is 16 bit
			{
				do
				{
					this->ulTimer_Period = Timer_Clock / ((this->ulTimer_Prescaler + 1) * (_ulFrequency));	//Calculate the timer period value
					this->ulTimer_Prescaler++;				//Increse the prescaler value
				} while (this->ulTimer_Period > 0xFFFF);	//Check the timer period value
				this->ulTimer_Prescaler--;	//Because of timer
				this->ulTimer_Period--;		//Because of timer
			}
		}
	}

	/**
	  * @brief  This function calculates the deadtime register value according to deadtime (nS)
	  *			Note: Deadtime registe value sholud not be bigger than timer deadtime register capacitance. It depends on the used timer.
	  * @param  None
	  * @retval Deadtime register value
	  */
	uint8_t Hardware_PWM::Timer_DeadTime_Calculator(void)
	{
		uint32_t DeadTime = 0;

		DeadTime = (uint32_t)((this->Timer_Get_Frequency() / 1e9) * this->pxTimerSpecs_Data->_ulDeadTime);	//Calculate the DeadTime register value

		return DeadTime;
	}

	/**
	  * @brief  This function returns the timer frequency value according to microcontroller type
	  *			Be careful, this function should be completed for different microcontroller types.
	  *			Before using this function check your microcontroller type here and make sure about its bus clock
	  * @param  None
	  * @retval Timer Frequency according to Hz
	  */
	uint32_t Hardware_PWM::Timer_Get_Frequency(void)
	{
		uint32_t Frequency = 0;

#ifdef STM32F0
		/*All timers are connected to the APB1 bus clock ==> Max = 48MHz*/
		if (HAL_RCC_GetHCLKFreq() == HAL_RCC_GetPCLK1Freq())	//It means APB1 Prescaler = 1
		{
			Frequency = HAL_RCC_GetPCLK1Freq();
		}
		else	//It means APB1 Prescaler != 1
		{
			Frequency = HAL_RCC_GetPCLK1Freq() * 2;
		}
#endif

#ifdef STM32F1
		if (this->pxTimer->Instance == TIM2 || this->pxTimer->Instance == TIM3 || this->pxTimer->Instance == TIM4) //These timers are connected to the APB1 bus clock ==> Max = 36MHz
		{
			if (HAL_RCC_GetHCLKFreq() == HAL_RCC_GetPCLK1Freq())	//It means APB1 Prescaler = 1
			{
				Frequency = HAL_RCC_GetPCLK1Freq();
			}
			else	//It means APB1 Prescaler != 1
			{
				Frequency = HAL_RCC_GetPCLK1Freq() * 2;
			}
		}
		else	//These timers are connected to the APB2 bus clock ==> Max = 72MHz
		{
			if (HAL_RCC_GetHCLKFreq() == HAL_RCC_GetPCLK2Freq())	//It means APB2 Prescaler = 1
			{
				Frequency = HAL_RCC_GetPCLK2Freq();
			}
			else	//It means APB2 Prescaler != 1
			{
				Frequency = HAL_RCC_GetPCLK2Freq() * 2;
			}
		}
#endif

#ifdef STM32F2
		if (this->pxTimer->Instance == TIM2 || this->pxTimer->Instance == TIM3 || this->pxTimer->Instance == TIM4 ||
			this->pxTimer->Instance == TIM5 || this->pxTimer->Instance == TIM6 || this->pxTimer->Instance == TIM7 ||
			this->pxTimer->Instance == TIM12 || this->pxTimer->Instance == TIM13 || this->pxTimer->Instance == TIM14) //These timers are connected to the APB1 bus clock ==> Max = 30MHz
		{
			if (HAL_RCC_GetHCLKFreq() == HAL_RCC_GetPCLK1Freq())	//It means APB1 Prescaler = 1
			{
				Frequency = HAL_RCC_GetPCLK1Freq();
			}
			else	//It means APB1 Prescaler != 1
			{
				Frequency = HAL_RCC_GetPCLK1Freq() * 2;
			}
		}
		else	//These timers are connected to the APB2 bus clock ==> Max = 60MHz
		{
			if (HAL_RCC_GetHCLKFreq() == HAL_RCC_GetPCLK2Freq())	//It means APB2 Prescaler = 1
			{
				Frequency = HAL_RCC_GetPCLK2Freq();
			}
			else	//It means APB2 Prescaler != 1
			{
				Frequency = HAL_RCC_GetPCLK2Freq() * 2;
			}
		}

#endif

#ifdef STM32F3
		if (this->pxTimer->Instance == TIM2 || this->pxTimer->Instance == TIM3 || this->pxTimer->Instance == TIM4 ||
			this->pxTimer->Instance == TIM6 || this->pxTimer->Instance == TIM7) //These timers are connected to the APB1 bus clock ==> Max = 36MHz
		{
			if (HAL_RCC_GetHCLKFreq() == HAL_RCC_GetPCLK1Freq())	//It means APB1 Prescaler = 1
			{
				Frequency = HAL_RCC_GetPCLK1Freq();
			}
			else	//It means APB1 Prescaler != 1
			{
				Frequency = HAL_RCC_GetPCLK1Freq() * 2;
			}
		}
		else	//These timers are connected to the APB2 bus clock ==> Max = 72MHz
		{
			if (HAL_RCC_GetHCLKFreq() == HAL_RCC_GetPCLK2Freq())	//It means APB2 Prescaler = 1
			{
				Frequency = HAL_RCC_GetPCLK2Freq();
			}
			else	//It means APB2 Prescaler != 1
			{
				Frequency = HAL_RCC_GetPCLK2Freq() * 2;
			}
		}

#endif

#ifdef STM32F4
		if (this->pxTimer->Instance == TIM2 || this->pxTimer->Instance == TIM3 || this->pxTimer->Instance == TIM4 ||
			this->pxTimer->Instance == TIM5 || this->pxTimer->Instance == TIM6 || this->pxTimer->Instance == TIM7 ||
			this->pxTimer->Instance == TIM12 || this->pxTimer->Instance == TIM13 || this->pxTimer->Instance == TIM14) //These timers are connected to the APB1 bus clock ==> Max = 42MHz
		{
			if (HAL_RCC_GetHCLKFreq() == HAL_RCC_GetPCLK1Freq())	//It means APB1 Prescaler = 1
			{
				Frequency = HAL_RCC_GetPCLK1Freq();
			}
			else	//It means APB1 Prescaler != 1
			{
				Frequency = HAL_RCC_GetPCLK1Freq() * 2;
			}
		}
		else	//These timers are connected to the APB2 bus clock ==> Max = 84MHz
		{
			if (HAL_RCC_GetHCLKFreq() == HAL_RCC_GetPCLK2Freq())	//It means APB2 Prescaler = 1
			{
				Frequency = HAL_RCC_GetPCLK2Freq();
			}
			else	//It means APB2 Prescaler != 1
			{
				Frequency = HAL_RCC_GetPCLK2Freq() * 2;
			}
		}

#endif

#ifdef STM32F7
		if (this->pxTimer->Instance == TIM2 || this->pxTimer->Instance == TIM3 || this->pxTimer->Instance == TIM4 ||
			this->pxTimer->Instance == TIM5 || this->pxTimer->Instance == TIM6 || this->pxTimer->Instance == TIM7 ||
			this->pxTimer->Instance == TIM12 || this->pxTimer->Instance == TIM13 || this->pxTimer->Instance == TIM14) //These timers are connected to the APB1 bus clock ==> Max = 54MHz
		{
			if (HAL_RCC_GetHCLKFreq() == HAL_RCC_GetPCLK1Freq())	//It means APB1 Prescaler = 1
			{
				Frequency = HAL_RCC_GetPCLK1Freq();
			}
			else	//It means APB1 Prescaler != 1
			{
				Frequency = HAL_RCC_GetPCLK1Freq() * 2;
			}
		}
		else	//These timers are connected to the APB2 bus clock ==> Max = 108MHz
		{
			if (HAL_RCC_GetHCLKFreq() == HAL_RCC_GetPCLK2Freq())	//It means APB2 Prescaler = 1
			{
				Frequency = HAL_RCC_GetPCLK2Freq();
			}
			else	//It means APB2 Prescaler != 1
			{
				Frequency = HAL_RCC_GetPCLK2Freq() * 2;
			}
		}

#endif
		return Frequency;
	}
}
/*****************************END OF FILE*****************************/