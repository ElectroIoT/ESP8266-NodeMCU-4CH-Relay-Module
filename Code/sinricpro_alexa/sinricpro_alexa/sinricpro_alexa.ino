#include <ESP8266WiFi.h>
#include <SinricPro.h>
#include <SinricProSwitch.h>

// Wi-Fi Credentials
const char* SSID = "Your_SSID";
const char* PASSWORD = "Your_PASSWORD";

// SinricPro Credentials
#define APP_KEY       "YOUR_APP_KEY"
#define APP_SECRET    "YOUR_APP_SECRET"
#define SWITCH_ID_1   "YOUR_DEVICE_ID_1"
#define SWITCH_ID_2   "YOUR_DEVICE_ID_2"
#define SWITCH_ID_3   "YOUR_DEVICE_ID_3"
#define SWITCH_ID_4   "YOUR_DEVICE_ID_4"

// Relay GPIOs
#define RELAY_1 5   // D1
#define RELAY_2 4   // D2
#define RELAY_3 15  // D8
#define RELAY_4 13  // D7

// Switch GPIOs
#define SWITCH_1 0   // D3
#define SWITCH_2 2   // D4
#define SWITCH_3 14  // D5
#define SWITCH_4 12  // D6

// Store relay states
bool relayState[4] = {false, false, false, false};

// Alexa callback function
bool onPowerState(const String &deviceId, bool state) {
  int relayIndex = -1;

  if (deviceId == SWITCH_ID_1) relayIndex = 0;
  else if (deviceId == SWITCH_ID_2) relayIndex = 1;
  else if (deviceId == SWITCH_ID_3) relayIndex = 2;
  else if (deviceId == SWITCH_ID_4) relayIndex = 3;

  if (relayIndex != -1) {
    relayState[relayIndex] = state;
    digitalWrite((relayIndex == 0) ? RELAY_1 :
                 (relayIndex == 1) ? RELAY_2 :
                 (relayIndex == 2) ? RELAY_3 : RELAY_4, state ? HIGH : LOW);
  }

  return true;
}

// Attach SinricPro devices
void setupSinricPro() {
  SinricProSwitch &switch1 = SinricPro[SWITCH_ID_1];
  SinricProSwitch &switch2 = SinricPro[SWITCH_ID_2];
  SinricProSwitch &switch3 = SinricPro[SWITCH_ID_3];
  SinricProSwitch &switch4 = SinricPro[SWITCH_ID_4];

  switch1.onPowerState(onPowerState);
  switch2.onPowerState(onPowerState);
  switch3.onPowerState(onPowerState);
  switch4.onPowerState(onPowerState);

  SinricPro.begin(APP_KEY, APP_SECRET);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(SSID, PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to WiFi");

  // Set relay pins as output
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);

  // Set switch pins as input with pull-up resistors
  pinMode(SWITCH_1, INPUT_PULLUP);
  pinMode(SWITCH_2, INPUT_PULLUP);
  pinMode(SWITCH_3, INPUT_PULLUP);
  pinMode(SWITCH_4, INPUT_PULLUP);

  // Initialize all relays to OFF
  digitalWrite(RELAY_1, LOW);
  digitalWrite(RELAY_2, LOW);
  digitalWrite(RELAY_3, LOW);
  digitalWrite(RELAY_4, LOW);

  // Setup Alexa (SinricPro)
  setupSinricPro();
}

void loop() {
  SinricPro.handle();

  // Read switch states
  if (digitalRead(SWITCH_1) == LOW) {
    relayState[0] = !relayState[0];
    digitalWrite(RELAY_1, relayState[0] ? HIGH : LOW);
    delay(300);
  }
  if (digitalRead(SWITCH_2) == LOW) {
    relayState[1] = !relayState[1];
    digitalWrite(RELAY_2, relayState[1] ? HIGH : LOW);
    delay(300);
  }
  if (digitalRead(SWITCH_3) == LOW) {
    relayState[2] = !relayState[2];
    digitalWrite(RELAY_3, relayState[2] ? HIGH : LOW);
    delay(300);
  }
  if (digitalRead(SWITCH_4) == LOW) {
    relayState[3] = !relayState[3];
    digitalWrite(RELAY_4, relayState[3] ? HIGH : LOW);
    delay(300);
  }
}
