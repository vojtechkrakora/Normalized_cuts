#ifndef NCUT_H
#define NCUT_H

class Edge{
public:
	int from;
	int to;
	double weight;
	Edge(int from, int to, double weight){
		this->from=from;
		this->to=to;
		this->weight=weight;
	}	
};

class Node{
public:
	int x;
	int y;
	double color;
	Edge * edges;
	int edgesCnt;
	Node(int x,int y,double color){
		this->x=x;
		this->y=y;
		this->color=color;
		this->edges=new Edge[8];
		this->edgesCnt=0;
	}
	void createEdges(Node* nodes,int lenght1, int lenght2);
};

class NCut{
private:
	int lenght1;
	int lenght2;
	Node * nodes;					//uzly
	double ***inputMatrix;			//vstupni matice;
	double ** affinityMatrix;		//matice podobnosti
	double ** degreeMatrix;			//matice degree
	int *** resultMatrix;			//vysledna segmentace
	double eigenvalue;				//vlastni cislo 2nd
	double * eigenvector;			//vlastni vektor


	double weightFunction(int x1,int y1, int x2,int y2);
	void CreateAffinityMatrix();	// vytvori matici podobnosti
	void CreateDegreeMatrix(); 		// vytvori degree matici
	void ComputeEigenValue();		// vypocita vlastni cislo (2nd)
	void ComputeEigenVector();		// vypocita vlastni vektor
	void NCut()						// provede rez
	
public:
	NCut(double *** input,int lenght1, int lenght2, int lenght3); // vyplni inputMatrix ("splacne")
	void Sementation();				// vlastni segmentace
	int ** getResult();				// vrati vysledek
};
#endif
