/* 
 * File:   fase_ataque_fisico.cpp
 * Author: asce
 * 
 * Created on 28 de marzo de 2012, 0:36
 */

#include "fase_ataque_fisico.h"

void ataque_fisico_t::salida(string numJ) {

    string cad = "accionJ" + numJ + ".sbt";
    string accion;
    ofstream out(cad.c_str());
    out.open(cad.c_str());

    /* Linea 1: NÃºmero de armas fÃ­sicas que se van a usar */
    accion = accion + itoStr(num_armas) + "\n";

    /* Para cada arma */
    for (int i = 0; i < num_armas; ++i) {
        /* LocalizaciÃ³n del arma fÃ­sica */
        switch (armas[i].localizacion) {
            case BI_A:
                accion = accion + "BI\n";
                break;
            case BD_A:
                accion = accion + "BD\n";
                break;
            case PI_A:
                accion = accion + "PI\n";
                break;
            case PD_A:
                accion = accion + "PD\n";
                break;
            case BIBD_A://ojooooooooooooooooooo declaraciones conflictivas ...
                accion = accion + "BIBD\n";
                break;
        }

        /* Slot del arma fÃ­sica */
        accion = accion + itoStr(armas[i].slot) + "\n";

        /* HexÃ¡gono objetivo del arma */
        accion = accion + armas[i].objetivo.stringPos() + "\n";

        /* Tipo de objetivo */
        switch (armas[i].tipo_objetivo) {
            case MECH:
                accion = accion + "Mech\n";
                break;
            case HEXAGONO:
                accion = accion + "HexÃ¡gono\n";
                break;
            case NINGUNO:
                accion = accion + "Ninguno\n";
                break;
        }
    }
    /* Cerrar el archivo */
    out << accion;
    out.close();
}

