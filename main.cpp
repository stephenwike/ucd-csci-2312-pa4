#include <iostream>
#include "Point.h"
#include "Cluster.h"
#include "KMeans.h"

using namespace std;
using namespace Clustering;

int main() {

    ifstream inFile;
    inFile.open("dim3pts100000.txt");

    KMeans<Cluster<Point<double,3>,3>,5,3> kmeans;

    inFile >> kmeans;

    kmeans.computeClusteringScore();

    fstream file;
    file.open("output.txt", ios::out);

    file << kmeans;
    cout << kmeans;

    return 0;
}