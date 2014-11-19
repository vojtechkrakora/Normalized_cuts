#ifndef NCUT_H
#define NCUT_H
class NCut{
private:
	double *** matrix;
	double *** affinityMatrix;
	double *** degreeMatrix;
	int *** resultMatrix;

	void CreateGraph();
	void SolveEquation();
	double * getEigenVector
	
public:
	NCut(double *** input);
	void Sementation();	
};
#endif
