#include "FuncionalidadDelProyectoDelSensor.h"
#include "ConexionWifi.h"
#include "Servidor.h"
#include "ComponentesExternos.h"



void setup() {
  Serial.begin(9600);

  EEPROM.begin(VariablesEEPROM::initSizeEEPROM());

  ComponentesExternos::setup();
  ConexionWifi::conectar();
  Servidor::iniciarServidor();
}

void loop() {
  Sensor::initFuncionalidadDelProyectoDelSensor();
  Servidor::serverEnEscucha();
}
