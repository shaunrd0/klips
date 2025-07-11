#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "main.h"

// Replace with your network credentials
const char *ssid = "wifi";
const char *password = "password";

#define DHTPIN GPIO_NUM_4  // Digital pin connected to the DHT sensor

// Uncomment the type of sensor in use:
#define DHTTYPE      DHT_TYPE_DHT11  // DHT 11
//#define DHTTYPE    DHT_TYPE_DHT22  // DHT 22 (AM2302)
//#define DHTTYPE    DHT_TYPE_DHT21  // DHT 21 (AM2301)

float DHT::readTemperature(bool f)
{
  float humidity = 0;
  float temperature = 0;
  esp_err_t result = dht_read_float_data(type_, gpio_, &humidity,
                                         &temperature);
  if (result == ESP_OK) {
    ESP_LOGI("[DHT::readTemperature]", "Humidity: %.1f%% Temperature: %.1f°C",
             humidity,
             temperature);
  } else {
    ESP_LOGE("[DHT::readTemperature]", "Failed to read sensor data: %s",
             esp_err_to_name(result));
  }
  return f ? (temperature * 1.8f) + 32 : temperature;
}

float DHT::readHumidity()
{
  float humidity = 0;
  float temperature = 0;
  esp_err_t result = dht_read_float_data(type_, gpio_, &humidity,
                                         &temperature);
  if (result == ESP_OK) {
    ESP_LOGI("[DHT::readTemperature]", "Humidity: %.1f%% Temperature: %.1f°C",
             humidity,
             temperature);
  } else {
    ESP_LOGE("[DHT::readTemperature]", "Failed to read sensor data: %s",
             esp_err_to_name(result));
  }
  return humidity;
}

DHT dht(DHTPIN, DHTTYPE);

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String readDHTTemperature()
{
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  } else {
    Serial.println(t);
    return String(t);
  }
}

String readDHTHumidity()
{
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
    return "--";
  } else {
    Serial.println(h);
    return String(h);
  }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .dht-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>ESP32 DHT Server</h2>
  <p>
    <i class="fas fa-thermometer-half" style="color:#059e8a;"></i>
    <span class="dht-labels">Temperature</span>
    <span id="temperature">%TEMPERATURE%</span>
    <sup class="units">&deg;C</sup>
  </p>
  <p>
    <i class="fas fa-tint" style="color:#00add6;"></i>
    <span class="dht-labels">Humidity</span>
    <span id="humidity">%HUMIDITY%</span>
    <sup class="units">&percnt;</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("temperature").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/temperature", true);
  xhttp.send();
}, 10000 ) ;

setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("humidity").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/humidity", true);
  xhttp.send();
}, 10000 ) ;
</script>
</html>)rawliteral";

// Replaces placeholder with DHT values
String processor(const String &var)
{
  //Serial.println(var);
  if (var == "TEMPERATURE") {
    return readDHTTemperature();
  } else if (var == "HUMIDITY") {
    return readDHTHumidity();
  }
  return String();
}

void setup()
{
  // Serial port for debugging purposes
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [ ](AsyncWebServerRequest *request) {
    request->send(200, "text/html", index_html, processor);
  });
  server.on("/temperature", HTTP_GET, [ ](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", readDHTTemperature().c_str());
  });
  server.on("/humidity", HTTP_GET, [ ](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", readDHTHumidity().c_str());
  });

  // Start server
  server.begin();
}

void loop()
{

}
