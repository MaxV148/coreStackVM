//
// Created by Maximilian Vater on 29.01.24.
//



#ifndef STACKVM_CSOBJECT_HPP
#define STACKVM_CSOBJECT_HPP
#include <memory>

class CSObject {
public:
    virtual ~CSObject() = default;
    virtual std::unique_ptr<CSObject> add(const CSObject& rhs) const = 0;

};
#endif //STACKVM_CSOBJECT_HPP


