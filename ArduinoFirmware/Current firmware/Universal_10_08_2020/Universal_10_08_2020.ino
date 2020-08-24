#include <SPI.h>//SPI Include
#include <STM32ADC.h>//Internal ADC Include

STM32ADC myADC(ADC1); 
uint8 pin = PA0; 

#define SAMPLE 5000// Number of samples
#define DAC_CS PB7 //Chip Select for MCP4921 DAC
#define Trigger_Pin PA3//Trigger pin for signaling
#define Interrupt_Pin PA1 //Interupt pin
  /*
   Standart code table:
   0x01XXXX - Gain setting, XXXX - Value 0x0000 - 0x0FFF (0 - 4095)
   0x10XXXX - Trigger level setting, XXXX - Value 0x0000 - 0x0FFF (0 - 4095)
   0x02 - Start Streaming mode sending debug traces (without external interrupt from tigger)
   0x03 - Start Tracer mode sending traces (with external interrupt from tigger)
   0x04 - Sart Trigger mode (sending trigger impulse)
   0x05 - Stop Stream\Tracer\Trigger mode
   0x06 - Reset Number of trace
   
   */
   
uint8_t Gain = 0x01;
uint8_t Trigger_Level = 0x10;
uint8_t Start_Stream = 0x02;
uint8_t Start_Trace = 0x03;
uint8_t Start_Trigger = 0x04;
uint8_t Stop = 0x05;
uint8_t Reset = 0x06;
uint16_t Trigger = 0;


volatile int num = 0;//Number of trace
volatile uint8_t ADC_FINISH = 0;//Flag of End of conversation
volatile uint16_t buff[SAMPLE];//Buffer of trace

void CYC_BUFF()
{
  detachInterrupt(Interrupt_Pin);
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
  uint16_t dac_data = 0;
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
  String in_buff = "";
  in_buff = HOLD_SERIAL_READ();
  {
    if(in_buff[0] == Gain)
    {
      uint16_t val = (in_buff[1] << 8) + in_buff[2];
      DAC_W(0,1,1,1,val);
      in_buff = "";
    }
    
    if(in_buff[0] == Start_Stream)
    {
      String inc = SERIAL_READ();
      while(inc[0] != Stop)
      {
        CYC_BUFF();
        SERIAL_WRITE();
        inc = SERIAL_READ();
      }
    }

    if(in_buff[0] == Start_Trace)
    {
      String inc = SERIAL_READ();
      while(inc[0] != Stop)
      {
        NUM_SERIAL_WRITE();
        attachInterrupt(Interrupt_Pin, CYC_BUFF, RISING);
        inc = SERIAL_READ();
      }
    }

    if(in_buff[0] == Reset)
    {
      num = 0;
      in_buff = "";
    }

     if(in_buff[0] == Trigger_Level)
    {
      Trigger = (in_buff[1] << 8) + in_buff[2];
      in_buff = "";
    }

    if(in_buff[0] == Start_Trigger)
    {
      int state = 0;
      String inc = SERIAL_READ();
      while(inc[0] != Stop)
      {
        state = 0;
        while(state < 100)
        {
          if(myADC.getData()>Trigger_Level)
          {
            digitalWrite(Trigger_Pin, HIGH);
            state = 100;
          }
          else
          {
            digitalWrite(Trigger_Pin, LOW);
            state++; 
          }
        }
      }
      in_buff = "";
    }

    
  }
}

void setup() 
{
  myADC.calibrate();
  myADC.setSampleRate(ADC_SMPR_1_5);
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
  
  
  pinMode(DAC_CS, OUTPUT);
  pinMode(Trigger_Pin, OUTPUT);
  pinMode(Interrupt_Pin, INPUT_PULLDOWN);
  attachInterrupt(Interrupt_Pin, CYC_BUFF, RISING);
  
  Serial.begin(115200);
}

void loop() 
{
  COMAND_CONTROLLER();
}
