/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID           "TMPL6xjUDhMPg"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "94JMP1qvX3SIOWEnFoEarErMvrC_h61J"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <rpcWiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleWioTerminal.h>

#include <Wire.h>
#include <DHT.h>

#define DHTTYPE DHT20
DHT dht(DHTTYPE);

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "S23FE";
char pass[] = "joaquin:)";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // Keep the random number demonstration
  int randomNumber = random(0, 1024);
  Blynk.virtualWrite(V5, randomNumber);

  // Read the DHT20 sensor
  float values[2];

  if (dht.readTempAndHumidity(values) == 0)
  {
    float humidity = values[0];
    float temperature = values[1];

    // Upload readings to Blynk
    Blynk.virtualWrite(V6, temperature);
    Blynk.virtualWrite(V7, humidity);

    // Print readings for debugging
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
  else
  {
    Serial.println("Failed to read DHT20!");
  }
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Wire.begin();
  dht.begin();
  
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  // Setup a function to be called every second
  timer.setInterval(2000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}

