#include <SPI.h>//SPI Include
#include <STM32ADC.h>//Internal ADC Include

STM32ADC myADC(ADC1); 
uint8 pin = PA0; 

//#define ADC_CS PB6 //Chip Select for AD7450 ADC
#define DAC_CS PB7 //Chip Select for MCP4921 DAC
#define INTER PA1 //Interupt pin
//#define Trig_Pin PA3
int trigg_level = 0;
#define SAMPLE 5000// Number of samples
volatile int num = 0;
volatile int ADC_FINISH = 0;

volatile uint16_t buff[SAMPLE];

void CYC_BUFF()
{
  detachInterrupt(INTER);
  for(volatile int i=0;i<SAMPLE;i++)
  {
    buff[i]=myADC.getData();    
  }
  ADC_FINISH = 1;
  num++;
  
}

void SERIAL_WRITE()
{
  if(ADC_FINISH == 1)
  {
    for(int i=0;i<SAMPLE;i++)
    {
      Serial.print(buff[i]);
      Serial.print(' ');
    }
    Serial.println();
    ADC_FINISH = 0;
  }
}

void NUM_SERIAL_WRITE()
{
  if(ADC_FINISH == 1)
  {
    Serial.print('<');
    Serial.print(num);
    Serial.print('>'); 
    Serial.print(' ');
    for(int i=0;i<SAMPLE;i++)
    {
      Serial.print(buff[i]);
      Serial.print(' ');
    }
    Serial.println();
    ADC_FINISH = 0;
  }
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
  SPI.transfer16(dac_data);
  digitalWrite(DAC_CS,HIGH);
}

String SERIAL_READ()
{
  String in_buff = "";
  char inChar;
  while(Serial.available()>0)
  {
    inChar = Serial.read();
    if(inChar!='\n')
    {
      in_buff += inChar;
    }
  }
  return in_buff;
}

String HOLD_SERIAL_READ()
{
  String in_buff = "";
  char inChar;
  while(in_buff == "")
  {
    while(Serial.available()>0)
    {
      inChar = Serial.read();
      if(inChar!='\n')
      {
        in_buff += inChar;
      }
    }
  }
  return in_buff;
}

void COMAND_CONTROLLER()
{
  Serial.println("Welcome to the Tracer-module interface!");
  Serial.println("Select comand:");
  Serial.println("Gain");
  Serial.println("Start Draw");
  Serial.println("Start Tracer");
  Serial.println("Stop");
  Serial.println("Reset");
  //Serial.println("Trigger Level");

  String in_buff;
  in_buff = HOLD_SERIAL_READ();
  {
    if(in_buff=="Gain")
    {
      Serial.println("Enter value (0-4095)");
      in_buff = HOLD_SERIAL_READ();
      int val = in_buff.toInt();
      DAC_W(0,1,1,1,val);
      in_buff = "";
      Serial.println("Gain Set!");
    }
    if(in_buff=="Start Draw")
    {
      while(SERIAL_READ()!="Stop")
      {
        CYC_BUFF();
        SERIAL_WRITE();
      }
    }

    if(in_buff=="Start Tracer")
    {
      while(SERIAL_READ()!="Stop")
      {
        NUM_SERIAL_WRITE();
        attachInterrupt(INTER, CYC_BUFF,RISING);
      }
    }

    if(in_buff=="Reset")
    {
      num = 0;
      Serial.println("Num Reseted!");  
    }
  }
}

void setup() 
{
  myADC.calibrate();
  myADC.setSampleRate(ADC_SMPR_7_5);
  myADC.setPins(&pin, 1);  
  myADC.setContinuous();
  myADC.startConversion();
  
  afio_cfg_debug_ports(AFIO_DEBUG_SW_ONLY); // PB3 free
  afio_remap(AFIO_REMAP_SPI1);

  gpio_set_mode (GPIOB, 3, GPIO_AF_OUTPUT_PP);
  gpio_set_mode (GPIOB, 4, GPIO_INPUT_FLOATING);
  gpio_set_mode (GPIOB, 5, GPIO_AF_OUTPUT_PP);
  
  // Setup SPI 1
  SPI.begin(); //Initialize the SPI_1 port.
  SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  SPI.setDataMode(SPI_MODE0); //Set the  SPI_1 data mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV4);      // Normal speed (72 / 4 = 18 MHz SPI_1 speed)
  
  //pinMode(ADC_CS, OUTPUT);
  pinMode(DAC_CS, OUTPUT);
  //pinMode(Trig_Pin, OUTPUT);
  pinMode(INTER, INPUT_PULLDOWN);
  //attachInterrupt(INTER, CYC_BUFF, RISING);
  
  Serial.begin(115200);
}

void loop() 
{
  COMAND_CONTROLLER();
}
