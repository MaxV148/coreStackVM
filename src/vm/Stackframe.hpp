

#ifndef STACKVM_STACKFRAME_HPP
#define STACKVM_STACKFRAME_HPP

#include <map>

#include "CSObject.hpp"

using std::map;

class Stackframe {
    map<int,CSObject>  variables{};
    int returnAddress{};
public:
    explicit Stackframe(int returnAddress);
    CSObject getVariable(int varNumber);
    void setVariable(int varNumber, CSObject value);
    int getReturnAddress()const;
};

#endif //STACKVM_STACKFRAME_HPP
