#include "NCut.h"
#include "Maths.h"
#include <cmath>
#include <cstring>
#include <cstdio>


//nasobení matic... mozna optimalizace pro diagonalni matice
float ** MatrixMultiply(float ** matA, float ** matB, float** matC, int rowCnt, bool matBisDiagonal=false){
    if(matC==0){
        matC=new float*[rowCnt];
        for(int i=0;i<rowCnt;i++){
            matC[i]=new float[rowCnt];
        }
    }
    for(int i=0;i<rowCnt;i++){
        for(int j=0;j<rowCnt;j++){
            matC[i][j]=0;
            for(int k=0;k<rowCnt;k++){
                matC[i][j]+=matA[i][k]*matB[k][j];
            }
        }
    }
    return matC;
}

float RGBtoGreyLuminosity(float r, float g, float b){
    return ((0.21*r)+(0.72*g)+(0.07*b));
}

float RGBtoGrey(float r, float g, float b){
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
float NCut::weightFunction(int node1, int node2){
    float sigma=2.0;
    Node* n1 = nodes[node1];
    Node* n2 = nodes[node2];
    float distance = sqrt((n1->x-n2->x)*(n1->x-n2->x)
        + (n1->y-n2->y)*(n1->y-n2->y));
    distance/=sigma;
    distance = exp((-1)*fabs(distance));
    float affinity=fabs(n1->color-n2->color);
    affinity/=sigma;
    affinity=exp((-1)*affinity);
    return affinity*distance;
}

// vytvori matici podobnosti
void NCut::CreateAffinityMatrix(){
    int size=lenght1*lenght2;
    affinityMatrix = new float*[size];
    for(int i=0;i<size;i++){
    	affinityMatrix[i] = new float[size];
    	for(int j=0;j<size;j++){
            affinityMatrix[i][j]=weightFunction(i,j);
	}
    }
}
	
// vytvori degree matici
void NCut::CreateDegreeMatrix(){
    degreeMatrix = new float*[nodesCnt];
    for(int i=0;i<nodesCnt;i++){
	degreeMatrix[i] = new float[nodesCnt];
	memset(degreeMatrix[i],0,nodesCnt);	
    }
    for(int item=0;item<nodesCnt;item++){
	for(int i=0;i<nodesCnt;i++){
            if(i==item)continue; // hadam ze se nema zapocitavat on sam
            degreeMatrix[item][item]+=weightFunction(item,i);
	}
    }
}
// A = D^(-1/2)*(D-A)*D^(-1/2) 
// ulozi do affinityMatrix
// je pak možné počítat A*x = labda*x
void NCut::SimplifyEquation(){
    //A=(D-A)
    for(int i=0;i<nodesCnt;i++){
        for(int j=0;j<nodesCnt;j++){
            affinityMatrix[i][j]=degreeMatrix[i][j]-affinityMatrix[i][j];
        }
    }
    //D=sqrt(D)
    //D=D^-1
    for(int i=0;i<nodesCnt;i++){
        degreeMatrix[i][i]=sqrt(degreeMatrix[i][i]);
        degreeMatrix[i][i]=1.0/degreeMatrix[i][i];
    }    

    float ** tmp=new float*[nodesCnt];
    for(int i=0;i<nodesCnt;i++){
        tmp[i]=new float[nodesCnt];
    }
        //maticove nasobeni
    //A = multiply(multiply(D,A),D)
    //tmp = D*A
    MatrixMultiply(degreeMatrix,affinityMatrix,tmp,nodesCnt);
    //A=tmp*D
    MatrixMultiply(tmp,degreeMatrix, affinityMatrix,nodesCnt);
    for(int i=0;i<nodesCnt;i++){
        delete []tmp[i];
    }
    delete[] tmp;
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
        	float color=RGBtoGrey(input[0][i][j],input[1][i][j],input[2][i][j]);
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
    SimplifyEquation();
    
}

int** NCut::getResult(){

    return 0;
}
