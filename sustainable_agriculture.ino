#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

int temperature, humidity, soilMoisture, ldr, waterLevel, mq135, relayStatus;

// Set the credentials for your Wi-Fi network
const char* ssid = "";
const char* password = "";

// Set the credentials for your Firebase project
const char* firebaseHost = "sustainable-agriculture-cc15d-default-rtdb.firebaseio.com/";
const char* firebaseAuth = "rocZvr9ZDm08LWskn5nVplyxatmYlNPg9hGFJK4P";

// Initialize Firebase
FirebaseData firebaseData;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  // Connect to Firebase
  Firebase.begin(firebaseHost, firebaseAuth);
}

void loop(){
  if (Serial.available()) {
    temperature = Serial.parseInt(); // read the temperature value
    Serial.read(); // discardthe newline character
    humidity = Serial.parseInt(); // read the humidity value
    Serial.read(); // discard the newline character
    soilMoisture = Serial.parseInt(); // read the soil moisture value
    Serial.read(); // discard the newline character
    ldr = Serial.parseInt(); // read the LDR value
    Serial.read(); // discard the newline character
    waterLevel = Serial.parseInt(); // read the water detection value
    Serial.read(); // discard the newline character
    mq135 = Serial.parseInt(); // read the MQ135 value
    Serial.read(); // discard the newline character
    relayStatus = Serial.parseInt(); // read the relayStatus value
    Serial.read(); // discard the newline character
 
    // Update sensor values in Firebase
    Firebase.setInt(firebaseData, "temperature", temperature);
    Firebase.setInt(firebaseData, "humidity", humidity);
    Firebase.setInt(firebaseData, "soilMoisture", soilMoisture);
    Firebase.setInt(firebaseData, "ldr", ldr);
    Firebase.setInt(firebaseData, "waterLevel", waterLevel);
    Firebase.setInt(firebaseData, "mq135", mq135);


    if (relayStatus == 1)
    {
      Firebase.setBool(firebaseData, "relayStatus", true); // Update relay status in Firebase
      delay(3000);
    }
    Firebase.setBool(firebaseData, "relayStatus", false); // Update relay status in Firebase

  }
}

