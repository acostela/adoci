/* 
 * File:   fase_movimiento.h
 * Author: asce
 *
 * Created on 28 de marzo de 2012, 0:34
 */

#ifndef FASE_MOVIMIENTO_H
#define	FASE_MOVIMIENTO_H
#include <fstream>
#include <iostream>
#include <vector>
#include "node.h"
#include "funcs.h"
#include "infoMapa.h"
#include "infoMechs.h"

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
    infoMapa* mapa;
    infoMechs * mechs;

    movimiento_t(infoMapa* inf_mapa, infoMechs * inf_mechs);
    int tipo_movim(const vector<node>& nodos);
    int estrategia_movimiento();
    void getDestino(int& fil_dest, int & col_dest, int & lado_dest, int estrategia);
    void salida(string numJ);
    void logica_movimiento();
    int getTipoMov(const node & n1, const node & n2);
    void getSecuenciaPasos(const vector<node> & nodos,int PM);
private:
    bool check_mov_correr(const vector<node>& nodos);


};

#endif	/* FASE_MOVIMIENTO_H */

