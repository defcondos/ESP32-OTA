#include <WiFi.h>
#include <ArduinoOTA.h>
#include <Servo.h>

const char* ssid="Richi wifi";
const char* password="28042991";

const char* PWD_OTA = "admin";
const char* HOST_NAME = "esp32-A734BC";
const int PORT_OTA = 8266;

Servo servomotor;

void setup() {
  
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.waitForConnectResult() != WL_CONNECTED){
    Serial.println("No se ha podido realizar la conexión a la red Wifi");
    delay(5000);
    ESP.restart();
  }

  for (int i = 0; i<5; i++){
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  }

  servomotor.attach(4);

  ArduinoOTA.setPassword(PWD_OTA);
  ArduinoOTA.setHostname(HOST_NAME);
  ArduinoOTA.setPort(PORT_OTA);

  ArduinoOTA.begin();

  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  
  Serial.print("Nombre de host: ");
  Serial.println(WiFi.getHostname());


}

void loop() {
  // put your main code here, to run repeatedly:
  ArduinoOTA.handle();
  delay(500);

  servomotor.write(0);
  delay(1000);
  servomotor.write(90);
  delay(1000);
}

