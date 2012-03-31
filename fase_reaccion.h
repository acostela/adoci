/* 
 * File:   fase_reaccion.h
 * Author: asce
 *
 * Created on 28 de marzo de 2012, 0:35
 */

#ifndef FASE_REACCION_H
#define	FASE_REACCION_H
#include "funcs.h"
#include <iostream>
#include <fstream>

using namespace std;

/* Datos para la fase de reacción */
class reaccion_t {
public:
    int encaramiento;

    reaccion_t();
    void salida(string numJ);
};

#endif	/* FASE_REACCION_H */

