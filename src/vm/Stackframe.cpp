//
// Created by Maximilian Vater on 18.01.24.
//

#include "Stackframe.hpp"

Stackframe::Stackframe() = default;

long Stackframe::getVariable(int varNumber) {
    return variables.at(varNumber);
}