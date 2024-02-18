//
// Created by Maximilian Vater on 30.01.24.
//

#ifndef STACKVM_CSTYP_HPP
#define STACKVM_CSTYP_HPP

#include "CSObject.hpp"
#include <string>
#include <utility>
#include <vector>
#include "memory"
#include <boost/multiprecision/cpp_int.hpp>

using boost::multiprecision::cpp_int;

using std::string;
using std::vector;

namespace CSTypes {


    class CSInteger : public CSObject {
        cpp_int value;
    public:
        explicit CSInteger(cpp_int value) : value(std::move(value)) {}


        [[nodiscard]] std::string toString() const {
            return value.str();
        }


        friend CSInteger operator+(const CSInteger &lhs, const CSInteger &rhs) {
            return CSInteger(lhs.value + rhs.value);
        }

        friend CSInteger operator-(const CSInteger &lhs, const CSInteger &rhs) {
            return CSInteger(lhs.value - rhs.value);
        }

        friend CSInteger operator*(const CSInteger &lhs, const CSInteger &rhs) {
            return CSInteger(lhs.value * rhs.value);
        }

        friend CSInteger operator/(const CSInteger &lhs, const CSInteger &rhs) {
            return CSInteger(lhs.value / rhs.value);
        }

        friend CSInteger operator%(const CSInteger &lhs, const CSInteger &rhs) {
            return CSInteger(lhs.value % rhs.value);
        }
        friend bool operator<(const CSInteger &lhs, const CSInteger &rhs) {
            return lhs.value < rhs.value;
        }

        friend bool operator<=(const CSInteger &lhs, const CSInteger &rhs) {
            return lhs.value <= rhs.value;
        }

        friend bool operator>(const CSInteger &lhs, const CSInteger &rhs) {
            return lhs.value > rhs.value;
        }
        friend bool operator>=(const CSInteger &lhs, const CSInteger &rhs) {
            return lhs.value >= rhs.value;
        }

        friend bool operator==(const CSInteger &lhs, const CSInteger &rhs) {
            return lhs.value == rhs.value;
        }
    };

    class CSDouble : public CSObject {
        double value;
    public:
        explicit CSDouble(double value) : value(value) {}



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


    };

    class CSString : public CSObject {
        string const value;
    public:
        explicit CSString(string str) : value(std::move(str)) {}


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
