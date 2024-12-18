#include <iostream>
#include "Persona.h"

Persona::Persona(std::string s){
        this-> s = s;
    }
std::string Persona::restituisciNome(){
        return s;
    }