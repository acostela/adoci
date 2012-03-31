/* 
 * File:   fase_ataque_armas.h
 * Author: asce
 *
 * Created on 28 de marzo de 2012, 0:35
 */

#ifndef FASE_ATAQUE_ARMAS_H
#define	FASE_ATAQUE_ARMAS_H
#include "hexagono_position.h"
#include "funcs.h"
#include <fstream>

using namespace std;
/* Datos para el disparo de un arma */
class arma_fuego {
public:
    int localizacion;
    int slot;
    bool doble_cadencia;
    int loc_municion;
    int slot_municion;
    hexagono_pos objetivo;
    int tipo_objetivo;

    arma_fuego() {
        localizacion = 0;
        slot = 0;
        doble_cadencia = false;
        loc_municion = -1;
        slot_municion = -1;
        objetivo.fila = 0;
        objetivo.columna = 0;
        tipo_objetivo = 0;
    }
};

/* Datos para la fase de ataque con armas */
class ataque_armas_t {
public:
    bool coger_garrote;
    hexagono_pos objetivo;
    int num_armas;
    arma_fuego armas_mech[20];

    ataque_armas_t();
    void salida(string numJ);
};


#endif	/* FASE_ATAQUE_ARMAS_H */

