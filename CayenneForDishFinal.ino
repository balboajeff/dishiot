#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>
/*
// WiFi network info.
char ssid[] = "ssid";
char wifiPassword[] = "wifiPassword";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "MQTT_USERNAME";
char password[] = "MQTT_PASSWORD";
char clientID[] = "CLIENT_ID";
*/
//start
// WiFi network info.
char ssid[] = "sparkfun-workshop";
char wifiPassword[] = "sparkfun";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "eae4d0e0-25fc-11e7-b2af-55ba5adcb0d5";
char password[] = "d18727aafc2c3afb77eef8f47a00e1aec259166c";
char clientID[] = "72141340-c8ba-11e7-b67f-67bba9556416";
//finish
unsigned long lastMillis = 0;
int led=LOW;
boolean doorPosition=0;
void setup() {
  pinMode(5,OUTPUT);
  pinMode(4, INPUT_PULLUP);
  Serial.begin(9600);
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();
doorPosition=digitalRead(4);
  //Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
  if (millis() - lastMillis > 3000) {
    lastMillis = millis();
    //Write data to Cayenne here. This example just sends the current uptime in milliseconds.
    Cayenne.virtualWrite(0, lastMillis);
    Cayenne.virtualWrite(4, doorPosition);
    
    //Some examples of other functions you can use to send data.
    //Cayenne.celsiusWrite(1, 22.0);
    //Cayenne.luxWrite(2, 700);
    //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
  }
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
if (request.channel = 5)
  {
    String value;
    value = (String)getValue.asString();

    if (value == "1")
    {
      digitalWrite(5, HIGH);
      led=HIGH;
    }
    else
    {
      digitalWrite(5, LOW);
      led=LOW;
    }
}
}
