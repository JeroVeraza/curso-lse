#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"

#define LED_RED 2
#define USER 4

/*
 * @brief   Application entry point.
*/
int main(void) {
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();


    gpio_pin_config_t in_config = { kGPIO_DigitalInput };
    GPIO_PortInit(GPIO, 0);
    GPIO_PinInit(GPIO, 0, USER, &in_config);
    gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };
    GPIO_PortInit(GPIO, 1);
    GPIO_PinInit(GPIO, 1, LED_RED, &out_config);

    while(1) {
    	if(!!GPIO_PinRead(GPIO, 0, USER)){
    		GPIO_PinWrite(GPIO, 1, LED_RED, 0);
    	}
    	else {

    	    		GPIO_PinWrite(GPIO, 1, LED_RED, 1);
    	    	}
    	    }

    	return 0;
}

