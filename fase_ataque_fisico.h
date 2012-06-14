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
#include "infoMapa.h"
#include "infoMechs.h"

using namespace std;
/* Datos para el uso de un arma fÃƒÆ’Ã‚Â­sica */
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

/* Datos para la fase de ataque fÃƒÆ’Ã‚Â­sico */
class ataque_fisico_t {
public:
    int num_armas;
    arma_fisica armas[4];
    infoMapa* mapa;
    infoMechs * mechs;
    
    ataque_fisico_t(infoMapa* inf_mapa, infoMechs * inf_mechs);
    void salida(string numJ);
    void posiciones_adyacentes(int f, int c, int adyacentes[][2]);
    int objetivoFisico();
    int angulo_torso_enemigo(int mech_obj);
    int angulo_mech_enemigo(int mech_obj);
    int obtenerSlotArma(iMech *&mech, Componente_Mech arma);
    void ataque_fisico();
};


#endif	/* FASE_ATAQUE_FISICO_H */

