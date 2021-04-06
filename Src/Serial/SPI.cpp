/*
 * SPI.cpp
 *
 *  Created on: Sep 17, 2020
 *      Author: hejmi
 */

#include <Serial/SPI.h>

namespace Serial {


SPI::SPI(SPI_HandleTypeDef& handle, DMA_HandleTypeDef& dmaRX, DMA_HandleTypeDef& dmaTX) :
		isrFlag_(false),
		state_(STATE_IDLE),
		busHandle_(handle),
		RXDmaHandle_(dmaRX),
		TXDmaHandle_(dmaTX),
		rxCount_(0)
{
}

/*
 * Write data over the SPI-bus.
 *
 * Use this method to write data over the SPI-bus.
 *
 * @param ´addr´ 	Device address for which the data should be written to.
 * @param ´data´ 	Data to be transmitted.
 * @param ´count´	The number of bytes to transmit.
 * */
void SPI::Write(const uint16_t addr, const uint8_t* reg_and_data, const uint16_t count){
	HAL_SPI_Transmit((SPI_HandleTypeDef*)&busHandle_, const_cast<uint8_t*>(reg_and_data), count, HAL_MAX_DELAY);
}

/*
 * Write data over the SPI-bus with a specified timeout.
 *
 * Use this method to write data over the SPI-bus with a specified timeout.
 *
 * @param ´addr´ 	Device address for which the data should be written to.
 * @param ´data´ 	Data to be transmitted.
 * @param ´count´	The number of bytes to transmit.
 * @param ´timeout´	The amount of sys-ticks before timing out.
 * */
void SPI::Write(const uint16_t addr, const uint8_t* reg_and_data, const uint16_t count, uint32_t timeout)
{
	HAL_StatusTypeDef status = HAL_SPI_Transmit((SPI_HandleTypeDef*)&busHandle_, const_cast<uint8_t*>(reg_and_data), count, timeout);
	if (status!=HAL_OK)
		throw TimeoutError();
}

/*
 * Read data over the SPI-bus.
 *
 * Use this method to read data from SPI-bus.
 *
 * @param ´addr´ 	Device address for which the data should be read from.
 * @param ´data´ 	Data container for the read data.
 * @param ´count´	The maximum bytes to read.
 * */
void SPI::Read(const uint16_t addr, uint8_t* data, const uint16_t count){
	HAL_SPI_Receive((SPI_HandleTypeDef*)&busHandle_, data, count, HAL_MAX_DELAY);
}

/*
 * Read data over the SPI-bus with a specified timeout.
 *
 * Use this method to read data from SPI-bus with a specified timeout.
 *
 * @param ´addr´ 	Device address for which the data should be read from. Ignored when the serial interface has no addressing scheme.
 * @param ´data´ 	Data container for the read data.
 * @param ´count´	The maximum bytes to read.
 * @param ´timeout´ The amount of sys-ticks before timing out.
 * */
void SPI::Read(const uint16_t addr, uint8_t* data, const uint16_t count, uint32_t timeout){
	HAL_StatusTypeDef status = HAL_SPI_Receive((SPI_HandleTypeDef*)&busHandle_, data, count, timeout);
	if (status!=HAL_OK)
		throw TimeoutError();
}

/*
 * Read data asynchronously over the SPI-bus.
 *
 * Use this method to initiate an asynchronously read from the SPI-bus. This method returns instantly.
 *
 * @param ´data´ 	Data container for the read data.
 * @param ´count´ 	Maximum amount of bytes to read.
 * */
void SPI::BeginReadAsync(uint8_t* data, const uint16_t count)
{
	isrFlag_ = false;
	HAL_StatusTypeDef status = HAL_SPI_Receive_DMA((SPI_HandleTypeDef*)&busHandle_, data, count);
	if (status != HAL_OK){
		throw AsyncReceptionError();
	}
}

/*
 * Write data asynchronously over the SPI-bus.
 *
 * Use this method to initiate an asynchronously write to the SPI-bus. This method returns instantly.
 *
 * @param ´data´ 	Data container for the read data.
 * @param ´count´ 	Maximum amount of bytes to read.
 * */
void SPI::BeginWriteAsync(uint8_t* data, const uint16_t count)
{
	//TODO: Make sure to abort before Transmitting
	//HAL_SPI_Abort(busHandle_);
	HAL_StatusTypeDef status = HAL_SPI_Transmit_DMA((SPI_HandleTypeDef*)&busHandle_, data, count);

	if (status != HAL_OK){
		throw AsyncTransmissionError();
	}

}

void SPI::OnInterrupt(uint16_t sig)
{
	// Message recieved
	isrFlag_ = true;
}

void SPI::Run(){
	while(true){
	switch(state_){
		case(STATE_IDLE):
			state_ = STATE_START_RECIEVE;	// Fall through for now
		case(STATE_START_RECIEVE):
			try{
				BeginReadAsync(rxBuffer_,RXBUFFER_SIZE);
				state_ = STATE_RECIEVING;	// If successful dma start
			} catch (const SPIException& e){
				break;
			}
			break;
		case(STATE_RECIEVING):
			// Wait for interrupt!
			if (isrFlag_)
				state_ = STATE_DONE_RECIEVING;	// fall through
			else
				break;
		case(STATE_DONE_RECIEVING):
			{//uint32_t rxCount_ = RXBUFFER_SIZE - ((DMA_Stream_TypeDef *)busHandle_->hdmarx->Instance)->NDTR;
			HAL_SPI_Abort((SPI_HandleTypeDef*)&busHandle_);	// Abort transfer and DMA
			state_ = STATE_IDLE;		// If successful transfer!
			break;}
		default:
			//TODO: Set to idle or ERROR!
			state_ = STATE_ERROR;
			break;
	}
	}
}

SPI::~SPI() {
	// TODO Auto-generated destructor stub
}

} /* namespace Serial */
