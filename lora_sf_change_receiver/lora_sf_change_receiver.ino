//LoRA Reciever 

#include <SPI.h>
#include <LoRa.h>

//array of frequencies valid for the application to change
long int frequencies[5] = {433000000, 12100000, 189000000,362000000,567000000};
//controls the current frequency index in the array 431182800
int indexFreq = 0;
int sf_value=7;

void changeFrequency()
{
  if (!LoRa.begin(frequencies[indexFreq]))
  { 
    //display.drawString(0, 0, "Starting LoRa failed!");
    //display.display();
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  //LoRa.enableCrc();
  LoRa.disableCrc();
  digitalWrite(13, LOW); //turns off the frequency change indicator LED
}

void changeSF()
{
  LoRa.setSpreadingFactor(sf_value);
  //LoRa.enableCrc();
  LoRa.disableCrc();
  digitalWrite(13, LOW); //turns off the frequency change indicator LED 
}


void setup() {
  pinMode(LED_BUILTIN,OUTPUT);
  Serial.begin(9600);
  while (!Serial);


  Serial.println("LoRa Receiver");
  delay(2500);
  

  if (!LoRa.begin(433E6)) {
  Serial.println("Starting LoRa failed!");

    while (1);
    
  }
  Serial.println("LoRa is working....");
  Serial.println("Recieving mode is ON");

  
}

bool frequency_changed=false;
bool sf_changed=false;
void loop() {
  
  if(!frequency_changed)
  {
    changeFrequency();
    frequency_changed=true;
  }
  if(!sf_changed)
  {
    changeSF(); 
    sf_changed=true;
  }
  
  int packetSize = LoRa.parsePacket();
  if (packetSize) {

    Serial.println("Received packet '");
   
  
    while (LoRa.available())
    {
      Serial.print((char)LoRa.read());
    }

    Serial.println("' with Recieved Signal Strength Indicator ");
    Serial.println(LoRa.packetRssi());
    delay(2000);
  
  digitalWrite(LED_BUILTIN,HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN,LOW);
  }
}