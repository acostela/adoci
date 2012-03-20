/* 
 * File:   acciones.h
 * Author: asce
 *
 * Created on 31 de mayo de 2010, 14:21
 */

#ifndef _ACCIONES_H
#define	_ACCIONES_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <cstdlib>
#include "funcs.h"
#include "infoMechs.h"
#include "infoMapa.h"
#include "OpcionesJuego.h"

using namespace std;

extern string flog;


enum local_arma{
    BI_A,             /* Brazo izquierdo */
    BD_A,             /* Brazo derecho */
    PI_A,             /* Pierna izquierda */
    PD_A,             /* Pierna derecha */
    TC_A,             /* Torso centro */
    TI_A,             /* Torso izquierda */
    TD_A,             /* Torso derecha */
    CAB_A,            /* Cabeza */
    BIBD_A            /* Brazo izquierdo + Brazo derecho                    (sólo para ataque físico con garrote) */
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
class node{
public:
    int g;
    int h;
    int f(){return g+h;}
    node* padre;
    bool walkable;
};


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

/* Datos para el uso de un arma física */
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

/********* Datos para las distintas fases ***********/

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

/* Datos para la fase de reacción */
class reaccion_t {
public:
    int encaramiento;

    reaccion_t();
    void salida(string numJ);
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

/* Datos para la fase de ataque físico */
class ataque_fisico_t {
public:
    int num_armas;
    arma_fisica armas[4];

    ataque_fisico_t() {
        num_armas = 0;
    }
    void salida(string numJ);
};

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

class acciones {
public:
    string numeroJugador;
    movimiento_t* mov;
    reaccion_t* reaccion;
    ataque_armas_t* armas;
    ataque_fisico_t* fisico;
    final_t* final;
    infoMapa* informacion_mapa;
    infoMechs* informacion_mechs;
    OpcionesJuego* informacion_juego;

    acciones(string numJ,infoMapa* mapa,infoMechs* mechs, OpcionesJuego* opts);
    acciones(const acciones& orig);
    virtual ~acciones();
    void salida(string cad);
    string mover(hexagono_pos destino);
    void reaccion_accion();
    void ataque_arma();
    int objetivoArmas();
    int obtenerLocalizacionMunicion(iMech mech, Componente_Mech arma);
    int obtenerSlotArma(iMech mech, Componente_Mech arma);
    int angulo_mech(int mech_obj);
    int buscar_municion(iMech mech, int cod_arma);
    int queda_municion(iMech mech, int codigo);
    //Movimiento
    int estrategia_movimiento();
    void reglas_movimiento();
    void confirmar_mov(int tipo_movimiento, hexagono_pos destino, int lado, int MASC, int tipo, int veces);
    void mov_huir(int num_jugador, int num_jugadores, int PM_INI, int tipo_mov);
    void actualizar_mov_candidatos(int PM, hexagono_pos casilla, int *candidatos, int toneladas, int tipo_mov);
    int func_direccion_giro (int encaramiento, int dir_objetivo);
    int func_coste_giro (int encaramiento, int dir_objetivo, int dir_giro);
    int lado_final_giro (int enc_ini, int dir_giro, int veces);
    int paso_huir(int* candidatos, int num_jugador, int mech_objetivo, int primer_mov);
	int obt_valor_obstaculos(hexagono_pos pos);
	int es_mejor(int LV1, int valor1, int LV2, int valor2);
	int linea_vision(int num_jugador, hexagono_pos origen, int nivel_origen,hexagono_pos destino, int nivel_destino);
	void mov_atacar(int num_jugador, int num_jugadores, int PM, int tipo_mov);
	int casilla_ocupada(int num_jugadores, hexagono_pos casilla);
	int mov_acercarse(int num_jugador, int mech_objetivo, int *candidatos, int PM);
	int obt_paso_anterior(int direccion);

 

private:
    bool dentroMapa(int fila, int columna);
    void astar_hex(int fila,int columna);
    void posiciones_adyacentes(int f,int c,int adyacentes[][2]);



};




#endif	/* _ACCIONES_H */

