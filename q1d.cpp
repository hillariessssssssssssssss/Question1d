// Define the LED pin (Assuming Pin 13, which is often an on-board LED)
const int ledPin = 13;
// Define the sensor pin
const int sensorPin = A0;


const int numReadings = 20;
float tempReadings[numReadings]; // Array to store temperatures in °C

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600); 
  // Initialize the array to 0.0
  for (int i = 0; i < numReadings; i++) {
    tempReadings[i] = 0.0;
  }
}


float readTemperature() {
  
  int adcValue = analogRead(sensorPin);

 
  float voltage = adcValue * (5.0 / 1024.0);
  float temperatureC = voltage * 100.0; 
  
  return temperatureC;
}

void loop() {
  float currentTemp = 0.0;

  for (int i = 0; i < numReadings; i++) {
    tempReadings[i] = readTemperature(); 
    currentTemp += tempReadings[i];      
    delay(500);
  }

  // Calculate the average temperature
  float averageTemp = currentTemp / numReadings;

  Serial.print("Average Temperature: ");
  Serial.print(averageTemp);
  Serial.println(" °C");


  if (averageTemp < 18.0) {
    // a. Below 18°C: Blink 15 times @ 500ms
    Serial.println("Temp LOW (Blink @ 500ms)");
    blinkLEDs(15, 500);
  } else if (averageTemp >= 18.0 && averageTemp <= 25.0) {
    // b. 18°C to 25°C: Blink 15 times @ 300ms
    Serial.println("Temp OK (Blink @ 300ms)");
    blinkLEDs(15, 300);
  } else if (averageTemp > 25.0 && averageTemp <= 30.0) {
    // c. 25°C to 30°C: Blink 20 times @ 100ms
    Serial.println("Temp WARM (Blink @ 100ms)");
    blinkLEDs(20, 100);
  } else { // averageTemp > 30.0
    // d. Exceeds 30°C: Turn on continuously
    Serial.println("Temp HIGH (LED ON)");
    digitalWrite(ledPin, HIGH); // Turn LEDs ON continuously
    delay(5000); // Keep LEDs on for a while before next loop
  }
}

// blink the LEDs
void blinkLEDs(int times, int interval) {
  for (int i = 0; i < times; i++) {
    digitalWrite(ledPin, HIGH); // Turn the LED on
    delay(interval);            // Wait
    digitalWrite(ledPin, LOW);  // Turn the LED off
    delay(interval);            // Wait
  }
  // Ensure the LED is off after blinking is complete
  digitalWrite(ledPin, LOW);
}