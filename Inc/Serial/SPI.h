/*
 * SPI.h
 *
 *  Created on: Sep 17, 2020
 *      Author: hejmi
 */

#ifndef SRC_SERIAL_SPI_H_
#define SRC_SERIAL_SPI_H_

#include <Serial/ISerial.h>
#include <Util/AProcess.h>
#include "stm32h7xx_hal.h"
#include <Util/Interruptable.h>
#include <Serial/SPIExceptions.h>

#define RXBUFFER_SIZE 50

namespace Serial {

#define STATE_IDLE 0
#define STATE_START_RECIEVE 1
#define STATE_RECIEVING 2
#define STATE_DONE_RECIEVING 3
#define STATE_ERROR 16

class SPI: public ISerial, public Util::AProcess, public Util::Interruptable {
public:
	SPI(SPI_HandleTypeDef& handle,DMA_HandleTypeDef& dmaRX,DMA_HandleTypeDef& dmaTX);

	void Write(const uint16_t addr, const uint8_t* reg_and_data, const uint16_t count);

	void Read(const uint16_t addr, uint8_t* data, const uint16_t count);

	void Write(const uint16_t addr, const uint8_t* reg_and_data, const uint16_t count, uint32_t timeout);

	void Read(const uint16_t addr, uint8_t* data, const uint16_t count, uint32_t timeout);

	void BeginReadAsync(uint8_t* data, const uint16_t count);

	void BeginWriteAsync(uint8_t* data, const uint16_t count);

	/*
	 * Determine if a message has been received.
	 *
	 * Use this method to determine if a message has been received.
	 *
	 * @return True if message has been received and false otherwise.
	 * */
	bool MessageReady() {
		return isrFlag_;
	}

	/*
	 * Get length of a recieved message.
	 *
	 * Use this method to retrieve the length of a recieved message.
	 *
	 * @return Returns the receieved message length.
	 * */
	uint32_t GetMessageLength() {
		return RXBUFFER_SIZE - ((DMA_Stream_TypeDef*)busHandle_.hdmarx->Instance)->NDTR;
	}

	/*
	 * Reset low-level hardware states.
	 * */
	void Reset() {
		__HAL_UNLOCK(&busHandle_);
		__HAL_UNLOCK(&RXDmaHandle_);
		__HAL_UNLOCK(&TXDmaHandle_);
		HAL_SPI_Abort((SPI_HandleTypeDef*)&busHandle_);	// Abort transfer and DMA
	}

	void OnInterrupt(uint16_t sig);

	void Run();
	void OnEnter(){}
	void OnExit(){}

	virtual ~SPI();

private:

	bool isrFlag_;
	uint8_t state_;

	SPI_HandleTypeDef& busHandle_;
	DMA_HandleTypeDef& RXDmaHandle_;
	DMA_HandleTypeDef& TXDmaHandle_;

	uint8_t rxBuffer_[RXBUFFER_SIZE] = {0};
	uint32_t rxCount_;
};

} /* namespace Serial */

#endif /* SRC_SERIAL_SPI_H_ */
