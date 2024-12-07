// Write a Program which reads the status of the pin PA0. If the status of the pin PA0 is low then turn off the onboard LED(PD12) and if the PA0 is High then turn on the LED 
//change the status of the pin PA0 manually by connecting between GND and VCC points of the Board
#include<stdint.h>

int main(void) 
{
  uint32_t *pclkctrlReg = (uint32_t*)0x4002380 ;  //this register is used to enable the clock of the peripheral
  uint32_t *pPortDModeReg = (uint32_t*)0x40020C00; //this register is used to decide the output or input of the peripheral
  uint32_t *pPortDoutReg = (uint32_t*)0x40020C14; //this pin is used to Write in the pin

  uint32_t *pPortAModeReg = (uint32_t*)0x40020000; //this pin is used to decide wheather the pin is in output or input
  uint32_t *pPortAInReg = (uint32_t*)0x40020000 + 0x10; //this pin is used to read the pin

  //1. Enabling the clock of the GPIOD, GPIOA peripheral in the AHB1ENR

  *pclkctrlReg = *pclkctrlReg | (1<<3); //3rd bit position is set to 1 for GPIO D peripheral
  *pclkctrlReg = *pclkctrlReg | (1<<0); //0th bit position is set to 1 for GPIO A peripheral

  //2. Configure PD12 as ouput

  *pPortDModeReg = *pPortDModeReg & ~(3<<24) ; //clear the 24 and 23 bit position 
  *pPortDModeReg = *pPortDModeReg | (1<<24) ; //set the bit position as 1 

  //3. Configure PA0 as input mode(GPIO A Mode Register)

  *pPortAModeReg = *pPortAModeReg & ~(3<<0);

  while (1)
  {
    //read the pin status of the pin PA0(GPIOA input Data Register0)
   uint8_t pinstatus = (uint8_t)(*pPortAInReg & 0x1);// Zero out all the bit position except bit position 0

   if(pinstatus)
   {
    //turn on the LED
    *pPortDoutReg = *pPortDoutReg | (1<<12);
   }
   else
   {
    //turn off the LED
    *pPortDoutReg = *pPortDoutReg & ~(1<<12);
   }
  }
  }
