/*
 * USART.cpp
 *
 *  Created on: 17 Sep 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#include <Serial/USART.h>

namespace Serial {

USART::USART(UART_HandleTypeDef* handle) : busHandle_(handle) {
}

/*
 * Write data over the USART-bus.
 *
 * Use this method to write data over the USART-bus.
 *
 * @param ´addr´ 	Device address for which the data should be written to.
 * @param ´data´ 	Data to be transmitted.
 * @param ´count´	The number of bytes to transmit.
 * */
void USART::Write(const uint16_t addr, const uint8_t* reg_and_data, const uint16_t count){
	//Ignore address as this isnt used for USART!
	HAL_UART_Transmit(busHandle_, const_cast<uint8_t*>(reg_and_data), count, HAL_MAX_DELAY);
}

/*
 * Read data over the USART-bus.
 *
 * Use this method to read data from USART-bus.
 *
 * @param ´addr´ 	Device address for which the data should be read from.
 * @param ´data´ 	Data container for the read data.
 * @param ´count´	The maximum bytes to read.
 * */
void USART::Read(const uint16_t addr, uint8_t* data, const uint16_t count){
	//Ignore address as this isnt used for USART!
	HAL_UART_Receive(busHandle_, data, count, HAL_MAX_DELAY);
}


USART::~USART() {
	// TODO Auto-generated destructor stub
}

} /* namespace Serial */
