//
// Created by Stephen on 11/10/2015.
//

#ifndef PA4_EXCEPTIONS_H
#define PA4_EXCEPTIONS_H

#include <string>
#include <iostream>

namespace Clustering {

    class OutOfBoundsEx {
        int index;
        std::string name;
    public:
        OutOfBoundsEx(int);
        int getIndex() const { return index; };
        void setIndex(int i) { index = i; };
        std::string getName() const { return name; };
        void setName(std::string s) { name = s; };
        friend std::ostream &operator<<(std::ostream &,const OutOfBoundsEx &);
    };

    class DimensionalityMismatchEx {
        int lhs, rhs;
        std::string name;
    public:
        DimensionalityMismatchEx(int l, int r);
        int getLhs() const { return lhs; };
        void setLhs(int i) { lhs = i; };
        int getRhs() const { return rhs; };
        void setRhs(int i) { rhs = i; };
        std::string getName() const { return name; };
        void setName(std::string s) { name = s; };
        friend std::ostream &operator<<(std::ostream &,const DimensionalityMismatchEx &);
    };

    class DivideByZeroEx {
        std::string name;
    public:
        DivideByZeroEx();
        std::string getName() const { return name; };
        void setName(std::string s) { name = s; };
        friend std::ostream &operator<<(std::ostream &,const DivideByZeroEx &);
    };

    class RemoveFromEmptyEx {
        std::string name;
    public:
        RemoveFromEmptyEx();
        std::string getName() const { return name; };
        void setName(std::string s) { name = s; };
        friend std::ostream &operator<<(std::ostream &,const RemoveFromEmptyEx &);
    };

    class DuplicatePointEx {
        std::string name;
    public:
        DuplicatePointEx();
        std::string getName() const { return name; };
        void setName(std::string s) { name = s; };
        friend std::ostream &operator<<(std::ostream &,const DuplicatePointEx &);
    };

};

#endif //PA4_EXCEPTIONS_H
