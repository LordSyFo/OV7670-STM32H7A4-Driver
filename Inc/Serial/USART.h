/*
 * USART.h
 *
 *  Created on: 17 Sep 2020
 *      Author: Nicklas Grunert (@github.com/LordSyFo)
 */

#ifndef INC_SERIAL_USART_H_
#define INC_SERIAL_USART_H_

#include <Serial/ISerial.h>
#include "stm32h7xx_hal.h"

namespace Serial {

/* USART 1 PB14 and PB15 */
class USART: public ISerial {
public:
	USART(UART_HandleTypeDef* handle);

	void Write(const uint16_t addr, const uint8_t* reg_and_data, const uint16_t count);

	void Read(const uint16_t addr, uint8_t* data, const uint16_t count);

	virtual ~USART();
private:

	UART_HandleTypeDef* busHandle_;
};

} /* namespace Serial */

#endif /* INC_SERIAL_USART_H_ */
