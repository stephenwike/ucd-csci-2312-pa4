//
// Created by Stephen on 11/11/2015.
//

#include "KMeans.h"

namespace Clustering {

    template<typename T, int k, int dim>
    const double KMeans<T,k,dim>::SCORE_DIFF_THRESHOLD = 0.001;

    template<typename T, int k, int dim>
    KMeans<T,k,dim>::KMeans()
    {
        k_clusters = std::vector<T>(k);
    }

    template<typename T, int k, int dim>
    double KMeans<T,k,dim>::computeClusteringScore() {
        double score, scoreDiff = SCORE_DIFF_THRESHOLD + 1;
        T clust;

        point_space.pickPoints(k, clust);

        //Set pickPoints as Centroids to k_clusters
        for(std::size_t i = 0; i < k; i++){
            k_clusters[i].setCent(clust[i]);
        }

        unsigned int cantor = 0;

        //Initialize Unordered Map
        for(auto it = point_space.c_points.begin(); it != point_space.c_points.end(); it++){
            for(auto next = it; next != point_space.c_points.end(); next){
                next++;
                if(next != point_space.c_points.end()){
                    if(it->getId() < next->getId()) {
                        cantor = (it->getId() + next->getId()) * (it->getId() + next->getId() + 1) / 2 + next->getId();
                    }else{
                        cantor = (it->getId() + next->getId()) * (it->getId() + next->getId() + 1) / 2 + it->getId();
                    }
                    point_space.distMap[cantor] = it->distanceTo(*next);
                }
            }
        }

        double BetaCV = 0.0, prevBetaCV = 0.0, DbetaCV = 0.0, din = 0.0, dout = 0.0, pin = 0.0, pout = 0.0;
        int count = 0;
        while(scoreDiff > SCORE_DIFF_THRESHOLD) {

            typename T::Move move;
            double minDist = 1.0/0.0;
            for(std::size_t from = 0; from < k; from++){
                for(std::size_t mp = 0; mp < k_clusters[from].getSize(); mp++){
                    double nativeDist = k_clusters[from].getCent().distanceTo(k_clusters[from][mp]);
                    bool tomove = false;
                    for(std::size_t to = 0; to < k; to++) {
                        if (to != from) {
                            double dist = k_clusters[to].getCent().distanceTo(k_clusters[from][mp]);
                            if(dist < nativeDist){
                                nativeDist = dist;
                                move.m_point = k_clusters[from][mp];
                                move.from = &k_clusters[from];
                                move.to = &k_clusters[to];
                                tomove = true;
                            }
                        }
                    }
                    if(tomove) {
                        move.perform();
                        mp--;
                    }
                }
            }

            for(std::size_t clusts = 0; clusts < k; clusts++){
                if(k_clusters[clusts].getValid() == 0){
                    k_clusters[clusts].computeCentroid();
                }
            }

            for(std::size_t i = 0; i < k; i++){
                din = din + k_clusters[i].intraClusterDistance();
            }

            for(std::size_t i = 0; i < k;){
                for(std::size_t j = i++; j < k; j++){
                    dout = dout + interClusterDistance(k_clusters[i],k_clusters[j]);
                }
            }

            for(std::size_t i = 0; i < k; i++){
                pin = pin + k_clusters[i].getClusterEdges();
            }

            for(std::size_t i = 0; i < k;){
                for(std::size_t j = i++; j < k; j++){
                    pout = pout + interClusterEdges(k_clusters[i],k_clusters[j]);
                }
            }

            prevBetaCV = BetaCV;
            BetaCV = (din/pin)/(dout/pout);
            DbetaCV = fabs(prevBetaCV - BetaCV);

            scoreDiff = DbetaCV;
            count++;
        }
        return 0;
    }

    template<typename T, int k, int dim>
    std::ostream &operator<< (std::ostream &os, const KMeans<T,k,dim> &kmean){
        for(std::size_t i = 0; i < k; i++){
            os << kmean.k_clusters[i];
        }
        return os;
    }

    template<typename T, int k, int dim>
    std::istream &operator>> (std::istream &is, KMeans<T,k,dim> &kmean){
        is >> kmean.point_space;
        kmean.k_clusters[0] = kmean.point_space;
        return is;
    }
};
