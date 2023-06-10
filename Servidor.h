#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <ESP8266WebServer.h>
#include "VariablesEEPROM.h"
#include <ArduinoJson.h>

ESP8266WebServer server(80);

class Servidor {

  private:
    static void guardarWifi() {
      if (!verificarToken()) {
        server.send(400, "text/plain", "Acceso denegado");
      }

      if (server.method() == HTTP_POST) {
        Serial.println("LLegue aca");
        Servidor::guardarDatos();
      } else {
        server.send(403, "text/plain", "Recurso no encontrado");
      }
    }
    static void guardarDatos() {
      // Leer el cuerpo de la solicitud JSON
      String jsonString = server.arg("plain");

      // Crear un objeto JSON para analizar el contenido
      StaticJsonDocument<256> jsonDoc;
      DeserializationError error = deserializeJson(jsonDoc, jsonString);

      // Verificar si ocurrió un error al analizar el JSON
      if (error) {
        server.send(400, "text/plain", "Error al procesar la solicitud");
        return;
      }

      // Obtener los valores de password y SSID del JSON
       const char* newPassword = jsonDoc["password"];
       const char* newSSID = jsonDoc["ssid"];

      Serial.println(newPassword);
      Serial.println(newSSID);

      // Verificar que los campos no excedan el tamaño máximo permitido
      if (VariablesEEPROM::guardarSSID(newSSID) && VariablesEEPROM::guardarPassword(newPassword)) {
        server.send(200, "text/plain", "Configuración exitosa");
      } else {
        server.send(400, "text/plain", "Los campos exceden el tamaño máximo permitido");
      }
    }
    static bool verificarToken() {
      // Obtener el token de autenticación de la solicitud
      String tokenDeLaPeticion = server.header("Authorization");
      String tokenGuardado = VariablesEEPROM::obtenerToken();
     
      // Comparar el token de autenticación con el token esperado
      return tokenDeLaPeticion == tokenGuardado;
    }

  public:
    static void iniciarServidor() {
      server.on("/wifi", Servidor::guardarWifi);
      server.begin();
      Serial.println("Servidor iniciado");
    }

    static void serverEnEscucha(){
      server.handleClient();
    }

    static void apagarServidor(){
      server.close();
    }



};


#endif
