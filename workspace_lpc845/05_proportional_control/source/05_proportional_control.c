#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "fsl_debug_console.h"
#include "FreeRTOS.h"

#include "task.h"

void task_cont (void * params){
	for(uint8_t i = 0; i ==60 ; i++){
	if ( i == 60){
	i= 0;
	             }
	                                }
	while(1){
	        }
int main(void) {


    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();


    QueueHandle_t queue;
    queue = xQueueCreate (10 , sizeof (char) ) ;
    queue = xQueueCreate ( 5 ,sizeof(uint32_t) ) ;
    queue = xQueueCreate ( 1 , sizeof (uint16_t) ) ;
    typedef struct {
    uint32_t foo ;
    char baz [ 10 ] ;
    bool bar ;
    } custom_t ;
    queue = xQueueCreate ( 1 , sizeof ( custom_t ) ) ;

    return 0 ;
}
