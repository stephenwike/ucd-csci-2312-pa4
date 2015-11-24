# ucd-csci2312-pa4

#### *	ALL CLASSES ARE IN NAMESPACE: Clustering
#### *	COMPILED WITH G++ ON CLION

#Header: Point<T,dim>
##Class: Point

--Point is a multi - dimensional point.  
--Values can be assigned, edited, and changed with basic arithmetic.

####Private Member Variables

`std::vector<T> p_val`
--p_val is a vector of dimensional values of type T.
`unsigned int p_dim;`
--p_dim tracks the dimensionality of the Point.
`unsigned int p_id;`
--p_id assigns a unique id to the Point.
	
####Constructor && Copy Constructor && Overloaded Assignment && Destructor

`Point();`
--Point constructed with specified type and dimension.
`Point(const Point &);`
--Makes a copy of an existing Point.
`Point &operator=(const Point &);`
--Assigns Point values to a Point.
`~Point();`
--Point destructor called when the Point is out of scope.
	
####Accessors and Mutator Methods

`unsigned int getDim(unsigned int) const;`
--Returns the T value at specified index.
`void setDim(unsigned int, const T &);`
--Requires an int within the range of Point's dimensionality.
--Sets the value of a Point's dimension at specified index to a given type T.
`unsigned int getId() const;`
--Returns the id of a Point.
`void setId(unsigned int);`
--Sets the id of a Point.
`double &operator[](int index)`
--Allows access to Point's dimensions by 0-based index.

####Comparison Operators

`friend bool operator== <> (const Point &, const Point &);`
--Compares two Points exact id.
`friend bool operator!= <> (const Point &, const Point &);`
--Compares two Points for inequality.
`friend bool operator< <> (const Point &, const Point &);`
--Compares left Point for less than right Point.
`friend bool operator> <> (const Point &, const Point &);`
--Compares left Point for greater than right Point.
`friend bool operator<= <> (const Point &, const Point &);`
--Compares left Point for less than or equal to right Point.
`friend bool operator>= <> (const Point &, const Point &);`
--Compares left Point for greater than or equal to right Point.

####Arithmetic Operators

`friend Point &operator+= <> (Point &, const Point &);`
--Adds and assigns the values of a Point to a Point.
`friend Point &operator-= <> (Point &, const Point &);`
--Subtracts and assigns the values of a Point to a Point.
`friend const Point operator+ <> (const Point &, const Point &);`
--Returns a Point with the sum value of two Points.
`friend const Point operator- <> (const Point &, const Point &);`
--Returns a Point with the difference in value of two Points.
`Point &operator*=(double);`
--Multiplies and assigns a Point increase by the magnitude of a passed double.
`const Point operator*(double) const;`
--Returns a Point with values multiplied by passed double.
`Point &operator/=(double);`
--Divides and assigns a Point divided by a divisor of passed double.
`const Point operator/(double) const;`
--Returns a Point with values divided by divisor double.

####IOstream Operators

`friend std::ostream &operator<< <> (std::ostream &, const Point &);`
--Prints Point's dimensional values.
`friend std::istream &operator>> <> (std::istream &, Point &);`
--Reads Point's dimensional values from stream or file.
	
####Member Functions

`double distanceTo(const Point &) const;`
--finds the distance bewteen two points of same dimensionality



#Header: Cluster<T,dim>
##Class: Cluster

--The Cluster class contains a set of Points.
--This is a list of Cluster member functions and variables

###Subclass: Centroid

--Centroid is a Point.
--Centroid is the center of a Cluster.

####Private Member Variables

`T __centroid;`
--A centroid of a Point type.
`unsigned int __dimension;`
--Shares dimension with Point dimension

####Accessors and Mutator Methods

`const T get() const;`
--Returns a Cluster's Point Centroid.
`void set(const T &point);`
--Sets the Cluster's Point Centroid

####Private Member Variables

`int c_dim;`
--The dimensions of the Points Cluster contains.
`Centroid c_cent;`
--A Centroid Point that acts as Cluster's center.
`unsigned int c_size;`
--Amount of Points in the Cluster.
`unsigned int c_id;`
--Cluster's Unique ID.
`bool c_valid;`
--Cluster's Centroid is invalidated when modified.  Must be re-validated.

####Public Member Variables
`static std::unordered_map<unsigned int,double> distMap;`
--Map of Point distances.  They key is the cantor value of the two point's id's.
`std::forward_list<T> c_points;`
--list of Points in the Cluster class.

