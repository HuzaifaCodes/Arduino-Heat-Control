#include <DHT.h> //adding dht library

#define DHTPIN 2          // Digital pin connected to the DHT11
#define DHTTYPE DHT11     // Since we are usind DHT 11

// Setting up variables
const int relayPin = 4;  // Digital pin connected to the relay (4)
const int buttonPin = 3; // Digital pin connected to the push button (3)
// We will set initial heating state to low because the heating element is off at starting
int heatingState = LOW;  // Initial heating state (OFF)
int previousButtonState = HIGH; // Previous state of the button
int currentButtonState; // Current state of the button
DHT dht(DHTPIN, DHTTYPE); // creating an object from dht library

void setup() {
  
  pinMode(relayPin, OUTPUT);      // Set the relay pin as output
  pinMode(buttonPin, INPUT_PULLUP); // Set the button pin as input with internal pull-up resistor
  digitalWrite(relayPin, heatingState); // Set the initial state of the relay

  Serial.begin(9600);
  dht.begin();
}

void loop() {
  currentButtonState = digitalRead(buttonPin); // Read the current state of the button

  // Check if the button is pressed and released
  if (currentButtonState == LOW && previousButtonState == HIGH) {
    heatingState = !heatingState; // Toggle the heating state

    if (heatingState == HIGH) {
      Serial.println("Heating turned ON");
    } else {
      Serial.println("Heating turned OFF");
    }

    digitalWrite(relayPin, heatingState); // Update the relay state
  }

  previousButtonState = currentButtonState; // Save the current state for the next iteration

  // Read temperature from DHT11 sensor
  float temperature = dht.readTemperature();
  if (!isnan(temperature)) {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println("°C");
  }

  delay(500); // Small delay between each iteration
}
