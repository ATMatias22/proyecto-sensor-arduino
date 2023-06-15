#ifndef ENVIAR_MENSAJE_H
#define ENVIAR_MENSAJE_H

#include "PrenderOApagarFuncionalidad.h"
#include "Request.h"
#include "ComponentesExternos.h"

class EnviarMensaje {
  private:
    static int valorSensor;
    static int CERRADO;
    static int ABIERTO;
    static int seEnvioMensaje;

  private:
    EnviarMensaje() {

    }
    
    static void manejarEstadoPuerta(String mensaje, bool puertaAbierta) {
      Serial.println(mensaje);
      puertaAbierta ? ComponentesExternos::encenderLedRojo(): ComponentesExternos::apagarLedRojo();
      EnviarMensaje::seEnvioMensaje = puertaAbierta ? EnviarMensaje::CERRADO : EnviarMensaje::ABIERTO;
      Request::enviarMensaje(mensaje);
    }

  public:
    static void puertaEstaAbierta(String mensaje) {
      EnviarMensaje::manejarEstadoPuerta(mensaje, HIGH);
    }

    static void puertaEstaCerrada(String mensaje) {
      EnviarMensaje::manejarEstadoPuerta(mensaje, LOW);
    }

    static void verificarSiLaPuertaEstaAbiertaOCerrada() {
      EnviarMensaje::valorSensor = ComponentesExternos::getEstadoSensorMagnetico();
      if (EnviarMensaje::valorSensor == EnviarMensaje::CERRADO) {
        if (EnviarMensaje::seEnvioMensaje == EnviarMensaje::CERRADO) {
          EnviarMensaje::puertaEstaCerrada("Se cerro la puerta!!");
        }
      } else {
        if (EnviarMensaje::seEnvioMensaje == EnviarMensaje::ABIERTO) {
          EnviarMensaje::puertaEstaAbierta("Se abrio la puerta!!");
        }
      }
    }


};

int EnviarMensaje::valorSensor = 0;
int EnviarMensaje::CERRADO = 0;
int EnviarMensaje::ABIERTO = 1;
int EnviarMensaje::seEnvioMensaje = 0;

#endif
