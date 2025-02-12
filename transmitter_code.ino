/*
This code is for transmitter which is Car2 which has transmitter and ldr and also the no-horn sign.
*/
// pin 12 is data transmission pin
// pin 11 is use for mode switch when key is on i.e. 11 is high then it is behaving as signal or else it is behaving as car for passing light model
// Include RadioHead Amplitude Shift Keying Library
#include <RH_ASK.h>
// Include dependant SPI Library 
#include <SPI.h> 
 
// Create Amplitude Shift Keying Object
RH_ASK rf_driver;
int MODE_SWITCH_STATUS = 11;
int LDR_POWER_SUPPLY = 10;
int LDR_LIGHT_DATA_PIN = A0;
int LDR_LIGHT_DATA_VALUE = 0;

void(* resetFunc) (void) = 0;

void setup() 
{
  // put your setup code here, to run once:
  // Initialize ASK Object
  rf_driver.init();

  pinMode(MODE_SWITCH_STATUS, INPUT);
  pinMode(LDR_POWER_SUPPLY, OUTPUT);

  digitalWrite(LDR_POWER_SUPPLY, HIGH);
  //Serial.begin(9600);
}

void loop() 
{
  if(digitalRead(MODE_SWITCH_STATUS) == HIGH)
  {
    //SIGNAL NO HONK MODE
    const char *msg = "No Honk Zone";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    //delay(1000);
    //Serial.println("on");
  }
  else
  {
    //Serial.println("off");
    // car mode i.e passig light model
    LDR_LIGHT_DATA_VALUE = analogRead(LDR_LIGHT_DATA_PIN);
   // Serial.println(LDR_LIGHT_DATA_VALUE);
   // delay(1000);
    if(LDR_LIGHT_DATA_VALUE >= 750)
    {
      // light is incident on driver so transmit use dipper
    const char *msg = "Use Dipper";
    rf_driver.send((uint8_t *)msg, strlen(msg));
    rf_driver.waitPacketSent();
    //delay(1000);
    resetFunc();
    }
  }
}
