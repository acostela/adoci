/* 
 * File:   fase_final.cpp
 * Author: asce
 * 
 * Created on 28 de marzo de 2012, 0:36
 */

#include "fase_final.h"

void final_t::salida(string numJ) {
    string cad = "accionJ" + numJ + ".sbt";
    string accion;
    ofstream out(cad.c_str());
    out.open(cad.c_str());
    /* Linea 1: NÃºmero de radiadores a apagar */
    accion = accion + itoStr(radiadores_off) + "\n";

    /* Linea 2: NÃºmero de radiadores a encender */
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

    /* Linea 4: NÃºmero de municiones a expulsar */
    accion = accion + itoStr(expulsar) + "\n";

    /* Para cada municiÃ³n a expulsar */
    for (int i = 0; i < expulsar; ++i) {
        /* LocalizaciÃ³n de la municiÃ³n */
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

        /* Slot de la municiÃ³n dentro de la localizaciÃ³n */
        accion = accion + itoStr(expulsada[i].slot) + "\n";
    }
    /* Cerrar el archivo */
    out << accion;
    out.close();
}


