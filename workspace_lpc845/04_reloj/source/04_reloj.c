#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"

#include "task.h"

void wrapper_display_init(void) {
		// Inicializo los pines como salidas
		gpio_pin_config_t config = { kGPIO_DigitalOutput, true };
		uint32_t pins[] = { SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G, COM_1, COM_2 };
		for(uint8_t i = 0; i < sizeof(pins) / sizeof(uint32_t); i++) {
			GPIO_PinInit(GPIO, 0, pins[i], &config);
			GPIO_PinWrite(GPIO, 0, pins[i], 1);
		}
		}
void wrapper_display_write(uint8_t number) {
		// Array con valores para los pines
		uint8_t values[] = { ~0x3f, ~0x6, ~0x5b, ~0x4f, ~0x66, ~0x6d, ~0x7d, ~0x7, ~0x7f, ~0x6f };
		// Array con los segmentos
		uint32_t pins[] = { SEG_A, SEG_B, SEG_C, SEG_D, SEG_E, SEG_F, SEG_G };

    for(uint8_t i = 0; i < sizeof(pins) / sizeof(uint32_t); i++) {
			// Escribo el valor del bit en el segmento que corresponda
			uint32_t val = (values[number] & (1 << i))? 1 : 0;
			GPIO_PinWrite(GPIO, 0, pins[i], val);
		}
	}
void task_cont (void * params){
	for(uint8_t i = 0; i ==60 ; i++){
	if ( i == 60){
	i= 0;
	             }
	                                }
	while(1){
	        }
		                      }
void task_disp (void * params){
	while(1){
	        }
		                      }

int main(void) {

	BOARD_BootClockFRO30M();

	xTaskCreate(
			task_cont,
			"Contador",
			64,
			NULL,
			1,
			NULL
		);

	xTaskCreate(
				task_disp,
				"Display",
				64,
				NULL,
				1,
				NULL
			);

//1 apago ambos (anodos)
	// PONGO EL 7 - PRENDO DISPLAY DEL 7 - DEMORA 20ms - APAGO AMBOS - PONGO 1 - PRENDO DISPLAY DEL 1 - DELAY 20ms

    return 0 ;
}
