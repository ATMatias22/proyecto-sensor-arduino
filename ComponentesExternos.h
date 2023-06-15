#ifndef ComponentesExternos_H
#define ComponentesExternos_H

#define PIN_LED_ROJO D5 //LED QUE SE PRENDE O APAGA SEGUN EL ESTADO DE LA PUERTA
#define PIN_SENSOR_MAGNETICO D7
#define PIN_LED_VERDE D1 //LED QUE SE PRENDE O APAGA SI EL PRODUCTO ESTA ENCENDIDO O APAGADO
#define PIN_BOTON D2

class ComponentesExternos {

    // Constructor privado para evitar instanciación directa
  private:
    static int pinLedRojo;
    static int pinLedVerde;
    static int pinSensorMagnetico;
    static int pinBoton;


  private:
    ComponentesExternos() {

    }

  public:
    static void setup() {
      pinMode(LED_BUILTIN, OUTPUT);
      pinMode(pinLedRojo, OUTPUT);
      pinMode(pinLedVerde, OUTPUT);
      pinMode(pinBoton, INPUT);
      pinMode(pinSensorMagnetico, INPUT_PULLUP);
      digitalWrite(LED_BUILTIN, HIGH); //mientras se esta conectandose al wifi va a estar apagado
      digitalWrite(pinLedVerde, HIGH);//cuando se inicia el programa por defecto la luz se prende, debido a que cualquier producto cuando se enchufa se prende
    }

    static int getEstadoLedRojo() {
      return digitalRead(ComponentesExternos::pinLedRojo);
    }

    static void encenderLedRojo() {
      digitalWrite(ComponentesExternos::pinLedRojo, HIGH);
    }

    static void apagarLedRojo() {
      digitalWrite(ComponentesExternos::pinLedRojo, LOW);
    }

    static int getEstadoLedVerde() {
      return digitalRead(ComponentesExternos::pinLedVerde);
    }

    static void encenderLedVerde() {
      digitalWrite(ComponentesExternos::pinLedVerde, HIGH);
    }

    static void apagarLedVerde() {
      digitalWrite(ComponentesExternos::pinLedVerde, LOW);
    }

    static int getEstadoBoton() {
      return digitalRead(ComponentesExternos::pinBoton);
    }

    static int getEstadoSensorMagnetico() {
      return digitalRead(ComponentesExternos::pinSensorMagnetico);
    }
};

int ComponentesExternos::pinLedRojo = PIN_LED_ROJO;
int ComponentesExternos::pinLedVerde = PIN_LED_VERDE;
int ComponentesExternos::pinSensorMagnetico = PIN_SENSOR_MAGNETICO;
int ComponentesExternos::pinBoton = PIN_BOTON;

#endif
