#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include <ESP8266WiFi.h>

const char DEVICE_LOGIN_NAME[] = ""; // Enter DEVICE ID
const char SSID[] = "";            // Enter WiFi SSID (name)
const char PASS[] = "";            // Enter WiFi password
const char DEVICE_KEY[] = "";      // Enter Secret device password (Secret Key)

// Define the GPIO connected with Relays and switches
#define RelayPin1 5  // D1
#define RelayPin2 4  // D2
#define RelayPin3 15 // D8
#define RelayPin4 13 // D7

#define SwitchPin1 0 // D3
#define SwitchPin2 2  // D4
#define SwitchPin3 14 // D5
#define SwitchPin4 12  // D6

#define wifiLed 16 // D0

int toggleState_1 = 0; // Define integer to remember the toggle state for relay 1
int toggleState_2 = 0; // Define integer to remember the toggle state for relay 2
int toggleState_3 = 0; // Define integer to remember the toggle state for relay 3
int toggleState_4 = 0; // Define integer to remember the toggle state for relay 4

void onRelay1Change();
void onRelay2Change();
void onRelay3Change();
void onRelay4Change();

CloudSwitch relay1;
CloudSwitch relay2;
CloudSwitch relay3;
CloudSwitch relay4;

void initProperties() {
  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);

  ArduinoCloud.addProperty(relay1, READWRITE, ON_CHANGE, onRelay1Change);
  ArduinoCloud.addProperty(relay2, READWRITE, ON_CHANGE, onRelay2Change);
  ArduinoCloud.addProperty(relay3, READWRITE, ON_CHANGE, onRelay3Change);
  ArduinoCloud.addProperty(relay4, READWRITE, ON_CHANGE, onRelay4Change);
}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);

const int debounceDelay = 200; // Debounce delay in milliseconds
unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long lastDebounceTime3 = 0;
unsigned long lastDebounceTime4 = 0;

bool previousSwitchState1 = HIGH;
bool previousSwitchState2 = HIGH;
bool previousSwitchState3 = HIGH;
bool previousSwitchState4 = HIGH;

void manual_control() {
  unsigned long currentMillis = millis();

  // Manual Switch Control
  if (digitalRead(SwitchPin1) == LOW && previousSwitchState1 == HIGH) {
    if (currentMillis - lastDebounceTime1 >= debounceDelay) {
      toggleState_1 = !toggleState_1;
      digitalWrite(RelayPin1, !toggleState_1);
      relay1 = toggleState_1;
      lastDebounceTime1 = currentMillis;
    }
  }
  previousSwitchState1 = digitalRead(SwitchPin1);

  if (digitalRead(SwitchPin2) == LOW && previousSwitchState2 == HIGH) {
    if (currentMillis - lastDebounceTime2 >= debounceDelay) {
      toggleState_2 = !toggleState_2;
      digitalWrite(RelayPin2, !toggleState_2);
      relay2 = toggleState_2;
      lastDebounceTime2 = currentMillis;
    }
  }
  previousSwitchState2 = digitalRead(SwitchPin2);

  if (digitalRead(SwitchPin3) == LOW && previousSwitchState3 == HIGH) {
    if (currentMillis - lastDebounceTime3 >= debounceDelay) {
      toggleState_3 = !toggleState_3;
      digitalWrite(RelayPin3, !toggleState_3);
      relay3 = toggleState_3;
      lastDebounceTime3 = currentMillis;
    }
  }
  previousSwitchState3 = digitalRead(SwitchPin3);

  if (digitalRead(SwitchPin4) == LOW && previousSwitchState4 == HIGH) {
    if (currentMillis - lastDebounceTime4 >= debounceDelay) {
      toggleState_4 = !toggleState_4;
      digitalWrite(RelayPin4, !toggleState_4);
      relay4 = toggleState_4;
      lastDebounceTime4 = currentMillis;
    }
  }
  previousSwitchState4 = digitalRead(SwitchPin4);
}

void setup() {
  Serial.begin(9600);
  delay(1500);

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(RelayPin1, OUTPUT);
  pinMode(RelayPin2, OUTPUT);
  pinMode(RelayPin3, OUTPUT);
  pinMode(RelayPin4, OUTPUT);

  pinMode(wifiLed, OUTPUT);

  pinMode(SwitchPin1, INPUT_PULLUP);
  pinMode(SwitchPin2, INPUT_PULLUP);
  pinMode(SwitchPin3, INPUT_PULLUP);
  pinMode(SwitchPin4, INPUT_PULLUP);

  digitalWrite(RelayPin1, HIGH);
  digitalWrite(RelayPin2, HIGH);
  digitalWrite(RelayPin3, HIGH);
  digitalWrite(RelayPin4, HIGH);

  digitalWrite(wifiLed, HIGH);
}

void loop() {
  ArduinoCloud.update();
  manual_control();

  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(wifiLed, HIGH);
  } else {
    digitalWrite(wifiLed, LOW);
  }
}

void onRelay1Change() {
  digitalWrite(RelayPin1, relay1 ? LOW : HIGH);
  toggleState_1 = relay1;
}

void onRelay2Change() {
  digitalWrite(RelayPin2, relay2 ? LOW : HIGH);
  toggleState_2 = relay2;
}

void onRelay3Change() {
  digitalWrite(RelayPin3, relay3 ? LOW : HIGH);
  toggleState_3 = relay3;
}

void onRelay4Change() {
  digitalWrite(RelayPin4, relay4 ? LOW : HIGH);
  toggleState_4 = relay4;
}
