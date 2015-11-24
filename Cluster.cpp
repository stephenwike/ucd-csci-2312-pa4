//
// Created by Stephen on 11/10/2015.
//

#include "Cluster.h"
#include <sstream>
#include <algorithm>

namespace Clustering {

    template<typename T,int dim>
    std::unordered_map<unsigned int,double> Cluster<T, dim>::distMap;

    template<typename T, int dim>
    Cluster<T, dim>::Cluster() : c_dim(dim) {
        IdGen<T> assign;
        c_id = assign.id_id;
    }

    template<typename T, int dim>
    Cluster<T, dim>::Cluster(const Cluster &cluster) {

        c_dim = cluster.c_dim;
        c_size = cluster.c_size;
        c_points = cluster.c_points;
    }

    template<typename T, int dim>
    Cluster<T,dim> &Cluster<T,dim>::operator=(const Cluster &cluster) {
        if (this == &cluster) {
            return *this;
        }

        c_dim = cluster.c_dim;
        c_size = cluster.c_size;
        c_points = cluster.c_points;
        return *this;
    }

    template<typename T, int dim>
    bool operator==(const Cluster<T, dim> &lhs, const Cluster<T, dim> &rhs) {
        return (lhs.getId() == rhs.getId());
    }

    template<typename T, int dim>
    bool operator!=(const Cluster<T, dim> &lhs, const Cluster<T, dim> &rhs) {
        return (lhs.getId() != rhs.getId());
    }

    template<typename T, int dim>
    Cluster<T, dim> &Cluster<T, dim>::operator+=(const Cluster &cluster) {
        c_valid = false;
        for(auto it = cluster.c_points.begin(); it != cluster.c_points.end(); it++){
            add(*it);
        }
        return *this;
    }

    template<typename T, int dim>
    Cluster<T, dim> &Cluster<T, dim>::operator-=(const Cluster &cluster) {
        c_valid = false;
        for(auto it = cluster.c_points.begin(); it != cluster.c_points.end(); it++){
            remove(*it);
        }
        return *this;
    }

    template<typename T, int dim>
    Cluster<T, dim> &Cluster<T, dim>::operator+=(const T &point) {
        c_valid = false;
        add(point);
        return *this;
    }

    template<typename T, int dim>
    Cluster<T, dim> &Cluster<T, dim>::operator-=(const T &point) {
        c_valid = false;
        remove(point);
        return *this;
    }

    template<typename T, int dim>
    const Cluster<T, dim> operator+(const Cluster<T, dim> &lhs, const Cluster<T, dim> &rhs) {
        lhs.c_valid = false;
        for(auto it = rhs.c_points.begin(); it != rhs.c_points.end(); it++){
            lhs.add(*it);
        }
        return lhs;
    }

    template<typename T, int dim>
    const Cluster<T, dim> operator-(const Cluster<T, dim> &lhs, const Cluster<T, dim> &rhs) {
        lhs.c_valid = false;
        for(auto it = rhs.c_points.begin(); it != rhs.c_points.end(); it++){
            lhs.remove(*it);
        }
        return lhs;
    }

    template<typename T, int dim>
    const Cluster<T, dim> operator+(const Cluster<T, dim> &lhs, const T &rhs) {
        lhs.c_valid = false;
        lhs.add(rhs);
        return lhs;
    }

    template<typename T, int dim>
    const Cluster<T, dim> operator-(const Cluster<T, dim> &lhs, const T &rhs) {
        lhs.c_valid = false;
        lhs.remove(rhs);
        return lhs;
    }

    template<typename T, int dim>
    std::ostream &operator<<(std::ostream &os, const Cluster<T, dim> &cluster) {
        if (cluster.c_size == 0) {
            std::cout << "Cluster is empty." << std::endl;
            return os;
        }
        for (auto it = cluster.c_points.begin(); it != cluster.c_points.end(); it++) {
            os << *it << " " << Cluster<T,dim>::CLUSTER_VALUE_DELIM << " " << cluster.c_id << "\r\n";
        }
        return os;
    }

