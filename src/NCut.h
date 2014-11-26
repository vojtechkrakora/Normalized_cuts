#ifndef NCUT_H
#define NCUT_H
class NCut{
private:
	double ** adjacencyMatrix;		//matice sousednosti
	double ** affinityMatrix;		//matice podobnosti
	double ** degreeMatrix;			//matice degree
	int *** resultMatrix;			//vysledna segmentace
	double eigenvalue;				//vlastni cislo 2nd
	double * eigenvector;			//vlastni vektor

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