###Subclass: Move

####Private Member Variables
`T m_point;`
--Point that will be moved.
`Cluster<T,dim> *from;`
--Cluster that Point will be moved from.
`Cluster<T,dim> *to;`
--Cluster that Point will be moved to.

####Constructor
`Move()`
--Makes a blank Move that lack initialization.
`Move(const T &p, Cluster *f, Cluster *t);`
--Makes an initialized Move object.

####Functions
`void perform()`
--Perform the move of a point from one Cluster to the other.

##Class: Cluster

####Constructor
`Cluster();`
--Creates a Cluster and assigns an ID.

####Copy Constructor && Overloaded Assignment && Destructor
`Cluster(const Cluster &);`
--Creates a copy of an existing Cluster to a new Cluster.
`Cluster &operator=(const Cluster &);`
--Clears a Cluster of Points and replaces with the Points of another Cluster.
--Checks for self assignment.
`~Cluster();`
--Dealocates Cluster.
	
####Accessors and Mutators
unsigned int getSize() cons;
--Returns Cluster Size.
void setSize(unsigned int s);
--Sets Cluster Size.
unsigned int getId() const;
--Returns Cluster ID.
void setId(unsigned int i);
--Sets Cluster ID.
bool getValid() const;
--Returns Centroid Validity.
void setValid(bool v);
--Sets Centroid Validity.
T getCent() const;
--Returns Centroid.
void setCent(const T point);
--Sets the Centroid.
	
####Comparison Operators
`friend bool operator==(const Cluster &lhs, const Cluster &rhs);`
--Compares two clusters for equal Cluster ID's.
`friend bool operator!=(const Cluster &lhs, const Cluster &rhs);`
--Compares two clusters for not equal Cluster ID's.

####Arithmetic Operators
`Cluster &operator+=(const Cluster &);`
--Unions two Clusters together.
`Cluster &operator-=(const Cluster &);`
--Removes identical Points in one Cluster from another.
`Cluster &operator+=(const T &);`
--Adds a new Point to a Cluster from a new set.
`Cluster &operator-=(const T &);;`
--Removes all Points with the same values as passed Point.
`friend const Cluster operator+<>(const Cluster &, const Cluster &);`
--Returns a Cluster with the combination of two Clusters.
`friend const Cluster operator-<>(const Cluster &, const Cluster &);`
--Returns a Cluster.
--Any identical Points from the left hand side Cluster are removed from the right.
`friend const Cluster operator+<>(const Cluster &, const T &);`
--Returns a Cluster with an added Point.
`friend const Cluster operator-<>(const Cluster &, const T &);`
--Returns a Cluster with a Point removed.

####IOstream Operators
`friend std::ostream &operator<<(std::ostream &, const Cluster &);`
--Prints a set of Points of a Cluster from the ostream.
`friend std::istream &operator>>(std::istream &, Cluster &);`
--Grabs a set of Points from a stream or file into a Cluster.

####Functions		
`void add(const T &);`
--Add's a Point to a Cluster.
--Does not allow for a duplicate of the same Point.
`const T &remove(const T &);`
--Remove's a Point from a Cluster.
`void computeCentroid();`
--Computes the Centroid of a Cluster and validates c_valid.
`void pickPoints(int k, Cluster&);`
--Find Points to act as initial k_Cluster Centroids.

####Functions for Kmeans Algorithm
`double intraClusterDistance() const;`
--Calculates intraClusterDistance within a Cluster.
`friend double interClusterDistance<>(const Cluster &, const Cluster &);`
--Calculates interClusterDistance between two Clusters.
`friend double interClusterEdges<>(const Cluster &, const Cluster &);`
--Calculates interClusterEdges between two Cluster's edges.
`int getClusterEdges();`
--Calculates intraClusterEdges within a Cluster.

#Header: KMeans<T,k,dim>
##Class: KMeans

####Private Member Variables
`std::vector<T> k_clusters;`
--KMeans K Clusters that Points are sorted into.
`T point_space;`
--KMeans initial Cluster that contains all the the Points

####Constructor
`KMeans<T,k,dim>();`

####IOstream
`friend std::ostream &operator<< <> (std::ostream &, const KMeans &);`
--Outputs the Clusters organized by the KMeans sorting algorithm.
`friend std::istream &operator>> <> (std::istream &, KMeans &);`
--Grabs input from a document and runs a sorting algorithm.

####Functions
`double computeClusteringScore();`
--Computes the score to analyze the Kmeans sorting algorithm.