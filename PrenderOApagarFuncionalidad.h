
#ifndef PRENDER_O_APAGAR_FUNCIONALIDAD_H
#define PRENDER_O_APAGAR_FUNCIONALIDAD_H


int nuevoEstadoDelBoton = 0; //variables que sirven para detectar si se toco el boton
int viejoEstadoDelBoton = 0; //variables que sirven para detectar si se toco el boton
int estaPrendido = 1; //cuando inicia el programa por defecto va a realizar la funcionalidad de detectar si el sensor esta abierto o cerrado



//public
boolean estaEncendido(int PIN_BOTON) {
  nuevoEstadoDelBoton = digitalRead(PIN_BOTON);
  if (nuevoEstadoDelBoton != viejoEstadoDelBoton) {
    viejoEstadoDelBoton = nuevoEstadoDelBoton;
    if (nuevoEstadoDelBoton == HIGH) {
      estaPrendido = !estaPrendido;
    }
  }
  return estaPrendido;
}

#endif
