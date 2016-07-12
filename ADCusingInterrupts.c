/*
 * ADCusingInterrupts.c
 *
 * Created: 26-06-2015 22:44:54
 *  Author: Sandeep
 */ 


#include <avr/io.h>
#include<avr/interrupt.h>

int main(void)
{
	//Configure ADC
	
	ADCSRA |= 1<<ADPS2;				//enable prescaler-determined by clock  1000000/p= [50000,200000] p=[20,5]
	ADMUX |= 1<<ADLAR;				//left adjust the result 8bit 10bit
	ADMUX |= 1<<REFS0;				//set reference voltage
	ADCSRA |= 1<<ADIE;				//enable interrupts function	
	ADCSRA |= 1<<ADEN;				//turn on adc
	
	sei();						//Enable global interrupts

	ADCSRA |= 1<<ADSC;				//start first conversion
	
		
	
    while(1)
    {
        //Code
    }
}

/////////////Interrupt routine and display results

ISR(ADC_vect)
{
	char adcResult[4];
	uint8_t LowBit = ADCL;
	uint16_t TenBitResult = ADCH<<2 | LowBit>>6;				//ADLAR=1 set above
	
	itoa(TenBitResult , adcResult ,10);					//convert the adc conversion result

	ADCSRA |= 1<<ADSC;							//start the next conversion

}