
#ifndef PRENDER_O_APAGAR_FUNCIONALIDAD_H
#define PRENDER_O_APAGAR_FUNCIONALIDAD_H
#include "EnviarMensaje.h"
#include "ComponentesExternos.h"

class EstadoDeSensor {
  private:
    static int nuevoEstadoDelBoton; //variables que sirven para detectar si se toco el boton
    static int estaPrendido; //cuando inicia el programa por defecto va a realizar la funcionalidad de detectar si el sensor esta abierto o cerrado
    static int viejoEstadoDelBoton; //variables que sirven para detectar si se toco el boton
    static int banderaEstadoDelDispositivo;
    static int CERRADO;
    static int ABIERTO;

  public:
    static boolean estaEncendido() {
     
      EstadoDeSensor::nuevoEstadoDelBoton = ComponentesExternos::getEstadoBoton();
      if (EstadoDeSensor::nuevoEstadoDelBoton != EstadoDeSensor::viejoEstadoDelBoton) {
        EstadoDeSensor::viejoEstadoDelBoton = EstadoDeSensor::nuevoEstadoDelBoton;
        if (EstadoDeSensor::nuevoEstadoDelBoton == HIGH) {
          EstadoDeSensor::estaPrendido = !EstadoDeSensor::estaPrendido;
        }
      }
      return EstadoDeSensor::estaPrendido;
    }

    static void sePrendioElDispositivo() {
      EstadoDeSensor::banderaEstadoDelDispositivo = !EstadoDeSensor::banderaEstadoDelDispositivo;
      ComponentesExternos::encenderLedVerde();

      if (ComponentesExternos::getEstadoSensorMagnetico() == EstadoDeSensor::ABIERTO) {
        EnviarMensaje::puertaEstaAbierta("Se inicio el sensor con la puerta abierta!!");
      } else {
        EnviarMensaje::puertaEstaCerrada("Se inicio el sensor con la puerta cerrada!!");
      }
    }

    static void seApagoElDispositivo() {
      EstadoDeSensor::banderaEstadoDelDispositivo = !EstadoDeSensor::banderaEstadoDelDispositivo;
      if (ComponentesExternos::getEstadoSensorMagnetico() == EstadoDeSensor::CERRADO) {
        EnviarMensaje::puertaEstaCerrada("Se apago el sensor con la puerta cerrada!!");
      } else {
        EnviarMensaje::puertaEstaAbierta("Se apago el sensor con la puerta abierta!!");
      }
      ComponentesExternos::apagarLedRojo();
      ComponentesExternos::apagarLedVerde();
    }

    static void setEstadoSensor(int estadoSensor) {
      EstadoDeSensor::estaPrendido = estadoSensor;
    }
    static int getEstadoSensor() {
      return EstadoDeSensor::estaPrendido;
    }

    static void setViejoEstadoDelBoton(int viejoEstadoDelBoton) {
      EstadoDeSensor::viejoEstadoDelBoton = viejoEstadoDelBoton;
    }
    static int getViejoEstadoDelBoton() {
      return EstadoDeSensor::viejoEstadoDelBoton;
    }

    static void setBanderaEstadoDelDispositivo(int bandera) {
      EstadoDeSensor::banderaEstadoDelDispositivo = bandera;
    }
    static int getBanderaEstadoDelDispositivo() {
      return EstadoDeSensor::banderaEstadoDelDispositivo;
    }
};

int EstadoDeSensor::nuevoEstadoDelBoton = 0;
int EstadoDeSensor::viejoEstadoDelBoton = 0;
int EstadoDeSensor::estaPrendido = 1;
int EstadoDeSensor::banderaEstadoDelDispositivo = 0;
int EstadoDeSensor::CERRADO = 0;
int EstadoDeSensor::ABIERTO = 1;
#endif
