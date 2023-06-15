
#ifndef FUNCIONALIDAD_DEL_PROYECTO_DEL_SENSOR_H
#define FUNCIONALIDAD_DEL_PROYECTO_DEL_SENSOR_H

#include "Servidor.h"
#include "PrenderOApagarFuncionalidad.h"


class Sensor {
  public:
    static void initFuncionalidadDelProyectoDelSensor() {
      Servidor::serverEnEscucha();
      if (!EstadoDeSensor::estaEncendido() ) {
        if (EstadoDeSensor::getBanderaEstadoDelDispositivo()) { //esta encendido false
          EstadoDeSensor::seApagoElDispositivo();
        }
      } else {
        if (!EstadoDeSensor::getBanderaEstadoDelDispositivo()) { //esta encendido true
          EstadoDeSensor::sePrendioElDispositivo();
        } else {
          EnviarMensaje::verificarSiLaPuertaEstaAbiertaOCerrada();
        }
      }
    }

};

#endif
