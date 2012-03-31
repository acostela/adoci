/* 
 * File:   fase_movimiento.h
 * Author: asce
 *
 * Created on 28 de marzo de 2012, 0:34
 */

#ifndef FASE_MOVIMIENTO_H
#define	FASE_MOVIMIENTO_H
#include "funcs.h"
#include <fstream>
#include <iostream>
using namespace std;
/* Datos para la fase de movimiento */
class movimiento_t {
public:
    int tipo_movimiento;
    hexagono_pos destino;
    int lado;
    bool MASC;
    int pasos;
    int tipo[20];
    int veces[20];

    movimiento_t() {
        tipo_movimiento = 0;
        destino.fila = 0;
        destino.columna = 0;
        lado = 0;
        MASC = false;
        pasos = 0;
        for (int i = 0; i < 20; ++i) {
            tipo[i] = 0;
            veces[i] = 0;
        }
    }
    void salida(string numJ);
};

#endif	/* FASE_MOVIMIENTO_H */

