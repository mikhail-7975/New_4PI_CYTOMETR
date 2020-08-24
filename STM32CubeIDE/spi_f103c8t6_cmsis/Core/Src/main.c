#include "stm32f103xb.h"

void SPI1_Init(void)
{
  //Включаем тактирование SPI1 и GPIOA
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPAEN;

  /**********************************************************/
  /*** Настройка выводов GPIOA на работу совместно с SPI1 ***/
  /**********************************************************/
  //PA7 - MOSI
  //PA6 - MISO
  //PA5 - SCK

  //Для начала сбрасываем все конфигурационные биты в нули
  GPIOA->CRL &= ~(GPIO_CRL_CNF5_Msk | GPIO_CRL_MODE5_Msk
                | GPIO_CRL_CNF6_Msk | GPIO_CRL_MODE6_Msk
                | GPIO_CRL_CNF7_Msk | GPIO_CRL_MODE7_Msk);

  //Настраиваем
  //SCK: MODE5 = 0x03 (11b); CNF5 = 0x02 (10b)
  GPIOA->CRL |= (0x02<<GPIO_CRL_CNF5_Pos) | (0x03<<GPIO_CRL_MODE5_Pos);

  //MISO: MODE6 = 0x00 (00b); CNF6 = 0x01 (01b)
  GPIOA->CRL |= (0x01<<GPIO_CRL_CNF6_Pos) | (0x00<<GPIO_CRL_MODE6_Pos);

  //MOSI: MODE7 = 0x03 (11b); CNF7 = 0x02 (10b)
  GPIOA->CRL |= (0x02<<GPIO_CRL_CNF7_Pos) | (0x03<<GPIO_CRL_MODE7_Pos);


  /**********************/
  /*** Настройка SPI1 ***/
  /**********************/

  SPI1->CR1 = 0<<SPI_CR1_DFF_Pos  //Размер кадра 8 бит
    | 0<<SPI_CR1_LSBFIRST_Pos     //MSB first
    | 1<<SPI_CR1_SSM_Pos          //Программное управление SS
    | 1<<SPI_CR1_SSI_Pos          //SS в высоком состоянии
    | 0x04<<SPI_CR1_BR_Pos        //Скорость передачи: F_PCLK/32
    | 1<<SPI_CR1_MSTR_Pos         //Режим Master (ведущий)
    | 0<<SPI_CR1_CPOL_Pos | 0<<SPI_CR1_CPHA_Pos; //Режим работы SPI: 0

  SPI1->CR1 |= 1<<SPI_CR1_SPE_Pos; //Включаем SPI
}

void SPI1_Write(uint16_t data)
{
  //Ждем, пока не освободится буфер передатчика
  while(!(SPI1->SR & SPI_SR_TXE))
    ;

  //заполняем буфер передатчика
  SPI1->DR = data;
}

uint16_t SPI1_Read(void)
{
  SPI1->DR = 0; //запускаем обмен

  //Ждем, пока не появится новое значение
  //в буфере приемника
  while(!(SPI1->SR & SPI_SR_RXNE))
    ;

  //возвращаем значение буфера приемника
  return SPI1->DR;
}

void main()
{
  //ClockInit();

  SPI1_Init();


  for(;;)
  {
    SPI1_Write(0b10101010);

  }
}
