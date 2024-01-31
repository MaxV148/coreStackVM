//
// Created by Maximilian Vater on 29.01.24.
//

#ifndef STACKVM_VMLIST_HPP
#define STACKVM_VMLIST_HPP
#include <vector>

using std::vector;

class VMList {
public:
    VMList(): elements(){}
    void add(long value){elements.push_back(value);};
    long get(size_t index){return elements.at(index);};
    void set(size_t index, long value) { elements.at(index) = value; }
    size_t size() { return elements.size(); }


private:

    vector<long> elements;


};


#endif //STACKVM_VMLIST_HPP
