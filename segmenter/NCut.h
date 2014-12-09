#ifndef NCUT_H
#define NCUT_H
#include <cstdio>

#define SORT true
#define THRESHOLD 0.0
#define IDEAL_RATIO 0.06 // Toto cislo je prevzato primo z clanku od Malik, Shi.
#define RESIZE 16

class Node{
public:
	int x;
	int y;
        int cluster;
	float color;
        bool isInCluster;
	Node(int x,int y,float color){
		this->x=x;
		this->y=y;
		this->color=color;
                this->isInCluster = false;
	}
        void print()
        {
            printf("[%d,%d], color = %f.\n",this->x,this->y,this->color);
        }
};

class NCut{
private:
    int clusterCnt;
    int originalLenght1;
    int originalLenght2;
    int lenght1;
    int lenght2;
    Node ** nodes;//uzly
    int nodesCnt;
    float ** affinityMatrix;		//matice podobnosti
    float ** degreeMatrix;			//matice degree
    int ** resultMatrix;			//vysledna segmentace
    float eigenvalue;				//vlastni cislo 2nd
    float * eigenvector;			//vlastni vektor
    int nextClusterID;
     
    int countPosition(int x,int y);
    void countCoords(int &x, int &y, int position);
    
    float *** resizeInput(float *** img,int &lenght1,int &lenght2);
    
    void SimplifyEquation();            // prevede do tvaru Ax=lambda x
    float weightFunction(int node1, int node2);
    void CreateAffinityMatrix();	// vytvori matici podobnosti
    void CreateDegreeMatrix(); 		// vytvori degree matici
    void ComputeEigenVector(int eigvalOffset = 0);		// vypocita vlastni vektor
    void Cut();				// provede rez
    float getClusterRatio(float max, float min); //zjisti pomer, dle ktereho pozna, jestli jde uz o cely cluster nebo se bude dal delit
	
public:
    NCut(float *** input,int lenght1, int lenght2, int clusterCnt); // vyplni inputMatrix ("splacne")
    ~NCut();
    void Segmentation();			// vlastni segmentace
    int ** getResult();				// vrati vysledek
    void SetProbs(float *** probs);
};
#endif
