/*//чёрный
//Реализовать:
//начало записи по прерыванию
//приём сообщений по SPI
//ответ на сообщения по SPI

#include <SPI.h>//SPI Include
#include <STM32ADC.h>//Internal ADC Include

STM32ADC myADC(ADC1); 
uint8 pin = PA0; 

#define ADC_CS PB6 //Chip Select for AD7450 ADC
#define DAC_CS PB7 //Chip Select for MCP4921 DAC
#define StartReading_INTERUPT_PIN PA3 //Interupt pin
#define SAMPLE_Count 1000// Number of samples
#define EMPTY_BUFFER 0
#define FULL_BUFFER 1


int ParticleNumber = 0;
volatile int state = 0;

String in_buff = "";

volatile uint16_t dataBuffer[SAMPLE_Count];

void ReadDataFromADC()
{
  detachInterrupt(StartReading_INTERUPT_PIN);
  if (state == FULL_BUFFER) 
    return;
  for(volatile int i=0; i<SAMPLE_Count; i++) {
    //чтение данных с АЦП
    dataBuffer[i]=myADC.getData();    
  }
  state = FULL_BUFFER;
  attachInterrupt(StartReading_INTERUPT_PIN, ReadDataFromADC, RISING);
}

void SERIAL_Write()
{
  if(state != FULL_BUFFER)
    return;
  //while(Serial.read() != 's');  
  Serial.print('<');
  Serial.print(ParticleNumber);
  Serial.print('>'); 
  Serial.print(' ');
  for(int i=0; i<SAMPLE_Count; i++) {
    Serial.print(/*dataBuffer[i]*/2);
    Serial.print(' ');
  }
  Serial.println();
  state = EMPTY_BUFFER;
  ParticleNumber = ParticleNumber + 1;
}

void DAC_W(boolean AB, boolean BUF, boolean GA, boolean STDN, int val )// Writes DAC value on MCP4921
/**
  AB = 0/1 - A chanel write/B chanel write
  BUF = 0/1 - Unbuffered/Buffered
  GA = 0/1 - 2x Gain Out/1x Gain Out
  SHDN = 0/1 -Disabled/Enabled
  val - value of output 0-4095
 */
  
{
  int dac_data = 0;
  digitalWrite(DAC_CS,LOW);
  dac_data = (AB << 15) + (BUF << 14) + (GA << 13) + (STDN << 12) + (val&0x0FFF); // Command register, see Datasheet page 18
  //SPI.transfer16(dac_data);
  digitalWrite(DAC_CS,HIGH);
}

void SERIAL_Read()
{
  while(Serial.available()>0)
  {
    char inChar = Serial.read();
    in_buff += inChar;
    if(inChar=='\n')
    {
      int val = in_buff.toInt();
      DAC_W(0,1,1,1,val);
      //Serial.println(val);//Debug information
      in_buff = "";
    }
  }
}

void setupSPI(void)
{
  // The clock value is not used
  // SPI1 is selected by default
  // MOSI, MISO, SCK and NSS PINs are set by the library
  SPI.beginTransactionSlave(SPISettings(4500000, MSBFIRST, SPI_MODE0, DATA_SIZE_8BIT));
}

void setup() 
{
  myADC.calibrate();
  myADC.setSampleRate(ADC_SMPR_1_5);
  myADC.setPins(&pin, 0);  
  myADC.setContinuous();
  myADC.startConversion();
  
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY); // PB3 free
  afio_remap(AFIO_REMAP_SPI1);

  gpio_set_mode (GPIOB, 3, GPIO_AF_OUTPUT_PP);
  gpio_set_mode (GPIOB, 4, GPIO_INPUT_FLOATING);
  gpio_set_mode (GPIOB, 5, GPIO_AF_OUTPUT_PP);
  
  // Setup SPI 1
  /*SPI.begin(); //Initialize the SPI_1 port.
  SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  SPI.setDataMode(SPI_MODE0); //Set the  SPI_1 data mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV4);      // Normal speed (72 / 4 = 18 MHz SPI_1 speed)
  */
  SPI.beginTransactionSlave(SPISettings(4500000, MSBFIRST, SPI_MODE0, DATA_SIZE_8BIT));
  
  pinMode(ADC_CS, OUTPUT);
  pinMode(DAC_CS, OUTPUT);
  pinMode(StartReading_INTERUPT_PIN, INPUT_PULLDOWN);
  
  
  Serial.begin(115200);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  SERIAL_Write();
}
