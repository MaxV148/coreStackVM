

#ifndef STACKVM_STACKFRAME_HPP
#define STACKVM_STACKFRAME_HPP

#include <map>

using std::map;

class Stackframe {
    const map<int,long> variables{};
public:
    explicit Stackframe();
    long getVariable(int varNumber);
    void setVariable(int varNumber, long value);

};


#endif //STACKVM_STACKFRAME_HPP
