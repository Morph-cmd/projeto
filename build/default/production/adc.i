# 1 "adc.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.46\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "adc.c" 2
# 24 "adc.c"
# 1 "./adc.h" 1
# 22 "./adc.h"
 void adcInit(void);
 int adcRead(void);
# 24 "adc.c" 2

# 1 "./pic18f4520.h" 1
# 25 "adc.c" 2


 void adcInit(void)
{
 (((*(volatile __near unsigned char*)0xF92)) |= (1<<0));

 (*(volatile __near unsigned char*)0xFC2) = 0b00000101;
 (*(volatile __near unsigned char*)0xFC1) = 0b00001110;
 (*(volatile __near unsigned char*)0xFC0) = 0b10101010;
}

int adcRead(void)
{
 unsigned int ADvalor;
 (*(volatile __near unsigned char*)0xFC2) |= 0b00000010;

 while((((*(volatile __near unsigned char*)0xFC2)) & (1<<1)));

 ADvalor = (*(volatile __near unsigned char*)0xFC4) ;
 ADvalor <<= 8;
 ADvalor += (*(volatile __near unsigned char*)0xFC3);
 return ADvalor;
}
