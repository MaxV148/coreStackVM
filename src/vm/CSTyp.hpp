//
// Created by Maximilian Vater on 30.01.24.
//

#ifndef STACKVM_CSTYP_HPP
#define STACKVM_CSTYP_HPP


#include <string>
#include <utility>
#include <vector>
#include "memory"
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

using std::string;
using std::vector;

namespace Typing {


    enum CSTypes{
        Double,
        Int,
        String
    };

    class CSObject {
    public:
        virtual ~CSObject() = default;
        virtual CSTypes getType() = 0;

    };

    class CSDouble : public CSObject {
        double value;
    public:
        explicit CSDouble(double value) : value(value) {}

        CSTypes getType() override{
            return CSTypes::Double;
        }

        friend CSDouble operator+(const CSDouble &lhs, const CSDouble &rhs) {
            return CSDouble(lhs.value + rhs.value);
        }

        friend CSDouble operator-(const CSDouble &lhs, const CSDouble &rhs) {
            return CSDouble(lhs.value - rhs.value);
        }

        friend CSDouble operator*(const CSDouble &lhs, const CSDouble &rhs) {
            return CSDouble(lhs.value * rhs.value);
        }

        friend CSDouble operator/(const CSDouble &lhs, const CSDouble &rhs) {
            return CSDouble(lhs.value / rhs.value);
        }

        friend bool operator<(const CSDouble &lhs, const CSDouble &rhs) {
            return lhs.value < rhs.value;
        }

        friend bool operator<=(const CSDouble &lhs, const CSDouble &rhs) {
            return lhs.value <= rhs.value;
        }

        friend bool operator>(const CSDouble &lhs, const CSDouble &rhs) {
            return lhs.value > rhs.value;
        }

        friend bool operator>=(const CSDouble &lhs, const CSDouble &rhs) {
            return lhs.value >= rhs.value;
        }

        friend bool operator==(const CSDouble &lhs, const CSDouble &rhs) {
            return lhs.value == rhs.value;
        }
        friend std::ostream& operator<<(std::ostream& os ,const CSDouble &obj){
            std::cout << obj.value << std::endl;
            return os;

        }


    };

    class CSString : public CSObject {
        string const value;
    public:
        explicit CSString(string str) : value(std::move(str)) {}

        CSTypes getType() override{
            return CSTypes::String;
        }

        friend bool operator==(const CSString &lhs, const CSString &rhs) {
            return lhs.value == rhs.value;
        }
        friend CSString operator+(const CSString &lhs, const CSString &rhs){
            return CSString(lhs.value+rhs.value);
        }


    };

    class CSStruct {
        const vector<CSObject> structMember;
    public:
        explicit CSStruct(vector<CSObject> member) : structMember(std::move(member)) {}
    };

}


#endif //STACKVM_CSTYP_HPP
