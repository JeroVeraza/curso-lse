#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"


#define LED_RED	2
#define POTE    8 //CANAL 8

int main(void) {
	BOARD_BootClockFRO24M();
    BOARD_InitBootClocks();
    BOARD_InitDebugConsole();
    CLOCK_EnableClock(kCLOCK_Swm);
        // Configuro la funcion de ADC en el canal del potenciometro
        SWM_SetFixedPinSelect(SWM0, kSWM_ADC_CHN0, true);
        // Desactivo clock de matriz de conmutacion
        CLOCK_DisableClock(kCLOCK_Swm);

        // Elijo clock desde el FRO con divisor de 1 (30MHz)
        CLOCK_Select(kADC_Clk_From_Fro);
        CLOCK_SetClkDivider(kCLOCK_DivAdcClk, 1);

        // Prendo el ADC
        POWER_DisablePD(kPDRUNCFG_PD_ADC0);
        // Obtengo frecuencia deseada y calibro ADC
    	uint32_t frequency = CLOCK_GetFreq(kCLOCK_Fro) / CLOCK_GetClkDivider(kCLOCK_DivAdcClk);
    	ADC_DoSelfCalibration(ADC0, frequency);
    	// Configuracion por defecto del ADC (Synchronous Mode, Clk Divider 1, Low Power Mode true, High Voltage Range)
    	adc_config_t adc_config;
    	ADC_GetDefaultConfig(&adc_config);
        // Habilito el ADC
    	ADC_Init(ADC0, &adc_config);
    	// Configuracion para las conversiones
    	adc_conv_seq_config_t adc_sequence = {
    		.channelMask = 1 << POT,							// Elijo el canal del potenciometro
    		.triggerMask = 0,										// No hay trigger por hardware
    		.triggerPolarity = kADC_TriggerPolarityPositiveEdge,	// Flanco ascendente
    		.enableSyncBypass = false,								// Sin bypass de trigger
    		.interruptMode = kADC_InterruptForEachConversion		// Interrupciones para cada conversion
    	};
    	// Configuro y habilito secuencia A
    	ADC_SetConvSeqAConfig(ADC0, &adc_sequence);
    	ADC_EnableConvSeqA(ADC0, true);
    gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };
    GPIO_PortInit(GPIO, 1);
    GPIO_PinInit(GPIO, 1, LED_RED, &out_config);


        SysTick_Config(SystemCoreClock / 1000);



    return 0;
}
void SysTick_Handler(void) {
	adc_result_info_t adc_info;
	ADC_DoSoftwareTriggerConvSeqA(ADC0);
	while(!ADC_GetChannelConversionResult(ADC0, POT, &adc_info));
	static uint16_t i = 0;

	if(i == 500) {
		i = 0;
		GPIO_PinWrite(GPIO, 1, LED_BLUE, !GPIO_PinRead(GPIO, 1, LED_BLUE));
	}

}
