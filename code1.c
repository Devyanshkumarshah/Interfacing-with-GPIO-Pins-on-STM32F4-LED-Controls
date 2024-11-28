#include<stdint.h>

int main(void)
{
  uint32_t *pclkctrlReg = (uint32_t*)0x40023830 ; //this pointer is used to store address of Clock Control Registor
  uint32_t *pPortDModeReg = (uint32_t*)0x40020C0 ; //used to store address of Mode Registor of port D(Wheather input or output)
  uint32_t *pPortDoutReg = (uint32_t*)0x40020C14 ; //output Data Registor 

  //1. enable the clock for GPOID Perifheral in the AHB1ENR Set the 3rd Bit pointer 
  *pclkctrlReg = *pclkctrlReg | (1<<3) ;

  //2. Config the Mode of the IO pin as output

  // a. clear the 24th and 25th pin bit position
  *pPortDModeReg = *pPortDModeReg & ~(3<<24) ; //Binary value of 3 is 1 1 so it will clear both the 24th and 25th bit position 

  // b. Make the 25th and 24th bit position as 0 and 1 respectively  (set)
  *pPortDModeReg = *pPortDModeReg | (1<<24) ; 

  //3. Set the 12th bit position of the output Data Registor to make IO pin 12 to toggle
  
  while (1) //this make a infinite loop
  {
      *pPortDoutReg = *pPortDoutReg | (1<<12) ; //this will make the LED High 

      //introduce small Human observable delay 
      //This loop executes for 10k times

      for(uint32_t i = 0; i<10000; i++);

      //turn off the LED
      *pPortDoutReg = *pPortDoutReg & ~(1<<12); //this will make the LED Low 
      
      for(uint32_t i=0; i<10000; i++);

  }





}