    template<typename T, int dim>
    std::istream &operator>>(std::istream &is, Cluster<T, dim> &cluster) {
        try {
            std::string line;
            if (is.good()) {
                while (!(is.eof())) {
                    getline(is, line);
                    int mycount = 0;
                    if (!line.empty()) {
                        mycount = std::count(line.begin(), line.end(), ',');
                        mycount++;
                    }
                    if (mycount != cluster.c_dim) {
                        DimensionalityMismatchEx e(mycount, cluster.c_dim);
                        throw e;
                    }
                    T *newPoint = new T();
                    std::stringstream lineStream(line);
                    lineStream >> *newPoint;
                    cluster.add(*newPoint);
                }
            } else {
                std::cerr << "The cluster file is not open!" << std::endl;
            }
            return is;
        } catch (DimensionalityMismatchEx e) {
            std::cout << e;
        }
    }

    template<typename T, int dim>
    void Cluster<T, dim>::add(const T &val) {
        try {
            if (c_points.empty()) {
                c_points.push_front(val); //If it's the first Point added.
            } else {
                auto prev = c_points.before_begin();
                for (auto it = c_points.begin(); it != c_points.end(); it++) {
                    if (*it == val) {
                        DuplicatePointEx e;
                        throw e;
                    }
                    if (val <= *it) {
                        c_points.insert_after(prev, val); //Places in Lexographic order
                        break;
                    } else {
                        auto next = it;
                        if (++next == c_points.end()) {
                            c_points.insert_after(it, val);  //Enter at end if it's the largest Point
                            break;
                        }
                        prev++;
                    }
                }
            }
            c_valid = false;
            c_size++;
        } catch (DuplicatePointEx e) {
            std::cout << e;
        }
    }

    template<typename T, int dim>
    const T &Cluster<T, dim>::remove(const T &val) {
        try {
            if (c_points.empty()) {
                RemoveFromEmptyEx e;
                throw e;
            }
            c_points.remove(val);
            c_size--;
            return val;
        } catch (RemoveFromEmptyEx e) {
            std::cout << e;
        }
    }

    template<typename T, int dim>
    void Cluster<T, dim>::computeCentroid() {
        T addend(false);
        for (auto it = c_points.begin(); it != c_points.end(); it++) {
            addend += *it / c_size;
        }
        setCent(addend);
        c_valid = true;
    }

    template<typename T, int dim>
    void Cluster<T, dim>::pickPoints(int k, Cluster &cluster) {
        int incr = c_size / k;
        int index = (0.5 * incr);
        for (std::size_t i = 0; i < k; i++) {
            cluster.add((*this)[index]);
            index += incr;
        }
    }

    template<typename T, int dim>
    double Cluster<T, dim>::intraClusterDistance() const {
        double dist = 0;
        unsigned int cantor = 0;
        Cluster<T,dim> clust;
        for (auto it = c_points.begin(); it != c_points.end(); it++) {
            for (auto jt = it; jt != c_points.end(); jt++) {
                if (it != jt) {
                    if(it->getId() < jt->getId()) {
                        cantor = (it->getId() + jt->getId()) * (it->getId() + jt->getId() + 1) / 2 + jt->getId();
                    }else{
                        cantor = (it->getId() + jt->getId()) * (it->getId() + jt->getId() + 1) / 2 + it->getId();
                    }
                    dist += clust.distMap[cantor];
                }
            }
        }
        return dist;
    }

    template<typename T, int dim>
    double interClusterDistance(const Cluster<T, dim> &c1, const Cluster<T, dim> &c2) {
        if (c1.c_size == 0 || c2.c_size == 0) {
            return 0;
        }
        double dist = 0;
        unsigned int cantor = 0;
        Cluster<T,dim> clust;
        for (auto it = c1.c_points.begin(); it != c1.c_points.end(); it++) {
            for (auto jt = c2.c_points.begin(); jt != c2.c_points.end(); jt++) {
                if(it->getId() < jt->getId()) {
                    cantor = (it->getId() + jt->getId()) * (it->getId() + jt->getId() + 1) / 2 + jt->getId();
                }else{
                    cantor = (it->getId() + jt->getId()) * (it->getId() + jt->getId() + 1) / 2 + it->getId();
                }
                dist += clust.distMap[cantor];
            }
        }
        return dist;
    }

    template<typename T, int dim>
    double interClusterEdges(const Cluster<T, dim> &c1, const Cluster<T, dim> &c2) {
        return (c1.c_size * c2.c_size);
    }

    template<typename T, int dim>
    int Cluster<T, dim>::getClusterEdges() {
        return (c_size * (c_size - 1) / 2);
    }
};