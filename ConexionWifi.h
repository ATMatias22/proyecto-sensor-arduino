#ifndef CONEXION_WIFI_H
#define CONEXION_WIFI_H


#include <ESP8266WiFi.h>
#include <IPAddress.h>
#include <DNSServer.h>
#include <WiFiManager.h>

#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


int MAX_INTENTOS_DE_CONEXION = 30;

class ConexionWifi {
    // Constructor privado para evitar instanciación directa
  private:
    ConexionWifi() {

    }
  public:

    static void conectar() {

      // Configurar la dirección IP estática
      IPAddress ip(192, 168, 0, 254);  // Dirección IP deseada
      IPAddress gateway(192, 168, 0, 1);  // Puerta de enlace
      IPAddress subnet(255, 255, 255, 0);  // Máscara de subred

      WiFi.config(ip, gateway, subnet);

      String p = VariablesEEPROM::obtenerPassword();
      String s = VariablesEEPROM::obtenerSSID();

      int contador = 0;
      WiFi.begin(s, p);

      while ((WiFi.status() != WL_CONNECTED) && (contador < MAX_INTENTOS_DE_CONEXION)) {
        delay(1000);
        Serial.println("Conectando a WiFi...");
        contador++;
      }

      if (contador == MAX_INTENTOS_DE_CONEXION) {
        Serial.println("No se pudo conectar al wifi");
        Serial.println("Entramos en modo access point");

        // Creamos una instancia de la clase WiFiManager
        WiFiManager wifiManager;
        wifiManager.resetSettings();
        // Cremos AP y portal cautivo

        IPAddress apIP(192, 168, 5, 6); // Ejemplo de dirección IP estática
        IPAddress netMsk(255, 255, 255, 0); // Ejemplo de máscara de subred
        WiFi.softAPConfig(apIP, apIP, netMsk);

        wifiManager.autoConnect("ESP8266Temp");

        Serial.println("estoy despues del autoconect");
      } else {
        Serial.println("Conectado a WiFi");
        Serial.println(WiFi.localIP());
      }
    }

};


#endif
