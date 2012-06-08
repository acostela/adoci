/* 
 * File:   fase_reaccion.cpp
 * Author: asce
 * 
 * Created on 28 de marzo de 2012, 0:35
 */

#include "fase_reaccion.h"
#include "infoMechs.h"

using namespace std;

reaccion_t::reaccion_t(infoMapa* inf_mapa, infoMechs * inf_mechs) {
    mapa = inf_mapa;
    mechs = inf_mechs;
    encaramiento = 0;
}

void reaccion_t::salida(string numJ) {
    /* Crear el archivo de salida */
    string cad = "accionJ" + numJ + ".sbt";
    string accion="";
    ofstream out;
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
int reaccion_t::objetivoEncaramiento(){
    int auxColumna;
    int auxFila;
    int columnaJugador;
    int filaJugador;
    int score_objetivo[mechs->nMechs - 1]; //Aqui se guardara en cada dimension el Score de cada objetivo para elegir el mejor al que encararse
    int objetivo;
    int scoreaux;

    columnaJugador = mechs->mechJugador->pos_Hexagono.columna;
    filaJugador = mechs->mechJugador->pos_Hexagono.fila;

    for (int i = 0; i < mechs->nMechs - 1; i++) {
        score_objetivo[i] = 0;
    }

    for (int i = 0; i < mechs->nMechs - 1; i++) {
        auxColumna = mechs->iMechVector[i]->pos_Hexagono.columna;
        auxFila = mechs->iMechVector[i]->pos_Hexagono.fila;
        if (mechs->iMechVector[i]->operativo == true) 
            score_objetivo[i] = distancia_hexagonal(filaJugador, columnaJugador, auxFila, auxColumna); //Se pone como Score la distancia del Mech con respecto al nuestro
    }

   // score_objetivo[mech_mas_debil] -= 1; //Si hay dos mechs a igual distancia pero uno esta mas daÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â±ado que otro disparamos a ÃƒÆ’Ã†â€™Ãƒâ€šÃ‚Â©ste.
    scoreaux = score_objetivo[0];

    for (int i = 1; i < mechs->nMechs; i++) {
        if (score_objetivo[i] < scoreaux) {
            scoreaux = score_objetivo[i];
            objetivo = i;
        }
    }
    return objetivo;
}

void reaccion_t::reaccion_accion() {
    int colum_ene, colum_jug;
    int fila_ene, fila_jug;
    int objetivo_mech;
    encaramiento = mechs->mechJugador->encaramiento_mech;

    objetivo_mech = objetivoEncaramiento();
    colum_jug = mechs->mechJugador->pos_Hexagono.columna;
    fila_jug = mechs->mechJugador->pos_Hexagono.fila;
    colum_ene = mechs->iMechVector[objetivo_mech]->pos_Hexagono.columna;
    fila_ene = mechs->iMechVector[objetivo_mech]->pos_Hexagono.fila;

    if (fila_ene > fila_jug) { //Hay que girarse hacia 5-4-3
        if (colum_ene == colum_jug) { //Hay que girarse a 4
            if (encaramiento < 4)
                encaramiento = ENC_DERECHA;
            else if (encaramiento == 4)
                encaramiento = ENC_IGUAL;
            else
                encaramiento = ENC_IZQUIERDA;
        } else if (colum_ene > colum_jug) { //Hay que girarse a 3
            if (encaramiento == 3)
                encaramiento = ENC_IGUAL;
            else if (encaramiento > 3) {
                encaramiento = ENC_DERECHA;
            } else {
                encaramiento = ENC_IZQUIERDA;
            }
        } else if (colum_ene < colum_jug) { //Hay que girarse hacia 5
            if (encaramiento == 5)
                encaramiento = ENC_IGUAL;
            else if (encaramiento == 6 || encaramiento == 1)
                encaramiento = ENC_IZQUIERDA;
            else
                encaramiento = ENC_DERECHA;
        }

    } else if (fila_ene < fila_jug) { //Hay que girarse hacia 6-1-2
        if (colum_ene == colum_jug) { //Hay que girarse hacia 1
            if (encaramiento == 1)
                encaramiento = ENC_IGUAL;
            else if (encaramiento == 2 || encaramiento == 3)
                encaramiento = ENC_IZQUIERDA;
            else
                encaramiento = ENC_DERECHA;
        } else if (colum_ene > colum_jug) { //Hay que girarse hacia 2
            if (encaramiento == 2)
                encaramiento = ENC_IGUAL;
            else if (encaramiento == 3 || encaramiento == 4)
                encaramiento = ENC_IZQUIERDA;
            else
                encaramiento = ENC_DERECHA;
        } else if (colum_ene < colum_jug) { //Hay que girarse hacia 6
            if (encaramiento == 6)
                encaramiento = ENC_IGUAL;
            else if (encaramiento == 1 || encaramiento == 2)
                encaramiento = ENC_IZQUIERDA;
            else
                encaramiento = ENC_DERECHA;
        }
    } else if (fila_ene == fila_jug) { //hay que girarse a 2-3 o 6-5
        if (colum_ene > colum_jug) { //Hay que girarse a 2-3
            if (encaramiento == 2 || encaramiento == 3)
                encaramiento = ENC_IGUAL;
            else if (encaramiento == 4 || encaramiento == 5)
                encaramiento = ENC_IZQUIERDA;
            else
                encaramiento = ENC_DERECHA;
        } else if (colum_ene < colum_jug) { //Hay que girarse a 6-5
            if (encaramiento == 6 || encaramiento == 5)
                encaramiento = ENC_IGUAL;
            else if (encaramiento == 1 || encaramiento == 2)
                encaramiento = ENC_IZQUIERDA;
            else
                encaramiento = ENC_DERECHA;
        }

    }


}
