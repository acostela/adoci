/* 
 * File:   infoMapa.h
 * Author: asce
 *
 * Created on 25 de mayo de 2010, 17:36
 */

#ifndef _INFOMAPA_H
#define	_INFOMAPA_H


#include <fstream>
#include <iostream>
#include <cstdlib>
#include "infoMechs.h"

using namespace std;
class hexagono_t {
public:
    hexagono_t(int f,int c);
    int fila;
    int columna;
    int nivel;
    int terreno; //0-ABIERTO, 1-PAVIMENTADO, 2-AGUA, 3-PANTANOSO
    int objetoTerreno; //0-escombros, 1-bosque ligero, 2-bosque denso,
    //3-edificio ligero,4-edificio medio, 5-edificio pesado,
    //6-edificio reforzado, 7-búnker, 255-nada
    int FCE; //>=0
    bool derrumbado;
    bool fuego;
    bool humo;
    int num_garrotes; //>=0
    bool rioCentroCara[6]; //NOTA: numero de cara<=>indice+1
    bool carreteraCentroCara[6]; //NOTA: numero de cara<=>indice+1
    //////


};

class infoMapa {
public:
    int filas; //alto
    int columnas; //ancho
    int modo;
    hexagono_t*** mapa; //Matriz de punteros a hexagonos

    infoMapa();
    infoMapa(const infoMapa& orig);
    virtual ~infoMapa();
    void inicializarPath();
    void inicializarMapa();
    void leeFich(string fichero);
    int coste_mov_ady(int f_origen,int c_origen,int f_objetivo,int c_objetivo, int toneladas);
    int coste_mov_giro(int f,int c);
    int distancia_casillas(hexagono_pos casilla_ini, hexagono_pos casilla_obj);
    float distancia(int col_ini, int fil_ini, int col_obj, int fil_obj);

    int direccion_objetivo(hexagono_pos origen, hexagono_pos destino);
    bool casilla_objetivo (hexagono_pos casilla, int direccion,hexagono_pos& objetivo);

private:

    bool s2bool(string cad) {
        if (cad.compare(0,4,"True")==0)
            return true;
        else
            return false;
    }





};

#endif	/* _INFOMAPA_H */

