#ifndef ISRCALLBACKS_H
#define ISRCALLBACKS_H

#include <Util/InterruptWrapper.h>
#include <Thread/Events/Events.hpp>

#define USE_EVENTS_DCMI 1

/*
 *
 * This headerfile should contain the callback functions used in the HAL driver.
 * These will be called whenever an appropriate interrupt is detected on the corresponding GPIO_Pin.
 *
 * */

/* External variables */
extern Util::InterruptWrapper dcmi_isr_wrapper;
extern TIM_HandleTypeDef htim1;
extern Util::InterruptWrapper spiss_isr_wrapper;
extern osSemaphoreId_t g_Semaphore;

/**
  * @brief  EXTI line detection callback.
  * @param  GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin==SPI_SS_Pin){
		Thread::Events::Signal(Thread::Events::SPISelectEvent);
		//osThreadYield();

	}
}

/**
  * @brief  Frame Event callback.
  * @param  hdcmi pointer to a DCMI_HandleTypeDef structure that contains
  *                the configuration information for DCMI.
  * @retval None
  */
void HAL_DCMI_FrameEventCallback(DCMI_HandleTypeDef *hdcmi)
{
	// A complete frame has been captured!
	#ifdef USE_EVENTS_DCMI
		Thread::Events::Signal(Thread::Events::DCMIFrameCaptureEvent);
	#else
		dcmi_isr_wrapper.Callback(0);	// 0 = FRAME_INTERRUPT
	#endif
}

/**
  * @brief  Error DCMI callback.
  * @param  hdcmi pointer to a DCMI_HandleTypeDef structure that contains
  *                the configuration information for DCMI.
  * @retval None
  */
void HAL_DCMI_ErrorCallback(DCMI_HandleTypeDef *hdcmi)
{
	// ERROR While capturing image!
	dcmi_isr_wrapper.Callback(0xFF);	// 0xFF = DCMI_ERROR
}

/**
  * @brief  Period elapsed callback in non-blocking mode
  * @param  htim TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	#ifdef USE_EVENTS_DCMI
	/*if (htim->Instance == TIM1) DEPRICATED
		Events::EmitEvent(Events::Flag::k_TimeoutFlag);*/
	#else
	if (htim->Instance == TIM1)
		dcmi_isr_wrapper.Callback(0xF0);	// 0xF0 = DCMI_TIMEOUT
	#endif
	if (htim->Instance == TIM6) {
		HAL_IncTick();
	}
}

#endif
