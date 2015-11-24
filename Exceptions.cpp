//
// Created by Stephen on 11/10/2015.
//

#include "Exceptions.h"

namespace Clustering {

    OutOfBoundsEx::OutOfBoundsEx(int i) : index(i), name("OutOfBounds")
    {
    }

    std::ostream &operator<<(std::ostream &os, const OutOfBoundsEx &ex) {
        os << ex.getName() << ": " << ex.getIndex() << " is not in range." << std::endl;
        return os;
    }

    DivideByZeroEx::DivideByZeroEx() : name("DivideByZero")
    {
    }

    std::ostream &operator<<(std::ostream &os, const DivideByZeroEx &ex) {
        os << ex.getName() << ": can't divide by zero." << std::endl;
        return os;
    }

    DimensionalityMismatchEx::DimensionalityMismatchEx(int l,int r) : lhs(l), rhs(r), name("DimensionalityMismatch")
    {
    }

    std::ostream &operator<<(std::ostream &os, const DimensionalityMismatchEx &ex) {
        os << ex.getName() << ": " << ex.getLhs() << " and " << ex.getRhs() << " have different dimensionality" << std::endl;
        return os;
    }

    RemoveFromEmptyEx::RemoveFromEmptyEx() : name("RemoveFromEmpty")
    {
    }

    std::ostream &operator<<(std::ostream &os, const RemoveFromEmptyEx &ex) {
        os << ex.getName() << ": This container is already empty." << std::endl;
        return os;
    }

    DuplicatePointEx::DuplicatePointEx() : name("DuplicatePoint")
    {
    }

    std::ostream &operator<<(std::ostream &os, const DuplicatePointEx &ex) {
        os << ex.getName() << ": Point already exist in this set." << std::endl;
        return os;
    }
};