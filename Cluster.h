//
// Created by Stephen on 11/10/2015.
//

#ifndef PA4_CLUSTER_H
#define PA4_CLUSTER_H
#include <forward_list>
#include <unordered_map>
#include "Point.h"

namespace Clustering {

    //Forward declarations of Cluster friend functions
    template<typename T, int dim> class Cluster;
    template<typename T, int dim>
    bool operator==(const Cluster<T,dim> &, const Cluster<T,dim> &);
    template<typename T, int dim>
    bool operator!=(const Cluster<T,dim> &, const Cluster<T,dim> &);
    template<typename T, int dim>
    const Cluster<T,dim> operator+(const Cluster<T,dim> &, const Cluster<T,dim> &);
    template<typename T, int dim>
    const Cluster<T,dim> operator-(const Cluster<T,dim> &, const Cluster<T,dim> &);
    template<typename T, int dim>
    const Cluster<T,dim> operator+(const Cluster<T,dim> &, const T &);
    template<typename T, int dim>
    const Cluster<T,dim> operator-(const Cluster<T,dim> &, const T &);
    template<typename T, int dim>
    std::ostream &operator<<(std::ostream &, const Cluster<T,dim> &);
    template<typename T, int dim>
    std::istream &operator>>(std::istream &, Cluster<T,dim> &);
    template<typename T, int dim>
    double interClusterDistance(const Cluster<T,dim> &, const Cluster<T,dim> &);
    template<typename T, int dim>
    double interClusterEdges(const Cluster<T,dim> &, const Cluster<T,dim> &);

    template<typename T, int dim>
    class Cluster {

        //Centroid Class
        class Centroid : public T{
            T __centroid;
            unsigned int __dimension;
        public:
            Centroid() :
                __dimension(dim),
                __centroid(T(false))
            {}

            const T get() const{
                return __centroid;
            }
            void set(const T &point){
                __centroid = point;
            }
        };

        int c_dim;
        Centroid c_cent;
        unsigned int c_size = 0;
        unsigned int c_id;
        bool c_valid = false;

    public:
        static const char CLUSTER_VALUE_DELIM = ':';
        static std::unordered_map<unsigned int,double> distMap;
        std::forward_list<T> c_points;

        //Move Class
        class Move{
        public:
            T m_point;
            Cluster<T,dim> *from;
            Cluster<T,dim> *to;

            Move() {};
            Move(const T &p, Cluster *f, Cluster *t) : m_point(p), from(f), to(t) {};
            void perform(){
                from->remove(m_point);
                to->add(m_point);
            };
        };

        //Constructor, Copy, Assignment
        Cluster();
        Cluster(const Cluster &);
        Cluster &operator=(const Cluster &);
        ~Cluster() { };

        //Setters and Getters
        unsigned int getSize() const { return c_size; };
        void setSize(unsigned int s) { c_size = s; };
        unsigned int getId() const { return c_id; };
        void setId(unsigned int i) { c_id = i; };
        bool getValid() const { return c_valid; };
        void setValid(bool v) { c_valid = v; };
        T getCent() const { return c_cent.get(); };
        void setCent(const T point) { c_cent.set(point); };

        //Selector Operators
        T &operator[](int index) {
            auto it = c_points.begin();
            for (std::size_t i = 0; i < index; i++){
                it++;
            }
            return *it;
        }

        //Comparison Operators
        friend bool operator==<>(const Cluster &, const Cluster &);
        friend bool operator!=<>(const Cluster &, const Cluster &);

        //Arithmetic Operators
        Cluster &operator+=(const Cluster &); // Cluster Union
        Cluster &operator-=(const Cluster &); // Cluster Difference (Asymmetric)
        Cluster &operator+=(const T &); // Add Point
        Cluster &operator-=(const T &); // Remove Point

        friend const Cluster operator+<>(const Cluster &, const Cluster &);
        friend const Cluster operator-<>(const Cluster &, const Cluster &);
        friend const Cluster operator+<>(const Cluster &, const T &);
        friend const Cluster operator-<>(const Cluster &, const T &);

        //IOStream Operators
        friend std::ostream &operator<<<>(std::ostream &, const Cluster &);
        friend std::istream &operator>><>(std::istream &, Cluster &);

        //Functions
        void add(const T &);
        const T &remove(const T &);
        void computeCentroid();
        void pickPoints(int k, Cluster&);

        //Functions for Kmeans Algorithm
        double intraClusterDistance() const;
        friend double interClusterDistance<>(const Cluster &, const Cluster &);
        friend double interClusterEdges<>(const Cluster &, const Cluster &);
        int getClusterEdges();
    };
};

#include "Cluster.cpp"
#endif //PA4_CLUSTER_H
