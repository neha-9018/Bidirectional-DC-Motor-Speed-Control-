#define BLYNK_TEMPLATE_ID "YourTemplateID"
#define BLYNK_DEVICE_NAME "EV_Battery_Monitor"
#define BLYNK_AUTH_TOKEN "YourAuthToken"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

/* WiFi credentials */
char ssid[] = "YourWiFiName";
char pass[] = "YourWiFiPassword";

/* Variables */
float temperature;
float voltage;

void setup()
{
  Serial.begin(9600);   // Communication with Arduino

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop()
{
  Blynk.run();

  /* Receive data from Arduino */
  if (Serial.available())
  {
    String data = Serial.readStringUntil('\n');

    int commaIndex = data.indexOf(',');

    if(commaIndex > 0)
    {
      temperature = data.substring(0, commaIndex).toFloat();
      voltage = data.substring(commaIndex + 1).toFloat();

      /* Send data to Blynk */
      Blynk.virtualWrite(V0, temperature);
      Blynk.virtualWrite(V1, voltage);

      /* Overheat alert */
      if(temperature > 40)
      {
        Blynk.virtualWrite(V2, 255);   // Alert LED ON
      }
      else
      {
        Blynk.virtualWrite(V2, 0);     // Alert LED OFF
      }
    }
  }
}