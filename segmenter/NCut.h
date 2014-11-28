#ifndef NCUT_H
#define NCUT_H


class Node{
public:
	int x;
	int y;
	double color;
	Node(int x,int y,double color){
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
    double ** affinityMatrix;		//matice podobnosti
    double ** degreeMatrix;			//matice degree
    int *** resultMatrix;			//vysledna segmentace
    double eigenvalue;				//vlastni cislo 2nd
    double * eigenvector;			//vlastni vektor

    int countPosition(int x,int y);
    void countCoords(int &x, int &y, int position);

    double** SimplifyEquation(double** D, double** A );
    double weightFunction(int node1, int node2);
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
