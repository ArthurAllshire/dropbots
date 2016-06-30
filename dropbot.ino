#include <ZumoMotors.h>
#include <Pushbutton.h>
#include <QTRSensors.h>
#include <ZumoReflectanceSensorArray.h>
#include <math.h>
 
#define LED 13

#define FULL_SPEED 400
#define MAX_SPEED 180
#define SIN_MOVEMENT_CYCLE_TIME 3
#define MAX_DELTA_SPEED 120

ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); 
 
#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];
 
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);
double start_time;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, HIGH);
  start_time = millis();
  motors.setSpeeds(0.0, 0.0);
}

void loop() {
  motors.setSpeeds(MAX_SPEED-MAX_DELTA_SPEED/2+(sin((millis()-start_time)/1000))/PI*SIN_MOVEMENT_CYCLE_TIME*MAX_DELTA_SPEED/2,
                   MAX_SPEED-MAX_DELTA_SPEED/2-(sin((millis()-start_time)/1000))/PI*SIN_MOVEMENT_CYCLE_TIME*MAX_DELTA_SPEED/2);
  sensors.read(sensor_values);
  // the indeces for the sensor values start from 0 at the leftmost sensor
  // 2000 means no reflection detected (no table sensed)
  for(int x = 0; x<6; x++) {
    Serial.print("x: ");
    Serial.print(x, 1);
    Serial.print(" val: ");
    Serial.print(sensor_values[x]);
    Serial.println("");
  }
  Serial.println("");
}
