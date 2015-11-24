//
// Created by Stephen on 11/10/2015.
//

#ifndef PA4_POINT_H
#define PA4_POINT_H
#include <vector>
#include <iostream>
#include "Exceptions.h"

namespace Clustering {

//Forward Declared template friend functions
    template<typename T, int dim> class Point;
    template<typename T, int dim>
    bool operator==(const Point<T, dim> &, const Point<T, dim> &);
    template<typename T, int dim>
    bool operator!=(const Point<T, dim> &, const Point<T, dim> &);
    template<typename T, int dim>
    bool operator<(const Point<T, dim> &, const Point<T, dim> &);
    template<typename T, int dim>
    bool operator<=(const Point<T, dim> &, const Point<T, dim> &);
    template<typename T, int dim>
    bool operator>(const Point<T, dim> &, const Point<T, dim> &);
    template<typename T, int dim>
    bool operator>=(const Point<T, dim> &, const Point<T, dim> &);
    template<typename T, int dim>
    Point<T,dim> &operator+=(Point<T, dim> &, const Point<T, dim> &);
    template<typename T, int dim>
    const Point<T,dim> operator+(const Point<T, dim> &, const Point<T, dim> &);
    template<typename T, int dim>
    Point<T,dim> &operator-=(Point<T, dim> &, const Point<T, dim> &);
    template<typename T, int dim>
    const Point<T,dim> operator-(const Point<T, dim> &, const Point<T, dim> &);
    template<typename T, int dim>
    std::ostream &operator<<(std::ostream &, const Point<T, dim> &);
    template<typename T, int dim>
    std::istream &operator>>(std::istream &, Point<T, dim> &);

    template<typename T, int dim>
    class Point {
        std::vector<T> p_val;
        unsigned int p_dim;
        unsigned int p_id;
    public:
        static const char POINT_VALUE_DELIM = ',';

        //Constructors, Copy, Assignment
        Point();
        Point(bool);
        Point(const Point &);
        Point &operator=(const Point &);
        ~Point() {};

        //Setters and Mutators
        unsigned int getDim(unsigned int) const;
        void setDim(unsigned int, const T &);
        unsigned int getId() const { return p_id; };
        void setId(unsigned int i) { p_id = i; };

        //Selector Operators
        double &operator[](int index) {
            try{
                if(index >= p_dim){
                    OutOfBoundsEx e(index);
                    throw e;
                }
            }catch(OutOfBoundsEx e){
                std::cout << e;
                e.setIndex(p_dim);
            }
            return p_val[index];
        }

        //Comparison Operators
        friend bool operator== <> (const Point &, const Point &);
        friend bool operator!= <> (const Point &, const Point &);
        friend bool operator< <> (const Point &, const Point &);
        friend bool operator<= <> (const Point &, const Point &);
        friend bool operator> <> (const Point &, const Point &);
        friend bool operator>= <> (const Point &, const Point &);

        //Arithmetic Operators
        friend Point &operator+= <> (Point &, const Point &);
        friend const Point operator+ <> (const Point &, const Point &);
        friend Point &operator-= <> (Point &, const Point &);
        friend const Point operator- <> (const Point &, const Point &);
        Point &operator*=(double);
        const Point operator*(double) const;
        Point &operator/=(double);
        const Point operator/(double) const;

        //IOStream Operators
        friend std::ostream &operator<< <> (std::ostream &, const Point &);
        friend std::istream &operator>> <> (std::istream &, Point &);

        //Functions
        double distanceTo(const Point &) const;

    };

};
#include "Point.cpp"
#endif //PA4_POINT_H
