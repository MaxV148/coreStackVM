//
// Created by Maximilian Vater on 18.01.24.
//

#include "Stackframe.hpp"


Stackframe::Stackframe(int returnAddress): returnAddress(returnAddress){};

long Stackframe::getVariable(int varNumber) {
    return variables.at(varNumber);
}

void Stackframe::setVariable(int varNumber,long value) {
    variables[varNumber] = value;
}

int Stackframe::getReturnAddress()const {
    return returnAddress;
}