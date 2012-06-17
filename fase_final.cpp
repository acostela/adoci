/* 
 * File:   fase_final.cpp
 * Author: Ángel Costela Sanmiguel y David Medina Godoy
 * 
 */

#include "fase_final.h"

void final_t::salida(string numJ) {
    string cad = "accionJ" + numJ + ".sbt";
    string accion;
    ofstream out(cad.c_str());
    /* Linea 1: Número de radiadores a apagar */
    accion = accion + itoStr(radiadores_off) + "\n";

    /* Linea 2: Número de radiadores a encender */
    accion = accion + itoStr(radiadores_on) + "\n";

    /* Linea 3: Soltar garrote */
    switch (soltar_garrote) {
        case true:
            accion = accion + "True\n";
            break;
        case false:
            accion = accion + "False\n";
            break;
    }

    /* Linea 4: Número de municiones a expulsar */
    accion = accion + itoStr(expulsar) + "\n";

    /* Para cada munición a expulsar */
    for (int i = 0; i < expulsar; ++i) {
        /* Localización de la munición */
        switch (expulsada[i].localizacion) {
            case 0:
                accion = accion + "BI\n";
                break;
            case 1:
                accion = accion + "TI\n";
                break;
            case 2:
                accion = accion + "PI\n";
                break;
            case 3:
                accion = accion + "PD\n";
                break;
            case 4:
                accion = accion + "TD\n";
                break;
            case 5:
                accion = accion + "BD\n";
                break;
            case 6:
                accion = accion + "TC\n";
                break;
            case 7:
                accion = accion + "CAB\n";
                break;
        }

        /* Slot de la munición dentro de la localización */
        accion = accion + itoStr(expulsada[i].slot) + "\n";
    }
    /* Cerrar el archivo */
    out << accion;
    out.close();
}

void final_t::logicaFinal(){
    radiadores_off=0;
    radiadores_on=0;
    soltar_garrote=0;
    expulsar=0;
    expulsada=0;
}

