#ifndef NCUT_H
#define NCUT_H

#define SORT true
#define THRESHOLD 0.0

class Node{
public:
	int x;
	int y;
        int cluster;
	float color;
	Node(int x,int y,float color){
		this->x=x;
		this->y=y;
		this->color=color;
	}
};

class NCut{
private:
    int clusterCnt;
    int lenght1;
    int lenght2;
    Node ** nodes;//uzly
    int nodesCnt;
    float ** affinityMatrix;		//matice podobnosti
    float ** degreeMatrix;			//matice degree
    int *** resultMatrix;			//vysledna segmentace
    float eigenvalue;				//vlastni cislo 2nd
    float * eigenvector;			//vlastni vektor

    int countPosition(int x,int y);
    void countCoords(int &x, int &y, int position);

    void SimplifyEquation();            // prevede do tvaru Ax=lambda x
    float weightFunction(int node1, int node2);
    void CreateAffinityMatrix();	// vytvori matici podobnosti
    void CreateDegreeMatrix(); 		// vytvori degree matici
    void ComputeEigenValue();		// vypocita vlastni cislo (2nd)
    void ComputeEigenVector();		// vypocita vlastni vektor
    void Cut();				// provede rez
	
public:
    NCut(float *** input,int lenght1, int lenght2, int lenght3, int clusterCnt); // vyplni inputMatrix ("splacne")
    ~NCut();
    void Segmentation();			// vlastni segmentace
    int ** getResult();				// vrati vysledek
};
#endif
