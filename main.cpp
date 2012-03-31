/* 
 * File:   main.cpp
 * Author: asce
 *
 * Created on 25 de mayo de 2010, 16:05
 */

#include "OpcionesJuego.h"
#include "infoMechs.h"
#include "infoMapa.h"
#include "acciones.h"
#include <fstream>
#include <cstdlib>
#include "node.h"

/*
 * 
 */
ofstream out_log;
string flog;

string cadtoStr(char* cad) {
    string s(cad);
    return s;
}

int main(int argc, char** argv) {

    if (argc != 3) {
        cerr << "Error, numero de argumentos incorrecto." << endl;
        return (EXIT_FAILURE);
    }

    flog = "";
    char cad[50];
    ofstream out_log;
    out_log.open("flog.txt");


    //    f_log = fopen("log.txt","a");
    time_t tiempo;
    time(&tiempo);
    sprintf(cad, "%s : Inicio fase \n", ctime(&tiempo));
    flog += cad;

    string numJ = argv[1]; //Leido desde la linea de comandos
    string nombreFase = argv[2];

    time(&tiempo);
    sprintf(cad, "%s : Fase: %s \n", ctime(&tiempo), nombreFase.c_str());
    flog += cad;


    string f_mechs = "mechsJ";
    string f_map = "mapaJ";
    string f_config = "configJ";


    f_mechs = f_mechs + numJ + ".sbt";
    f_map = f_map + numJ + ".sbt";
    f_config = f_config + numJ + ".sbt";
    OpcionesJuego inf_juego;
    infoMechs inf_mechs(atoi(numJ.c_str()));
    infoMapa inf_mapa;

    acciones acs(numJ, &inf_mapa, &inf_mechs, &inf_juego);

    inf_mechs.leeFich(f_mechs);

    inf_juego.leeFich(f_config);

    inf_mapa.leeFich(f_map);
    node destino(14, 9,1, &inf_mapa, inf_mechs.mechJugador->defMechInfo->toneladas);

    printf("Dest: %i\n",&destino);
    node inicio(14, 8,2,&destino, &inf_mapa, inf_mechs.mechJugador->defMechInfo->toneladas);
    aStar(&inicio,&destino,&inf_mapa, inf_mechs.mechJugador->defMechInfo->toneladas);
    //inicio.expand();



    
    acs.salida(nombreFase);
 /*
  
  //   usleep(2000000);


    
    time(&tiempo);
    sprintf(cad,"%s : Fin de fase.\n",ctime(&tiempo));
    flog+=cad;
    out_log<<flog;
    out_log.close();
    cout<<"Fin"<<endl;
    cin.get();

     */
    return (EXIT_SUCCESS);
}

