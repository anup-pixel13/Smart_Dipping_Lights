/*
This code is for receiver which is Car1 which has horn and light installed and receiver too.
*/
// pin 11 is data receiver pin
// pin 12 is used for mode switch when key is on i.e 12 is high then it is behaving as horn model or else it is behaving as pass light model.
// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
int MODE_SWITCH_STATUS = 12;
int LED_SWITCH_POWER_SUPPLY = 1;
int LED_SWITCH_STATUS = 2;
int L1 = 3;
int L2 = 4;
int H1 = 5;
int H2 = 6;
int HORN_SWITCH_POWER_SUPPLY = 7;
int HORN_SWITCH_STATUS = 8;
int HORN = 9;

void setup() 
{
  // put your setup code here, to run once:
  // Initialize ASK Object
  rf_driver.init();

  pinMode(MODE_SWITCH_STATUS, INPUT);
  pinMode(LED_SWITCH_POWER_SUPPLY, OUTPUT);
  pinMode(LED_SWITCH_STATUS, INPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(H1, OUTPUT);
  pinMode(H2, OUTPUT);
  pinMode(HORN_SWITCH_POWER_SUPPLY, OUTPUT);
  pinMode(HORN_SWITCH_STATUS, INPUT);
  pinMode(HORN, OUTPUT);

  digitalWrite(LED_SWITCH_POWER_SUPPLY, HIGH);
  digitalWrite(HORN_SWITCH_POWER_SUPPLY, HIGH);
  
  // Setup Serial Monitor
  //Serial.begin(9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  if(digitalRead(MODE_SWITCH_STATUS) == HIGH)
  {
    //Serial.print("horn Mode");
    //horn model
    if(digitalRead(HORN_SWITCH_STATUS) == HIGH)
    {
      //BUTTON PRESSED
      // Set buffer to size of expected message
      uint8_t buf[12];
      uint8_t buflen = sizeof(buf);
     // Serial.println("hello");
      // Check if received packet is correct size
      if (rf_driver.recv(buf, &buflen))
      {
        // Message received with valid checksum
        //Serial.print("Message Received: ");
        //Serial.println((char*)buf);     
        //in no honking zone so no horn power supply
        digitalWrite(HORN, LOW); 
        delay(300);   
      }
      else
      {
        
        //out of no honking zone
        delay(300);
        //Serial.println("no signal recv");
        digitalWrite(HORN, HIGH);
      }
    }
    else
    {
      //SWITCH OFF
       digitalWrite(HORN, LOW);
    }
    if(digitalRead(LED_SWITCH_STATUS) == HIGH)
    {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      digitalWrite(H1, HIGH);
      digitalWrite(H2, HIGH);
    }
    else
    {
      digitalWrite(L1, LOW);
      digitalWrite(L2, LOW);
      digitalWrite(H1, LOW);
      digitalWrite(H2, LOW);
    }
  }
  else
  {
    //passing light model
    if(digitalRead(LED_SWITCH_STATUS) == HIGH)
    {
      digitalWrite(L1, HIGH);
      digitalWrite(L2, HIGH);
      //BUTTON ON
      // Set buffer to size of expected message
      uint8_t buf[10];
      uint8_t buflen = sizeof(buf);
      //Serial.print("hello");
      // Check if received packet is correct size
      if (rf_driver.recv(buf, &buflen))
      {
        // Message received with valid checksum
        //Serial.print("Message Received: ");
        //Serial.println((char*)buf);     
        //car1 is sending use dipper so turn off H1, H2
        digitalWrite(H1, LOW); 
        digitalWrite(H2, LOW); 
        //delay(1000);  
        delay(4500);//wait for car to go on
      }
      else
      {
        //now can use high beam
        digitalWrite(H1, HIGH); 
        digitalWrite(H2, HIGH);  
      }
    }
    else
    {
      //SWITCH OFF
       digitalWrite(L1, LOW);
       digitalWrite(L2, LOW);
       digitalWrite(H1, LOW);
       digitalWrite(H2, LOW);
    }      
  }
}
