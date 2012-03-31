/* 
 * File:   movimiento.h
 * Author: asce
 *
 * Created on 29 de febrero de 2012, 14:50
 */

#ifndef MOVIMIENTO_H
#define	MOVIMIENTO_H

#include <vector>
#include "fase_movimiento.h"
#include "infoMapa.h"
using namespace std;

class node {
public:
    node();
    node(node * padr, int fila, int columna, int orienta, float heur);
    node(int fila,int columna,int orienta,infoMapa* map,int pesoMech);
    node(int fila,int columna,int orienta,node * destino,infoMapa* map,int pesoMech);
    node(node * ini, node * dest, infoMapa* map, int pesoMech);
    void showInfo();
    void showPath();
    void showInfoHijos();
    string getSecuencia(float PM,movimiento_t * mov);
    //node(const node& orig);
    vector <node *> hijos;
    void expand();
    virtual ~node();
    float f();
    float g();
    float h();
    bool operator==(const node & nodo);
    node& operator=(const node & nodo);
    node * padre;

private:
    node * inicio;
    node * destino;
    infoMapa* mapa;
    float hVal;

    int peso;
    int fil;
    int col;
    int orientacion;
    float costeDesdePadre();


};

void nodoEnEsaDireccion(int fila, int columna, int direccion, int & filaSiguiente, int & colSiguiente);

void aStar(node * inicio, node * destino, infoMapa *mapa, int tonelaje);


#endif	/* MOVIMIENTO_H */

