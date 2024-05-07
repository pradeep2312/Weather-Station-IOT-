#include <WiFi.h>
#include <HTTPClient.h>
#include <DHT.h>

// Wifi Credentials
const char* ssid = "schoimkang";
const char* password = "sc1003mk0709";

// Server endpoint
const char* serverName = "https://z9k5911x-5000.use2.devtunnels.ms/post-data";

// DHT Sensor setup
#define DHTPIN 4        // Pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    dht.begin();

    // Connect to Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi!!");
}

void loop() {
    // Check Wi-Fi connection
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // Read temperature and humidity values
        /*
        float humidity = dht.readHumidity();
        float temperature = dht.readTemperature();

        // Check if any reads failed and exit early (to try again).
        if (isnan(humidity) || isnan(temperature)) {
            Serial.println("Failed to read from DHT sensor!");
            return;
        }
        */

        // Used for testing w/o DHT Sensor (Comment out the above code)
        float humidity = 45;
        float temperature = 70;

        http.begin(serverName);
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");

        // Prepare data string
        String httpRequestData = "team_number=2";
        httpRequestData += "&temperature=" + String(temperature);
        httpRequestData += "&humidity=" + String(humidity);
        httpRequestData += "&timestamp=" + String(millis());

        Serial.println(httpRequestData);
        // Send HTTP POST request
        int httpResponseCode = http.POST(httpRequestData);

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println("success");
            Serial.println(httpResponseCode);
            Serial.println(response);
        } else {
            Serial.print("Error on sending POST: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    } else {
        Serial.println("WiFi Disconnected");
    }

    delay(10000);  // Send data every 10 seconds
}
