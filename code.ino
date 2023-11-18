// Include the required libraries
#include <DHT.h>
#include <MQ135.h>

#define POWER_PIN  7

// Define the pins for the sensors
const int waterDetectionSensorPin = A5;
const int dht22SensorPin = 2;
const int soilMoistureSensorPin = A1;
const int ldrSensorPin = A0;
const int relayPin = 6;
const int mq135SensorPin = A3;

// Create an instance of the DHT22 sensor
DHT dht(dht22SensorPin, DHT22);

// Create an instance of the MQ135 sensor
MQ135 mq135(mq135SensorPin);

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Set the pin modes
  pinMode(waterDetectionSensorPin, INPUT);
  pinMode(relayPin, OUTPUT);
  
  // Initialize the DHT22 sensor
  dht.begin();

  pinMode(POWER_PIN, OUTPUT);   // configure D7 pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
}

void loop() {
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON

  // Read the sensor values
  int waterDetectionSensorValue = digitalRead(waterDetectionSensorPin);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int soilMoistureSensorValue = analogRead(soilMoistureSensorPin);
  int ldrSensorValue = analogRead(ldrSensorPin);
  int mq135SensorValue = analogRead(mq135SensorPin);
  
   // Send data to NodeMCU via Serial
  Serial.println(int(temperature));
  Serial.println(int(humidity));
  Serial.println(soilMoistureSensorValue);
  Serial.println(ldrSensorValue);
  Serial.println(waterDetectionSensorValue);
  Serial.println(mq135SensorValue);
  

  // Check the conditions for the water pump to work
  if (temperature >= 15 && temperature <= 29 && humidity >= 40 && ldrSensorValue >= 0 && ldrSensorValue <= 200 && soilMoistureSensorValue >= 100 && soilMoistureSensorValue <= 500) {
    digitalWrite(relayPin, HIGH); // Activate the relay module
    Serial.println(1);
    delay(3000);
    digitalWrite(relayPin, LOW); // Deactivate the relay module
  } else {
    digitalWrite(relayPin, LOW); // Deactivate the relay module
    Serial.println(0);
  }
  
  // Wait for some time before taking the next sensor readings
  delay(3000);
}
