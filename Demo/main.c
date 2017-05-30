#include <FreeRTOS.h>
#include <task.h>
#include <stdint.h>  //for uint8_t
//#include "FreeRTOS_sockets.h" //for FreeRTOS_IPInit

#include "Drivers/irq.h"
#include "Drivers/gpio.h"

static uint8_t ucMACAddress[ 6 ] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55 };

/* Define the network addressing.  These parameters will be used if either
ipconfigUDE_DHCP is 0 or if ipconfigUSE_DHCP is 1 but DHCP auto configuration
failed. */
static const uint8_t ucIPAddress[ 4 ] = { 10, 10, 10, 200 };
static const uint8_t ucNetMask[ 4 ] = { 255, 0, 0, 0 };
static const uint8_t ucGatewayAddress[ 4 ] = { 10, 10, 10, 1 };

/* The following is the address of an OpenDNS server. */
static const uint8_t ucDNSServerAddress[ 4 ] = { 208, 67, 222, 222 };

void task1(void *pParam) {
int i = 0;
	while(1) {
		i++;
		vTaskDelay(100);
		SetGpio(16, 1);
		vTaskDelay(100);
	}

}

void task2(void *pParam) {

	int i = 0;
	while(1) {
		i++;
		vTaskDelay(100);
		SetGpio(16, 0);
		vTaskDelay(100);
	}
}


/**
 *	This is the systems main entry, some call it a boot thread.
 *
 *	-- Absolutely nothing wrong with this being called main(), just it doesn't have
 *	-- the same prototype as you'd see in a linux program.
 **/



void main (void)
{
	 
	SetGpioFunction(16, 1);			// RDY led

	
	xTaskCreate(task1, "LED_0", 128, NULL, 0, NULL);
	xTaskCreate(task2, "LED_1", 128, NULL, 0, NULL);

	vTaskStartScheduler();

	/*
	 *	We should never get here, but just in case something goes wrong,
	 *	we'll place the CPU into a safe loop.
	 */
	while(1) {
		;
	}
}
