/* 
 * File:   funcs.h
 * Author: asce
 *
 * Created on 12 de octubre de 2011, 18:53
 */

#ifndef FUNCS_H
#define	FUNCS_H

#include <sstream>
#include "hexagono_position.h" 
//#include "node.h"

#define MOVIMIENTO_INVALIDO 99999

using namespace std;
//Para las clases componentes
enum localizacion_t {
    BI, BD, PI, PD, TC, TI, TD, CAB
};
struct municion {
    localizacion_t localizacion; /* (BI,BD,PI,PD,TC,TI,TD o CAB) */
    int slot; /* (0-5) si PI,PD o CAB. (0-11) en otro caso */
};
enum componente_t{
    VACIO,
    ARMA,
    MUNICION,
    EQUIPO,
    ACTUADOR,
    ARMADURA,
    ARMAFISICA
};
//Para los tipos de armas 
enum arma_type_t{
    ENERGIA=1,
    BALISTICA=2,
    MISILES=3
};
enum{
    ABIERTO,
    PAVIMENTADO,
    AGUA,
    PANTANO
};

enum{
    ESCOMBROS,
    B_LIGERO,
    B_DENSO,
    E_LIGERO,
    E_MEDIO,
    E_PESADO,
    E_REFORZADO,
    BUNKER,
    NADA=255
};


enum tipo_movimiento {
    INMOVIL,
    ANDAR,
    CORRER,
    SALTAR
};

enum local_arma{
    BI_A,             /* Brazo izquierdo */
    BD_A,             /* Brazo derecho */
    PI_A,             /* Pierna izquierda */
    PD_A,             /* Pierna derecha */
    TC_A,             /* Torso centro */
    TI_A,             /* Torso izquierda */
    TD_A,             /* Torso derecha */
    CAB_A,            /* Cabeza */
    BIBD_A            /* Brazo izquierdo + Brazo derecho                    (sÃƒÂ³lo para ataque fÃƒÂ­sico con garrote) */
};

enum estrat_mov{
    ATACAR,
    HUIR
};

enum paso {
    MOV_ADELANTE,
    MOV_ATRAS,
    MOV_IZQUIERDA,
    MOV_DERECHA,
    MOV_LEVANTARSE,
    MOV_TIERRA
};

enum encaramiento {
    ENC_IGUAL,
    ENC_IZQUIERDA,
    ENC_DERECHA
};

enum tipo_objetivo {
    MECH,
    HEXAGONO,
    NINGUNO
};

enum angulo{
    FRONTAL=1,
    TRASERO,
    IZQUIERDO,
    DERECHO
};

enum booleanos{
    FALSE=0,
    TRUE
};

string itoStr(int num);

//int strtoInt(string cadena);



#endif	/* FUNCS_H */
