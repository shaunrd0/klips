#include <WiFi.h>

//
// Web server project globals

// Replace with your network credentials
const char* ssid = "network-name";
const char* password = "password";

WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

//
// Button / light project globals

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

  // wait for the Serial Monitor to be open
  while (!Serial) {
    delay(100);
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("Web Server IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

// Handles the on-board button press.
void handleButtonPress() {
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

void displayPinState(WiFiClient client, int gpio_pin, bool state) {
  // Display current state, and ON/OFF buttons for GPIO <gpio_pin>
  client.println(String("<p>GPIO ") + String(gpio_pin) + String(" - Current State ") + String(state ? "ON" : "OFF") + String("</p>"));
  // If the output state is off, it displays the ON button
  if (state) {
    client.println(String("<p><a href=\"/") + String(gpio_pin) + String("/off\"><button class=\"button button2\">OFF</button></a></p>"));
  } else {
    client.println(String("<p><a href=\"/") + String(gpio_pin) + String("/on\"><button class=\"button\">ON</button></a></p>"));
  }
}

void handleStateChange(WiFiClient client, int gpio_pin) {
  if (header.indexOf(String("GET /") + String(gpio_pin) + String("/on")) >= 0) {
    Serial.println(String("GPIO ") + String(gpio_pin) + String(" on"));
    light_on = true;
    digitalWrite(gpio_pin, HIGH);
  } else if (header.indexOf(String("GET /") + String(gpio_pin) + String("/off")) >= 0) {
    Serial.println(String("GPIO ") + String(gpio_pin) + String(" off"));
    light_on = false;
    digitalWrite(gpio_pin, LOW);
  }
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  handleButtonPress();

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    Serial.println("Web Server IP address: ");
    Serial.println(WiFi.localIP());

    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      // Also handle the button press in this loop to not miss events.
      handleButtonPress();

      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // turns the GPIOs on and off
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");

            //
            // Web Page Heading
            client.println("<body><h1>ESP32 Web Server</h1>");
            //
            // Web Page Body Contents

            // Button Controls
            displayPinState(client, ledPin, light_on);

            //
            // Close Web Page Body / Heading
            client.println("</body></html>");
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
