//
// Created by Stephen on 11/11/2015.
//

#ifndef PA4_KMEANS_H
#define PA4_KMEANS_H
#include "Point.h"
#include "Cluster.h"

namespace Clustering {

    template<typename T, int k, int dim> class KMeans;//k is the amount of clusters
    template<typename T, int k, int dim> std::ostream &operator<<(std::ostream &, const KMeans<T,k,dim> &);
    template<typename T, int k, int dim> std::istream &operator>>(std::istream &, KMeans<T,k,dim> &);

    template<typename T, int k, int dim>
    class KMeans {

        std::vector<T> k_clusters;
        T point_space;

    public:
        static const double SCORE_DIFF_THRESHOLD;

        //Constructor
        KMeans<T,k,dim>();

        //IOStream Operators
        friend std::ostream &operator<< <> (std::ostream &, const KMeans &);
        friend std::istream &operator>> <> (std::istream &, KMeans &);

        //Functions
        double computeClusteringScore();
    };
};

#include "KMeans.cpp"
#endif //PA4_KMEANS_H
