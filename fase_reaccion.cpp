/* 
 * File:   fase_reaccion.cpp
 * Author: asce
 * 
 * Created on 28 de marzo de 2012, 0:35
 */

#include "fase_reaccion.h"

reaccion_t::reaccion_t() {
    encaramiento = 0;
}

void reaccion_t::salida(string numJ) {
    /* Crear el archivo de salida */
    string cad = "accionJ" + numJ + ".sbt";
    string accion;
    ofstream out(cad.c_str());
    out.open(cad.c_str());
    /* Linea 1: Cambio de encaramiento */
    switch (encaramiento) {
        case ENC_IGUAL:
            accion = accion + "Igual\n";
            break;
        case ENC_IZQUIERDA:
            accion = accion + "Izquierda\n";
            break;
        case ENC_DERECHA:
            accion = accion + "Derecha\n";
            break;
    }
    /* Cerrar el archivo */
    out << accion;
    out.close();
}

