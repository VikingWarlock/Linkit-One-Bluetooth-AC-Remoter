#include <LTask.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "RemoteGATT.h"
#include "RemoterService.h"
#include <LGATTUUID.h>
#include "midea.h"

#define PWM_PIN 3

VKIRSender sender;
MideaIR remote_control(&sender);
DHT_Unified dht(10, DHT22);
uint32_t delayMS;
float temperature=-1;
float humidity=-1;
RemoterService uart;
RemoteGATT abc;
uint32_t currentDelay;
uint32_t cmdDelay;

void setup()
{

  pinMode(PWM_PIN,OUTPUT);

  // Serial.begin(9600);

  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  if (!LGATTServer.begin(2, &uart,&abc))
  {
     APP_LOG("[FAILED] GATTS begin");
  }
  else
  {
     APP_LOG("GATTS begin");
  }
  delay(2000);
}

void handleDHT22(sensors_event_t event){
if (isnan(event.temperature)) {
    // Serial.println("Error reading temperature!");
  }
  else {
    temperature=event.temperature;
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    // Serial.println("Error reading humidity!");
  }
  else {
    humidity=event.relative_humidity;
  }
  if(humidity>0&&temperature>0){
    Serial.print("Temperature:");
    Serial.print(temperature);
    Serial.print(",Humidity:");
    Serial.print(humidity);
    Serial.println("%");
  }
}


void loop()
{
  // Make sure we are connected, and dump the response content to Serial
  delay(15);
  currentDelay+=15;
  if(currentDelay>delayMS){
	currentDelay=0;
	sensors_event_t event;  
  	dht.temperature().getEvent(&event);
  	handleDHT22(event);
  	uart.setTempData(temperature,humidity);
  }

  LGATTServer.handleEvents();
  if(abc.hasCmd()){
   	ACState *state = abc.getState();
      if(state->power){
      	remote_control.setMode(state->mode);
      	// Serial.println(state->mode);
      	remote_control.setSpeedFan(state->fan);
      	// Serial.println(state->fan);
      	remote_control.setTemperature(state->temp);
      	// Serial.println(state->temp);
		remote_control.turnON();
      }else{
   		remote_control.turnOFF();
      }
  }

}

