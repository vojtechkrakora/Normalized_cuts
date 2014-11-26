#include "NCut.h"

// vytvori matici podobnosti
void NCut::CreateAffinityMatrix(){

}
	
// vytvori degree matici
void NCut::CreateDegreeMatrix(){
}
// vypocita vlastni cislo (2nd)
void NCut::ComputeEigenValue(){

}
// vypocita vlastni vektor
void NCut::ComputeEigenVector(){

}
//provede rez
void NCut::NCut(){

}

NCut::NCut(double *** input,int lenght1, int lenght2, int lenght3){
	int size=lenght1+lenght2;
	int index=0;
	double * nodes=new double[size];
	for(int i=0;i<lenght1;i++){
		for(int j=0;j<lenght2;j++){
			nodes[index]=(input[i,j,0]+input[i,j,1]+input[i,j,2])/3.0;
		}
	}	
	double ** adjacencyMatrix=new double[size];
	for(int i =0;i<size;i++){
		adjacencyMatrix[i]=new double[size];
		memset(adjecencyMatrix[i],0,size);
	}
	
}
void NCut::Sementation(){

}
int** NCut::getResult(){

return null;
}
