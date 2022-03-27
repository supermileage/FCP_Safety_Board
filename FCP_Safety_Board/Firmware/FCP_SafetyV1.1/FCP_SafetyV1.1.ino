#define relay1 4
#define relay2 5
#define relay3 2
#define relay4 3

#define faultLED 10
#define testLED 9

#define faultButton 7
#define testButton 6

#define hydrogenSensor A0

// Variables will change:
int faultButtonState;             // the current reading from the input pin
int testButtonState;             // the current reading from the input pin
int lastFaultButtonState = HIGH;   // the previous reading from the input pin
int lastTestButtonState = HIGH;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastFaultDebounceTime = 0;  // the last time the output pin was toggled
unsigned long lastTestDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

float hydrogenThreshold = 100; // todo find a threshold value for hydrogen

void setup() {
  pinMode(faultButton, INPUT_PULLUP);
  pinMode(testButton, INPUT_PULLUP);
  
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  pinMode(faultLED, OUTPUT);
  pinMode(testLED, OUTPUT);

  pinMode(hydrogenSensor, INPUT);


  // set initial LED state
  digitalWrite(faultLED, true);
  digitalWrite(testLED, false);

  digitalWrite(relay1, false);
  digitalWrite(relay2, false);
  digitalWrite(relay3, false);
  digitalWrite(relay4, false);
}

void loop() {
  // read the state of the switch into a local variable:
  int faultReading = digitalRead(faultButton);

  // If the switch changed, due to noise or pressing:
  if (faultReading != lastFaultButtonState) {
    // reset the debouncing timer
    lastFaultDebounceTime = millis();
  }

  if ((millis() - lastFaultDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (faultReading != faultButtonState) {
      faultButtonState = faultReading;

      // only toggle the LED if the new button state is HIGH
      if (faultButtonState == LOW) {
        digitalWrite(faultLED, false);
        digitalWrite(testLED, false);

        digitalWrite(relay2, true);

        delay(1000);
      
        digitalWrite(relay1, true);
        digitalWrite(relay3, true);
        
        digitalWrite(relay4, true);
      }
    }
  }


  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastFaultButtonState = faultReading;


    // read the state of the switch into a local variable:
  int testReading = digitalRead(testButton);

  // If the switch changed, due to noise or pressing:
  if (testReading != lastTestButtonState) {
    // reset the debouncing timer
    lastTestDebounceTime = millis();
  }

  if ((millis() - lastTestDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (testReading != testButtonState) {
      testButtonState = testReading;

      // only toggle the LED if the new button state is HIGH
      if (testButtonState == LOW) {
        digitalWrite(faultLED, false);
        digitalWrite(testLED, true);
      
        digitalWrite(relay1, false);
        digitalWrite(relay2, false);
        digitalWrite(relay3, false);
        digitalWrite(relay4, false);
      }
    }
  }
  
//if we detect a hydrogen leak then send the system to fault
  // if (analogRead(hydrogenSensor)> hydrogenThreshold){
  //   digitalWrite(faultLED, true);
  // }


  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastTestButtonState = testReading;
}
