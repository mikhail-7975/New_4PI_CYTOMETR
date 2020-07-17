//синий
//Реализовать:
//сигнал о начале записи+
//отправку сообщений по SPI+
//получение сообщений по SPI+
//отправка сообщений на ПК+
#include <SPI.h>
#include <STM32ADC.h>

STM32ADC myADC(ADC1); 
uint8 pin = PA0; 

#define ADC_CS PB6 //Chip Select for AD7450 ADC
#define DAC_CS PB7 //Chip Select for MCP4921 DAC
#define SAMPLE_Count 1000// Number of samples
#define EMPTY_BUFFER 0
#define FULL_BUFFER 1


#define BEGIN_READING_INTERUPT_PIN PA3
#define BUTTON_INTERUPT_PIN PA2

/*void setupSPI() {
  // Setup SPI 1
  SPI.begin(); //Initialize the SPI_1 port.
  SPI.setBitOrder(MSBFIRST); // Set the SPI_1 bit order
  SPI.setDataMode(SPI_MODE0); //Set the  SPI_2 data mode 0
  SPI.setClockDivider(SPI_CLOCK_DIV16);      // Slow speed (72 / 16 = 4.5 MHz SPI_1 speed)
  pinMode(SPI1_NSS_PIN, OUTPUT);
}*/

void setupStartReadingSignal() {
  pinMode(BEGIN_READING_INTERUPT_PIN, OUTPUT);
  digitalWrite(BEGIN_READING_INTERUPT_PIN, LOW);
}

/*uint16_t messaging(uint16_t message) {
   digitalWrite(SPI1_NSS_PIN, LOW); // manually take CSN low for SPI_1 transmission
  uint16_t data = SPI.transfer((uint16_t)message); //Send the HEX data 0x55 over SPI-1 port and store the received byte to the <data> variable.
  digitalWrite(SPI1_NSS_PIN, HIGH); // manually take CSN high between spi transmissions
  return data;
}*/

String messageParser(uint16_t msg) {
  switch (msg) {
    case 1:
      Serial.println("get message \"1\", all correct");
      return "All correct";
      break;
    case 2:
      Serial.println("get message \"2\", some problems");
      return "some problems";
      break;
    default:
      break;
  }
}

void SendSignal_StartReading() {
  digitalWrite(BEGIN_READING_INTERUPT_PIN, HIGH);
  digitalWrite(BEGIN_READING_INTERUPT_PIN, LOW);
  //digitalWrite(BEGIN_READING_INTERUPT_PIN, LOW);
}

void setupADC() {
  myADC.calibrate();
  myADC.setSampleRate(ADC_SMPR_1_5);
  myADC.setPins(&pin, 0);  
  myADC.setContinuous();
  myADC.startConversion();
}

void setup() {
  //setupSPI();
  
  
  setupStartReadingSignal();
  Serial.begin(115200); 
}

volatile uint16_t dataBuffer[SAMPLE_Count];

void ReadDataFromADC() {
  for(int i=0; i<SAMPLE_Count; i++) {
    //чтение данных с АЦП
    dataBuffer[i]=myADC.getData();    
  }
  //state = FULL_BUFFER;
}

void SERIAL_Write() {
  //if(state != FULL_BUFFER)
    //return;
  //while((Serial.available() > 0) && Serial.read() != 's');  
  Serial.print('<');
  Serial.print('t');
  Serial.print('>'); 
  Serial.print(' ');
  for(int i=0; i<SAMPLE_Count; i++) {
    Serial.print(dataBuffer[i]);
    Serial.print(' ');
  }
  Serial.println();
  //state = EMPTY_BUFFER;
  //ParticleNumber = ParticleNumber + 1;
}

void loop() {
  //uint16_t inp = 0;
  //Serial.println("ready");
  
  /*while(inp < 1000) {
    inp = myADC.getData();
  }
  Serial.println("start");
  SendSignal_StartReading();
  ReadDataFromADC();
  SERIAL_Write();*/
  digitalWrite(BEGIN_READING_INTERUPT_PIN, HIGH);
  //delay(1);
  digitalWrite(BEGIN_READING_INTERUPT_PIN, LOW);
  //delay(1);
  
}
