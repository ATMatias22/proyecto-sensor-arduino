 #include "FuncionalidadDelProyectoDelSensor.h"
#include "ConexionWifi.h"
#include "Servidor.h"

void setup() {
  Serial.begin(9600);

  EEPROM.begin(VariablesEEPROM::initSizeEEPROM());

  initProductosExternos();
  ConexionWifi::conectar();
  Servidor::iniciarServidor();

}

void loop() {
  initFuncionalidadDelProyectoDelSensor();

 Servidor::serverEnEscucha();
}
