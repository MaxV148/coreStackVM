

#ifndef STACKVM_STACKFRAME_HPP
#define STACKVM_STACKFRAME_HPP

#include <map>

using std::map;

class Stackframe {
    map<int,long>  variables{};
    int returnAddress{};
public:
    explicit Stackframe(int returnAddress);
    long getVariable(int varNumber);
    void setVariable(int varNumber, long value);
    int getReturnAddress()const;
};

#endif //STACKVM_STACKFRAME_HPP
