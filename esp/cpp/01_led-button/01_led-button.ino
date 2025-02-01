// set pin numbers
const int buttonPin = 4;  // the number of the pushbutton pin
const int ledPin =  5;    // the number of the LED pin

// variable for storing the pushbutton status
int buttonState = 0;

bool light_on = false;
bool handled = false;

void setup() {
  Serial.begin(115200);
  // initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT);
  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the state of the pushbutton value
  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed.
  if (buttonState == HIGH) {
    if (!handled) {
      Serial.println("Handling button pressed.");
      light_on = !light_on;
      handled = true;
      digitalWrite(ledPin, light_on ? HIGH : LOW);
    }
    // turn LED on
  } else {
    if (handled) {
      Serial.println("Reset button handled state.");
      handled = false;

    }
  }
}
