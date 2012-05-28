/* 
 * File:   nodoArea.h
 * Author: asce
 *
 * Created on 27 de mayo de 2012, 2:04
 */

#ifndef NODOAREA_H
#define	NODOAREA_H

#include <vector>

class nodoArea {
public:
    int fila;
    int columna;
    float distancia;
    nodoArea();
    nodoArea(int f, int c, float d);
    nodoArea(const nodoArea& orig);
    void show()const;
    virtual ~nodoArea();
private:

};


void showNodosArea(const std::vector<nodoArea> & nodosArea);

#endif	/* NODOAREA_H */

