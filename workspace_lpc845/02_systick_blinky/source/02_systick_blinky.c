#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"

// Etiqueta para el LED azul
#define LED_BLUE	2
#define LED_DEUNO   29

/*
 * @brief   Application entry point.
*/
int main(void) {
	BOARD_BootClockFRO24M();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();

    gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };
    GPIO_PortInit(GPIO, 1);
    GPIO_PinInit(GPIO, 1, LED_BLUE, &out_config);
    GPIO_PortInit(GPIO, 0);
        GPIO_PinInit(GPIO, 0, LED_DEUNO, &out_config);

        SysTick_Config(SystemCoreClock / 1000);



    return 0;
}
/**
 * @brief Handler para interrupcion de SysTick
 */
void SysTick_Handler(void) {
	static uint16_t i = 0;
	static uint16_t b = 0;
	i++;
	b++;
	if(i == 500) {
		// Reinicio el contador
		i = 0;
		// Conmuto el LED
		GPIO_PinWrite(GPIO, 1, LED_BLUE, !GPIO_PinRead(GPIO, 1, LED_BLUE));
	}
	if(b == 1500) {
			// Reinicio el contador
			b = 0;
			// Conmuto el LED
			GPIO_PinWrite(GPIO, 0, LED_DEUNO, !GPIO_PinRead(GPIO, 0, LED_DEUNO));
		}
}
