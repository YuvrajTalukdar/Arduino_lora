#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
//band 2
//567000000 upper range
//363000000 lower stable
//band 3
//189000000 upper
//12100000 lower

//more than 50 sf upper
//7 sf lower

long int frequencies[5] = {433000000, 121000000, 189000000,362000000,567000000};
//controls the current frequency index in the array
int indexFreq = 0;
int sf_value=7;

//change the frequency of Lora, the new frequency will be according to the variable "indexFreq" that will pick up in the array the new frequency<br>
void changeFrequency()
{
  if (!LoRa.begin(frequencies[indexFreq]))
  { 
    //display.drawString(0, 0, "Starting LoRa failed!");
    //display.display();
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.enableCrc();
  digitalWrite(13, LOW); //turns off the frequency change indicator LED
}

void changeSF()
{
  LoRa.setSpreadingFactor(sf_value);
  LoRa.enableCrc();
  digitalWrite(13, LOW); //turns off the frequency change indicator LED 
}

//starting 
int counter = 0;
int Senderled = 5;
int Errorled = 6;


void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("LoRa Sender");
  Serial.println("Sending mode is ON");
  pinMode(Senderled, OUTPUT);
  pinMode(Errorled, OUTPUT);
  digitalWrite(Senderled, LOW);
  digitalWrite(Errorled, LOW);

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    digitalWrite(Errorled, HIGH);
    delay(2000);
    while (1);
  }
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
  digitalWrite(Senderled, LOW);
  digitalWrite(Errorled, LOW);

  Serial.print("Sending packet: ");
  Serial.println(counter);

  LoRa.beginPacket();
  LoRa.print("Hello From Arduino ");
  Serial.println("Hello From Arduino...");
  digitalWrite(Senderled, HIGH);
  delay(500);
  digitalWrite(Senderled, LOW);
  LoRa.print(counter);
  LoRa.endPacket();

  counter++;

  delay(1000);
}