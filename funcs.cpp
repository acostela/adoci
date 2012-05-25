/* 
 * File:   funcs.cpp
 * Author: asce
 * 
 * Created on 12 de octubre de 2011, 18:53
 */

#include "funcs.h"


string itoStr(int num){
    stringstream ss;
    ss << num;
    return ss.str();
}

/*int strtoInt(string cadena){
    stringstream salida;
    
    salida << cadena;
    salida.
    return salida.int();
}*/
