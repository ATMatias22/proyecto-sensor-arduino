
#ifndef REQUEST_H
#define REQUEST_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h> 

class Request {
  private:
    static char* HOST ;
    static char* URI ;
    static int PORT ;

  public:
    static void enviarMensaje(String mensaje) {

      if (WiFi.status() == WL_CONNECTED) {
        WiFiClientSecure client;
        client.setFingerprint("95:F6:BE:80:49:C9:6A:D2:B3:72:88:CA:E5:5C:2A:71:A7:1B:81:2B");
        HTTPClient http;

        Serial.println(WiFi.status());

        http.begin(client, Request::HOST,Request::PORT, Request::URI,true ); //HTTP

        // Configura los encabezados de la solicitud POST
        http.addHeader("Content-Type", "application/json");

        // Crea un objeto JSON
        StaticJsonDocument<200> jsonDoc;

        // Añade los atributos al JSON
        jsonDoc["deviceCode"] = VariablesEEPROM::obtenerDeviceCode();
        jsonDoc["message"] = mensaje;
        jsonDoc["token"] = VariablesEEPROM::obtenerToken();

        // Crea una cadena para almacenar el JSON
        String jsonData;
        serializeJson(jsonDoc, jsonData);

        // Envía la solicitud POST al servidor
        int httpResponseCode = http.POST(jsonData);

        // Verifica el código de respuesta
        if (httpResponseCode > 0) {
          String response = http.getString();
          Serial.println("Código de respuesta: " + String(httpResponseCode));
          Serial.println("Respuesta: " + response);
        } else {
          Serial.println("Error en la solicitud. Código de respuesta: " + String(httpResponseCode));
        }

        // Cierra la conexión HTTP
        http.end();
      } else {
        Serial.println("No se pudo conectar a la red Wi-Fi");
      }

    }
};

char* Request::HOST = "proyecto-backend-movil-production.up.railway.app";
char* Request::URI = "/app_movil_sensor/api/arduino/add-informative-message";
int Request::PORT = 443;
#endif
