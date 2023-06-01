#pragma once


#include <emblib_stm32/interfaces/uart.h>


namespace emb {

namespace uart {

class UartInterface {
public:
	UartInterface() = default;
	virtual ~UartInterface() = default;
	
	UartInterface(const UartInterface& other) = delete;
	UartInterface& operator=(const UartInterface& other) = delete;

	//virtual void reset() = 0;
	//virtual bool hasRxError() const = 0;

	virtual int getchar(char& ch) = 0;
	virtual int recv(char* buf, int len) = 0;

	virtual int putchar(char ch) = 0;
	virtual int send(const char* buf, int len) = 0;

	//virtual void registerRxInterruptHandler(void (*handler)(void)) = 0;
	//virtual void enableRxInterrupts() = 0;
	//virtual void disableRxInterrupts() = 0;
	//virtual void acknowledgeRxInterrupt() = 0;
};

} // namespace uart

} // namespace emb

