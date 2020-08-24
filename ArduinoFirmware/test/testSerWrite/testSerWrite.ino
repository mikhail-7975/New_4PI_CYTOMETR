#define POINT_COUNT 1000
uint8_t *arr;

void setup() {
  arr = (uint8_t*)malloc(sizeof(uint8_t) * POINT_COUNT);
  for(int i = 0; i < POINT_COUNT; i++) {
    uint16_t d = i % 3;
    memcpy((arr + i * sizeof(uint8_t)), &d, sizeof(uint16_t));
  }
  
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.write(arr, sizeof(uint8_t) * POINT_COUNT);
  delay(1000);
}
