
#ifndef REQUEST_H
#define REQUEST_H

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>

class Request {
  private:
    static char* HOST ;
    static char* ENDPOINT ;
    static int PORT ;

  public:
    static void enviarMensaje(String mensaje) {

      if (WiFi.status() == WL_CONNECTED) {
        WiFiClient client;
        HTTPClient http;

        // Configura la URL del endpoint
        String url = "http://" + String(Request::HOST) + ":" + Request::PORT + String(Request::ENDPOINT);
        Serial.println(url);

        Serial.println(WiFi.status());

        http.begin(client, url); //HTTP

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

char* Request::HOST = "192.168.0.29";
char* Request::ENDPOINT = "/app_movil_sensor/api/arduino/add-informative-message";
int Request::PORT = 8080;
#endif
