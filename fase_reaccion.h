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
#include "infoMapa.h"
#include "infoMechs.h"

using namespace std;

/* Datos para la fase de reacción */
class reaccion_t {
public:
    int encaramiento;
    infoMapa* mapa;
    infoMechs * mechs;
    
    reaccion_t(infoMapa* inf_mapa, infoMechs * inf_mechs);
    void reaccion_accion() ;
    int objetivoEncaramiento();
    void salida(string numJ);
};

#endif	/* FASE_REACCION_H */

