//
// Created by Maximilian Vater on 30.01.24.
//

#ifndef STACKVM_CSTYP_HPP
#define STACKVM_CSTYP_HPP

#include "CSObject.hpp"
#include <string>
#include <utility>
#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;

using std::string;

typedef cpp_int CSBigInt;

template<typename T>
class CSTyp : public CSObject {
    virtual T const getValue() = 0;
};



class CSInteger : public CSTyp<CSBigInt> {
    CSBigInt value;
public:
    explicit CSInteger(CSBigInt value) : value(std::move(value)) {}

    CSBigInt const getValue() override {
        return value;
    }
};

class CSDouble : public CSTyp<double> {
    double value;
public:
    explicit CSDouble(double value) : value(value) {}

    double const getValue() override {
        return value;
    }
};

class CSString : public CSTyp<string> {
    string const value;
public:
    explicit CSString(string  str) : value(std::move(str)) {}

    string const getValue() override {
        return value;
    }
};


#endif //STACKVM_CSTYP_HPP
