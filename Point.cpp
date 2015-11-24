//
// Created by Stephen on 11/10/2015.
//

#include "Point.h"
#include "IdGen.h"
#include "Exceptions.h"
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>

namespace Clustering{

    template<typename T, int dim>
    Point<T,dim>::Point() : p_dim(dim)
    {
        IdGen<T> assign;
        p_id = assign.id_id;
        p_val = std::vector<T>(dim,0);
    }

    template<typename T, int dim>
    Point<T,dim>::Point(bool b) : p_dim(dim)
    {
        p_id = 0;
        p_val = std::vector<T>(dim,0);
    }

    template<typename T, int dim>
    Point<T,dim>::Point(const Point &point)
    {
        p_val = point.p_val;
        p_dim = point.p_dim;
        p_id = point.p_id;
    }

    template<typename T, int dim>
    Point<T,dim> &Point<T,dim>::operator=(const Point &point) {
        if(this == &point){
            return *this;
        }

        p_val = point.p_val;
        p_dim = point.p_dim;
        p_id = point.p_id;
        return *this;
    }

    template<typename T, int dim>
    unsigned int Point<T,dim>::getDim(unsigned int index) const {
        try{
            if(index >= p_dim){
                OutOfBoundsEx e(index);
                throw e;
            }
            return p_val[index];
        }catch(OutOfBoundsEx e){
            std::cout << e;
        }
    }

    template<typename T, int dim>
    void Point<T,dim>::setDim(unsigned int index, const T &val) {
        try{
            if(index >= p_dim){
                OutOfBoundsEx e(index);
                throw e;
            }
            p_val[index] = val;
        }catch(OutOfBoundsEx e){
            std::cout << e;
        }
    }

    template<typename T, int dim>
    bool operator==(const Point<T,dim> &lhs, const Point<T,dim> &rhs) {
        if(lhs.p_id == rhs.p_id){
            return true;
        }else {
            return false;
        }
    }

    template<typename T, int dim>
    bool operator!=(const Point<T,dim> &lhs, const Point<T,dim> &rhs) {
        return !(lhs == rhs);
    }

    template<typename T, int dim>
    bool operator<(const Point<T,dim> &lhs, const Point<T,dim> &rhs) {
        for(std::size_t i = 0; i < lhs.p_dim; i++){
            if(lhs.p_val[i] < rhs.p_val[i]){
                return true;
            }else if(lhs.p_val[i] > rhs.p_val[i]){
                return false;
            }
        }
        return false;
    }

    template<typename T, int dim>
    bool operator<=(const Point<T,dim> &lhs, const Point<T,dim> &rhs) {
        return !(lhs > rhs);
    }

    template<typename T, int dim>
    bool operator>(const Point<T,dim> &lhs, const Point<T,dim> &rhs) {
        for(std::size_t i = 0; i < lhs.p_dim; i++){
            if(lhs.p_val[i] > rhs.p_val[i]){
                return true;
            }else if(lhs.p_val[i] < rhs.p_val[i]){
                return false;
            }
        }
        return false;
    }

    template<typename T, int dim>
    bool operator>=(const Point<T,dim> &lhs, const Point<T,dim> &rhs) {
        return !(lhs < rhs);
    }

    template<typename T, int dim>
    Point<T,dim> &operator+=(Point<T,dim> &lhs, const Point<T,dim> &rhs) {
        for(std::size_t i = 0; i < lhs.p_dim; i++){
            lhs.p_val[i] = lhs.p_val[i] + rhs.p_val[i];
        }
        return lhs;
    }

    template<typename T, int dim>
    const Point<T,dim> operator+(const Point<T,dim> &lhs, const Point<T,dim> &rhs) {
        Point<T,dim> result(lhs);
        result += rhs;
        return result;
    }

    template<typename T, int dim>
    Point<T,dim> &operator-=(Point<T,dim> &lhs, const Point<T,dim> &rhs) {
        for(std::size_t i = 0; i < lhs.p_dim; i++){
            lhs.p_val[i] = lhs.p_val[i] - rhs.__val[i];
        }
        return lhs;
    }

    template<typename T, int dim>
    const Point<T,dim> operator-(const Point<T,dim> &lhs, const Point<T,dim> &rhs) {
        Point<T,dim> result(lhs);
        result -= rhs;
        return result;
    }

    template<typename T, int dim>
    Point<T,dim> &Point<T,dim>::operator*=(double val) {
        for(std::size_t i = 0; i < p_dim; i++){
            p_val[i] = p_val[i] * val;
        }
        return *this;
    }

    template<typename T, int dim>
    const Point<T,dim> Point<T,dim>::operator*(double val) const {
        Point result(*this);
        result *= val;
        return result;
    }

    template<typename T, int dim>
    Point<T,dim> &Point<T,dim>::operator/=(double val) {
        try {
            if(val == 0) {
                DivideByZeroEx e;
                throw e;
            }
            for (std::size_t i = 0; i < p_dim; i++) {
                p_val[i] /= val;
            }
            return *this;
        }catch(DivideByZeroEx e){
            std::cout << e;
        }
    }

    template<typename T, int dim>
    const Point<T,dim> Point<T,dim>::operator/(double val) const {
        Point result(*this);
        result /= val;
        return result;
    }

    template<typename T, int dim>
    std::ostream &operator<<(std::ostream &os, const Point<T,dim> &point){
        for(std::size_t i = 0; i < point.p_dim; i++){
            os << point.p_val[i];
            if(i != point.p_dim - 1){
                os << Point<T,dim>::POINT_VALUE_DELIM;
            }
        }
        return os;
    }

    template<typename T, int dim>
    std::istream &operator>>(std::istream &is, Point<T,dim> &point) {
        try {
            Point<T, dim> *newPoint = new Point<T, dim>(false);
            char line[25];
            if (is.good()) {
                for (std::size_t i = 0; i < point.p_dim; i++) {
                    is.getline(line, 25, Point<T, dim>::POINT_VALUE_DELIM);

                    std::stringstream lineStream(line);
                    lineStream >> newPoint->p_val[i];
                }
            } else {
                std::cerr << "The file is not open!" << std::endl;
            }
            point.p_val = newPoint->p_val;
            return is;
        }catch(DimensionalityMismatchEx e){
            std::cout << e;
        }
    }

    template<typename T, int dim>
    double Point<T,dim>::distanceTo(const Point &point) const {
        double sums = 0;
        for(std::size_t i = 0; i < p_dim; i++){
            sums += pow((point.p_val[i] - p_val[i]),2);
        }
        double dist = sqrt(sums);
        return dist;
    }
};
