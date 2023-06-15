#ifndef SERVIDOR_H
#define SERVIDOR_H

#include <ESP8266WebServer.h>
#include "VariablesEEPROM.h"
#include <ArduinoJson.h>
#include "PrenderOApagarFuncionalidad.h"
#include <ESP8266WiFi.h>



ESP8266WebServer server(80);

class Servidor {

  private:
    static void guardarWifi() {
      StaticJsonDocument<100> responseJsonDoc;
      String respuesta;
      if (server.method() == HTTP_POST) {
        if (!verificarToken()) {
          responseJsonDoc["message"] = "Acceso prohibido";
          serializeJson(responseJsonDoc, respuesta);
          server.send(403, "application/json", respuesta);
        }
        Servidor::httpPOSTGuardarWifi();
      } else {
        responseJsonDoc["message"] = "Recurso no encontrado";
        serializeJson(responseJsonDoc, respuesta);
        server.send(404, "application/json", respuesta);
      }
    }
    static void httpPOSTGuardarWifi() {
      // Leer el cuerpo de la solicitud JSON
      String jsonString = server.arg("plain");
      String response;
      // Crear un objeto JSON para analizar el contenido
      StaticJsonDocument<100> responseJsonDoc;
      StaticJsonDocument<256> requestJsonDoc;

      DeserializationError error = deserializeJson(requestJsonDoc, jsonString);

      // Verificar si ocurrió un error al analizar el JSON
      if (error) {
        responseJsonDoc["message"] = "Error al procesar la solicitud";
        serializeJson(responseJsonDoc, response);
        server.send(400, "application/json", response);
        return;
      }

      // Obtener los valores de password y SSID del JSON
      const char* newPassword = requestJsonDoc["password"];
      const char* newSSID = requestJsonDoc["ssid"];

      Serial.println(newPassword);
      Serial.println(newSSID);

      // Verificar que los campos no excedan el tamaño máximo permitido
      if (VariablesEEPROM::guardarSSID(newSSID) && VariablesEEPROM::guardarPassword(newPassword)) {
        responseJsonDoc["message"] = "Se guardaron las credenciales correctamente";
        serializeJson(responseJsonDoc, response);
        server.send(200, "application/json", response);
      } else {
        responseJsonDoc["message"] = "Los campos exceden el tamaño máximo permitido";
        serializeJson(responseJsonDoc, response);
        server.send(400, "application/json", response);
      }
    }
    static void encenderDispositivo() {
      StaticJsonDocument<200> responseJsonDoc;
      String respuesta;

      if (server.method() == HTTP_POST) {
        if (!verificarToken()) {
          responseJsonDoc["message"] = "Acceso prohibido";
          serializeJson(responseJsonDoc, respuesta);
          server.send(403, "application/json", respuesta);
        }
        responseJsonDoc["on"] = true;
        if (EstadoDeSensor::getEstadoSensor() == 0) {
          EstadoDeSensor::setViejoEstadoDelBoton(1);
          EstadoDeSensor::setEstadoSensor(1);
          EstadoDeSensor::setBanderaEstadoDelDispositivo(0);
          EstadoDeSensor::sePrendioElDispositivo();
          responseJsonDoc["message"] = "El dispositivo se prendio";
        } else {
          responseJsonDoc["message"] = "El dispositivo ya estaba prendido";
        }

        serializeJson(responseJsonDoc, respuesta);
        server.send(200, "application/json", respuesta);

      } else {
        responseJsonDoc["message"] = "Recurso no encontrado";
        serializeJson(responseJsonDoc, respuesta);
        server.send(404, "application/json", respuesta);
      }
    }

    static void apagarDispositivo() {
      StaticJsonDocument<200> responseJsonDoc;
      String respuesta;

      if (server.method() == HTTP_POST) {
        if (!verificarToken()) {
          responseJsonDoc["message"] = "Acceso prohibido";
          serializeJson(responseJsonDoc, respuesta);
          server.send(403, "application/json", respuesta);
        }

        if (EstadoDeSensor::getEstadoSensor() == 1) {
          EstadoDeSensor::setViejoEstadoDelBoton(1);
          EstadoDeSensor::setEstadoSensor(0);
          EstadoDeSensor::setBanderaEstadoDelDispositivo(1);
          EstadoDeSensor::seApagoElDispositivo();
          responseJsonDoc["message"] = "El dispositivo se apagó";

        } else {
          responseJsonDoc["message"] = "El dispositivo ya estaba apagado";
        }

        serializeJson(responseJsonDoc, respuesta);
        server.send(200, "application/json", respuesta);
      } else {
        responseJsonDoc["message"] = "Recurso no encontrado";
        serializeJson(responseJsonDoc, respuesta);
        server.send(404, "application/json", respuesta);
      }
    }

    static void verificarConexionWifi() {
      StaticJsonDocument<200> responseJsonDoc;
      String respuesta;

      if (server.method() == HTTP_GET) {
        if (!verificarToken()) {
          responseJsonDoc["message"] = "Acceso prohibido";
          serializeJson(responseJsonDoc, respuesta);
          server.send(403, "application/json", respuesta);
        }

        if (WiFi.status() == WL_CONNECTED) {
          responseJsonDoc["message"] = "Conectado al wifi";
          responseJsonDoc["on"] = true;
          serializeJson(responseJsonDoc, respuesta);
          server.send(200, "application/json", respuesta);
        }
      } else {
        responseJsonDoc["message"] = "Recurso no encontrado";
        serializeJson(responseJsonDoc, respuesta);
        server.send(404, "application/json", respuesta);
      }
    }

    static void verificarEstadoDelSensor() {
      StaticJsonDocument<200> responseJsonDoc;
      String respuesta;
      if (server.method() == HTTP_GET) {
        if (!verificarToken()) {
          responseJsonDoc["message"] = "Acceso prohibido";
          serializeJson(responseJsonDoc, respuesta);
          server.send(403, "application/json", respuesta);
        }

        if (EstadoDeSensor::getEstadoSensor() == 1) {
          responseJsonDoc["message"] = "El dispositivo esta encendido";
          responseJsonDoc["on"] = true;
        } else {
          responseJsonDoc["message"] = "El dispositivo esta apagado";
          responseJsonDoc["on"] = false;
        }

        serializeJson(responseJsonDoc, respuesta);
        server.send(200, "application/json", respuesta);
      } else {
        responseJsonDoc["message"] = "Recurso no encontrado";
        serializeJson(responseJsonDoc, respuesta);
        server.send(404, "application/json", respuesta);
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
      server.on("/encender", Servidor::encenderDispositivo);
      server.on("/apagar", Servidor::apagarDispositivo);
      server.on("/verificar-wifi", Servidor::verificarConexionWifi);
      server.on("/verificar-estado-sensor", Servidor::verificarEstadoDelSensor);
      server.begin();
      Serial.println("Servidor iniciado");
    }

    static void serverEnEscucha() {
      server.handleClient();
    }

    static void apagarServidor() {
      server.close();
    }



};


#endif
