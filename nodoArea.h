/* 
 * File:   nodoArea.h
 * Author: asce
 *
 * Created on 27 de mayo de 2012, 2:04
 */

#ifndef NODOAREA_H
#define	NODOAREA_H

#include <vector>
#include "infoMapa.h"
#include "funcs.h"
#include "hexagono_position.h"
#include <sstream>


class nodoArea {
public:
    int fila;
    int columna;
    float distancia;
    float evaluacionHuir;
    nodoArea();
    nodoArea(int f, int c, float d);
    nodoArea(const nodoArea& orig);
    void show()const;
    bool adyacenteNodoArea(const nodoArea & n,infoMapa* mapa)const;
    virtual ~nodoArea();
    vector<nodoArea> getAdyacentes(infoMapa * mapa)const;
    bool operator==(const nodoArea & n)const;
    bool pertenece(const vector<nodoArea> & nodos )const;
    void evaluaHuir(int f,int c, int enc);
private:

};
typedef vector<nodoArea> nodeVector;

void posAtaque(int niveles, vector<nodeVector> & anillosJugador, vector<nodeVector> & anillosObjetivo, int & fil_dest, int & col_dest, infoMapa * mapa);
void cobertura(int niveles, vector<nodeVector> & anillos, int & fil_dest, int & col_dest, int f_obj, int c_obj, int enc,infoMapa * mapa);
void coberturaSalto(int niveles, vector<nodeVector> & anillos, int & fil_dest, int & col_dest, int f_obj, int c_obj, int enc,infoMapa * mapa);
vector<nodoArea> adyacentes(const vector<nodoArea> & anillo,infoMapa * mapa);
vector<nodoArea> getAnillo(const vector<nodoArea> & anillo,const vector<nodoArea> & anillo_interior,infoMapa * mapa);
vector<nodeVector> getAnillos(const nodoArea & centro,infoMapa * mapa);//5 anillos
vector<nodoArea> check_linea(const nodoArea & ini, const nodoArea & dest, int numJ);
bool check_mov_salto(const vector<nodoArea>& nodos,int PS,infoMapa * mapa);
bool check_salto(const nodoArea & ini, const nodoArea & dest, infoMapa *mapa);
bool perteneceAnillos(int niveles, vector<nodeVector> & anillos, int f, int c);

void showNodosArea(const std::vector<nodoArea> & nodosArea);
#endif	/* NODOAREA_H */

