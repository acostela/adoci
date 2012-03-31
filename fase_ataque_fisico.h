/* 
 * File:   fase_ataque_fisico.h
 * Author: asce
 *
 * Created on 28 de marzo de 2012, 0:36
 */

#ifndef FASE_ATAQUE_FISICO_H
#define	FASE_ATAQUE_FISICO_H
#include "hexagono_position.h"
#include "funcs.h"
#include <fstream>

using namespace std;
/* Datos para el uso de un arma fÃ­sica */
class arma_fisica {
public:
    int localizacion;
    int slot;
    hexagono_pos objetivo;
    int tipo_objetivo;

    arma_fisica() {
        localizacion = 0;
        slot = 0;
        objetivo.fila = 0;
        objetivo.columna = 0;
        tipo_objetivo = 0;

    }
};

/* Datos para la fase de ataque fÃ­sico */
class ataque_fisico_t {
public:
    int num_armas;
    arma_fisica armas[4];

    ataque_fisico_t() {
        num_armas = 0;
    }
    void salida(string numJ);
};


#endif	/* FASE_ATAQUE_FISICO_H */

