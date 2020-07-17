#include "stm32f1xx.h"

void PortInit(void)
{
  RCC->APB2ENR |= RCC_APB2ENR_IOPBEN; //Включаем тактирование порта GPIOB

  GPIOB->CRH &= ~(GPIO_CRH_MODE12 | GPIO_CRH_CNF12); //для начала все сбрасываем в ноль

  //MODE: выход с максимальной частотой 2 МГц
  //CNF: режим push-pull
  GPIOB->CRH |= (GPIO_CRH_MODE12) | (0x00 << GPIO_CRH_CNF12_Pos);
}

void PortSetHi(void)
{
  //GPIOB->ODR |= GPIO_ODR_ODR12;//(1<<12);
	GPIOB->BSRR = (1 << 12);
}

void PortSetLow(void)
{
  //GPIOB->ODR &= ~GPIO_ODR_ODR12;
	GPIOB->BRR = (1 << 12);
}

void main()
{
  int i;
  PortInit();

  for(;;)
  {
	  GPIOB->BSRR = GPIO_BSRR_BS12;
	  GPIOB->BRR = GPIO_BSRR_BS12;
  }
}
