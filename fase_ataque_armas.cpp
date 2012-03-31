/* 
 * File:   fase_ataque_armas.cpp
 * Author: asce
 * 
 * Created on 28 de marzo de 2012, 0:35
 */

#include "fase_ataque_armas.h"


ataque_armas_t::ataque_armas_t() {
    coger_garrote = false;
    objetivo.fila = 0;
    objetivo.columna = 0;
    num_armas = 0;
    for (int i = 0; i < 20; i++) {
        armas_mech[i].localizacion = 0;
        armas_mech[i].slot = 0;
        armas_mech[i].doble_cadencia = false;
        armas_mech[i].loc_municion = -1;
        armas_mech[i].slot_municion = -1;
        armas_mech[i].objetivo.columna = 0;
        armas_mech[i].objetivo.fila = 0;
        armas_mech[i].tipo_objetivo = 0;
    }
}

void ataque_armas_t::salida(string numJ) {
    /* Crear el archivo de salida */
    string cad = "accionJ" + numJ + ".sbt";
    string accion;
    ofstream out;
    out.open(cad.c_str());
    /* Linea 1: Coger garrote */
    switch (coger_garrote) {
        case true:
            accion = accion + "True\n";
            break;
        case false:
            accion = accion + "False\n";
            break;
    }

    /* Si se coge un garrote, terminar aquÃ­ */
    if (coger_garrote == true) {
        out << accion;
        out.close();
        return;
    }

    /* Linea 2: HexÃ¡gono objetivo primario */
    accion = accion + objetivo.stringPos() + "\n";

    /* Linea 3: NÃºmero de armas que se van a disparar */
    accion = accion + itoStr(num_armas) + "\n";

    /* Para cada arma a disparar */
    for (int i = 0; i < num_armas; ++i) {
        /* LocalizaciÃ³n del arma */
        switch (armas_mech[i].localizacion) {
            case 0:
                accion = accion + "BI\n";
                break;
            case 1:
            case 8:
                accion = accion + "TI\n";
                break;
            case 2:
                accion = accion + "PI\n";
                break;
            case 3:
                accion = accion + "PD\n";
                break;
            case 4:
            case 9:
                accion = accion + "TD\n";
                break;
            case 5:
                accion = accion + "BD\n";
                break;
            case 6:
            case 10:
                accion = accion + "TC\n";
                break;
            case 7:
                accion = accion + "CAB\n";
                break;
        }

        /* Slot del arma dentro de la localizaciÃ³n */
        accion = accion + itoStr(armas_mech[i].slot) + "\n";

        /* Doble cadencia */
        switch (armas_mech[i].doble_cadencia) {
            case true:
                accion = accion + "True\n";
                break;
            case false:
                accion = accion + "False\n";
                break;
        }

        /* LocalizaciÃ³n de la municiÃ³n */
        switch (armas_mech[i].loc_municion) {
            case 0:
                accion = accion + "BI\n";
                break;
            case 1:
            case 8:
                accion = accion + "TI\n";
                break;
            case 2:
                accion = accion + "PI\n";
                break;
            case 3:
                accion = accion + "PD\n";
                break;
            case 4:
            case 9:
                accion = accion + "TD\n";
                break;
            case 5:
                accion = accion + "BD\n";
                break;
            case 6:
            case 10:
                accion = accion + "TC\n";
                break;
            case 7:
                accion = accion + "CAB\n";
                break;
            default:
                accion = accion + "-1\n";
        }

        /* Slot de la municiÃ³n dentro de la localizaciÃ³n */
        accion = accion + itoStr(armas_mech[i].slot_municion) + "\n";

        /* HexÃ¡gono objetivo del arma */
        accion = accion + armas_mech[i].objetivo.stringPos() + "\n";

        /* Tipo de objetivo */
        switch (armas_mech[i].tipo_objetivo) {
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

