
#ifndef FUNCIONALIDAD_DEL_PROYECTO_DEL_SENSOR_H
#define FUNCIONALIDAD_DEL_PROYECTO_DEL_SENSOR_H

#include "VariablesEEPROM.h"
#include "ConexionWifi.h"
#include "PrenderOApagarFuncionalidad.h"
#include "Request.h"
#include "Servidor.h"

#define PIN_LED_ROJO D5 //LED QUE SE PRENDE O APAGA SEGUN EL ESTADO DE LA PUERTA
#define PIN_SENSOR_MAGNETICO D7
#define PIN_LED_VERDE D1 //LED QUE SE PRENDE O APAGA SI EL PRODUCTO ESTA ENCENDIDO O APAGADO
#define PIN_BOTON D2

int valorSensor;

const int CERRADO = 0;
const int ABIERTO = 1;

int seEnvioMensaje;

int banderaEstadoDelDispositivo = 0;

//private 
void manejarEstadoPuerta(String mensaje, bool puertaAbierta) {
  Serial.println(mensaje);
  digitalWrite(PIN_LED_ROJO, puertaAbierta ? HIGH : LOW);
  seEnvioMensaje = puertaAbierta ? CERRADO : ABIERTO;
  Request::enviarMensaje(mensaje);
}


//private 
void puertaEstaAbierta(String mensaje) {
   manejarEstadoPuerta(mensaje, HIGH);
}

//private 
void puertaEstaCerrada(String mensaje) {
  manejarEstadoPuerta(mensaje, LOW);
}




//private
void verificarSiLaPuertaEstaAbiertaOCerrada() {
  valorSensor = digitalRead(PIN_SENSOR_MAGNETICO);
  if (valorSensor == CERRADO) {
    if (seEnvioMensaje == CERRADO) {
      puertaEstaCerrada("Se cerro la puerta!!");
    }
  } else {
    if (seEnvioMensaje == ABIERTO) {
      puertaEstaAbierta("Se abrio la puerta!!");
    }
  }
}



void sePrendioElDispositivo() {
  banderaEstadoDelDispositivo = !banderaEstadoDelDispositivo;
  digitalWrite(PIN_LED_VERDE, HIGH); //apagamos el led interno

  Servidor::iniciarServidor();

  if (digitalRead(PIN_SENSOR_MAGNETICO) == ABIERTO) {
    puertaEstaAbierta("Se inicio el sensor con la puerta abierta!!");
  } else {
    puertaEstaCerrada("Se inicio el sensor con la puerta cerrada!!");
  }
}


void seApagoElDispositivo() {
  banderaEstadoDelDispositivo = !banderaEstadoDelDispositivo;
  if (digitalRead(PIN_SENSOR_MAGNETICO) == CERRADO) {
    puertaEstaCerrada("Se apago el sensor con la puerta cerrada!!");
  } else {
    puertaEstaAbierta("Se apago el sensor con la puerta abierta!!");
  }

  digitalWrite(PIN_LED_ROJO, LOW); //apagamos el led interno
  digitalWrite(PIN_LED_VERDE, LOW); //apagamos el led interno

}


void initFuncionalidadDelProyectoDelSensor() {
  if (!estaEncendido(PIN_BOTON) ) {
    if (banderaEstadoDelDispositivo) {
      seApagoElDispositivo();
    }
  } else {
    if (!banderaEstadoDelDispositivo) {
      sePrendioElDispositivo();
    } else {
      verificarSiLaPuertaEstaAbiertaOCerrada();
      Servidor::serverEnEscucha();
    }
  }
}


void initProductosExternos() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(PIN_LED_ROJO, OUTPUT);
  pinMode(PIN_LED_VERDE, OUTPUT);
  pinMode(PIN_BOTON, INPUT);
  pinMode(PIN_SENSOR_MAGNETICO, INPUT_PULLUP);
  digitalWrite(LED_BUILTIN, HIGH); //mientras se esta conectandose al wifi va a estar apagado
  digitalWrite(PIN_LED_VERDE, HIGH);//cuando se inicia el programa por defecto la luz se prende, debido a que cualquier producto cuando se enchufa se prende
}


#endif
