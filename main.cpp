#include <WiFi.h>
#include "ThingSpeak.h"
#define RELAY_PIN    17 // ESP32 pin GPIO17 that connects to relay
#define THRESHOLD 50   // => CHANGE YOUR THRESHOLD HERE
int moisture,sensor_analog;
const int sensor_pin = 34;  /* Soil moisture sensor O/P pin */

const char* ssid = "REPLACE_WITH_YOUR_SSID";   // your network SSID (name) 
const char* password = "REPLACE_WITH_YOUR_PASSWORD";   // your network password

unsigned long myChannelNumber = X;
const char * myWriteAPIKey = "XXXXXXXXXXXXXXXX";

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 30000;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  // set the ADC attenuation to 11 dB (up to ~3.3V input)
  analogSetAttenuation(ADC_11db);
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    
    // Connect or reconnect to WiFi
    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Attempting to connect");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }

  sensor_analog = analogRead(sensor_pin);
  moisture = ( 100 - ( (sensor_analog/4095.00) * 100 ) );

  if (moisture < THRESHOLD) {
    Serial.print("The soil moisture is DRY => activate pump");
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    Serial.print("The soil moisture is WET => deactivate the pump");
    digitalWrite(RELAY_PIN, LOW);
  }

  Serial.print(" (");
  Serial.print(moisture);
  Serial.println("%");
  Serial.println(")");
  int x = ThingSpeak.writeField(myChannelNumber, 1, moisture, myWriteAPIKey);
    //uncomment if you want to get temperature in Fahrenheit
    //int x = ThingSpeak.writeField(myChannelNumber, 1, temperatureF, myWriteAPIKey);

    if(x == 200){
      Serial.println("Channel update successful.");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    lastTime = millis();
  }
  delay(1000);
}
