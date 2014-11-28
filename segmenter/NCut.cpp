#include "NCut.h"
#include <cmath>
#include <cstring>
#include <cstdio>

double RGBtoGreyLuminosity(double r, double g, double b){
    return ((0.21*r)+(0.72*g)+(0.07*b));
}

double RGBtoGrey(double r, double g, double b){
    return (r+g+b)/3.0;
}

//TODO Zkontrolovat
//vypocet pozice na zaklade souradnic v realnem obrazku
int NCut::countPosition(int x,int y){
    int position=x*lenght1 + y;
    return position;
}

//TODO Zkontrolovat
//vypocet souradnic v realnem obrazku z pozice v poli
void NCut::countCoords(int &x, int &y, int position){
    x=position/lenght1;
    y=position%lenght1;
}

//funkce vypoctu podobnosti 2 pixelu (rozdil barvy/vzdalenosti)
double NCut::weightFunction(int node1, int node2){
    double sigma=2.0;
    Node* n1 = nodes[node1];
    Node* n2 = nodes[node2];
    double distance = sqrt((n1->x-n2->x)*(n1->x-n2->x)
        + (n1->y-n2->y)*(n1->y-n2->y));
    distance/=sigma;
    distance = exp((-1)*fabs(distance));
    double affinity=fabs(n1->color-n2->color);
    affinity/=sigma;
    affinity=exp((-1)*affinity);
    return affinity*distance;
}

// vytvori matici podobnosti
void NCut::CreateAffinityMatrix(){
    int size=lenght1*lenght2;
    affinityMatrix = new double*[size];
    for(int i=0;i<size;i++){
    	affinityMatrix[i] = new double[size];
    	for(int j=0;j<size;j++){
            affinityMatrix[i][j]=weightFunction(i,j);
	}
    }
}
	
// vytvori degree matici
void NCut::CreateDegreeMatrix(){
    degreeMatrix = new double*[nodesCnt];
    for(int i=0;i<nodesCnt;i++){
	degreeMatrix[i] = new double[nodesCnt];
	memset(degreeMatrix[i],0,nodesCnt);	
    }
    for(int item=0;item<nodesCnt;item++){
	for(int i=0;i<nodesCnt;i++){
            if(i==item)continue; // hadam ze se nema zapocitavat on sam
            degreeMatrix[item][item]+=weightFunction(item,i);
	}
    }
}
// TODO dodělat
// B = D^(-1/2)*(D-A)*D^(-1/2) 
// vrati B
double** NCut::SimplifyEquation(double** D, double** A ){
    //A=(D-A)
    for(int i=0;i<nodesCnt;i++){
        for(int j=0;j<nodesCnt;j++){
            affinityMatrix[i][j]=degreeMatrix[i][j]-affinityMatrix[i][j];
        }
    }
    //D=sqrt(D)
    for(int i=0;i<nodesCnt;i++){
        degreeMatrix[i][i]=sqrt(degreeMatrix[i][i]);
    }
    //inverzni matici z degree
    //inverse(degreeMatrix);
    //D = D^(-1/2)
    
    //maticove nasobeni
    //B = multiply(multiply(D,A),D)
    return 0;// return B
}

// vypocita vlastni cislo (2nd)
void NCut::ComputeEigenValue(){
	
}
// vypocita vlastni vektor
void NCut::ComputeEigenVector(){

}
//provede rez
void NCut::Cut(){

}
//TODO ulozit clustersCnt
NCut::NCut(float *** input,int lenght1, int lenght2, int lenght3,int clustersCnt){
    nodes= new Node*[lenght1*lenght2];
    nodesCnt=0;
    for(int i=0;i<lenght1;i++){
    	for(int j = 0;j<lenght2;j++){
        	double color=RGBtoGrey(input[0][i][j],input[1][i][j],input[2][i][j]);
                nodes[nodesCnt++]= new Node(i,j,color);
        }
    }
    this->lenght1=lenght1;
    this->lenght2=lenght2;
}   
NCut::~NCut(){
    //TODO
}
void NCut::Segmentation(){
    CreateAffinityMatrix();
    CreateDegreeMatrix();
}

int** NCut::getResult(){

    return 0;
}
