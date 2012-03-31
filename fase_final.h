/* 
 * File:   fase_final.h
 * Author: asce
 *
 * Created on 28 de marzo de 2012, 0:36
 */

#ifndef FASE_FINAL_H
#define	FASE_FINAL_H
#include <iostream>
#include "funcs.h"
#include <fstream>
using namespace std;


/* Datos para la fase final */
class final_t {
public:
    int radiadores_off;
    int radiadores_on;
    bool soltar_garrote;
    int expulsar;
    municion *expulsada;

    final_t() {
        radiadores_off = 0;
        radiadores_on = 0;
        soltar_garrote = false;
        expulsar = 0;
    }
    void salida(string numJ);
};


#endif	/* FASE_FINAL_H */

