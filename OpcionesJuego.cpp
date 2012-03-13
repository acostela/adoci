/* 
 * File:   OpcionesJuego.cpp
 * Author: asce
 * 
 * Created on 25 de mayo de 2010, 16:05
 */

#include "OpcionesJuego.h"

OpcionesJuego::OpcionesJuego() {
}

OpcionesJuego::OpcionesJuego(const OpcionesJuego& orig) {
}

OpcionesJuego::~OpcionesJuego() {
}

void OpcionesJuego::leeFich(string fichero){
    string cad;
     ifstream fich(fichero.c_str());//Creacion y apertura
		if(!fich){
			cerr << "\nNo es posible abrir " << fichero <<"\n";
                        exit(1);
		}
    
    fich.ignore(1000,'\n');//Ignoramos número mágico
    fich >> cad;
    incendios_permitidos=s2bool(cad);

    fich >> cad;
    viento_permitido=s2bool(cad);

    fich >> direccion_viento;//INT 1 y 6 o -1
    if(direccion_viento!=-1 && (direccion_viento<1 || direccion_viento>6)){
        cerr << "\nValor de dirección del viento incorrecto, debe de estar entre 1 y 6 o ser -1"<<endl;
        exit(1);
    }
    fich >>cad;
    ataques_fisicos_permitidos=s2bool(cad);

    fich >> cad;
    fase_calor=s2bool(cad);

    fich >>cad;
    devastar_bosques=s2bool(cad);

    fich >>cad;
    derrumbar_edificios=s2bool(cad);

    fich >>cad;
    chequeos_pilotaje=s2bool(cad);

    fich >>cad;
    chequeo_danho=s2bool(cad);

    fich >>cad;
    chequeo_desconexion=s2bool(cad);

    fich >>cad;
    impactos_criticos=s2bool(cad);

    fich >>cad;
    explosion_municion=s2bool(cad);

    fich >>cad;
    apagar_radiadores=s2bool(cad);

    fich >>cad;
    limitar_tiempo_respuesta=s2bool(cad);

    fich >> valor_limite_tiempo;//entero positivo o -1
    if(valor_limite_tiempo!=-1 && valor_limite_tiempo<0){
        cerr << "\nValor de tiempo incorrecto, debe ser entero positivo o -1"<<endl;
        exit(1);
    }


}

