#include "NCut.h"
#include "Maths.h"
#include <cmath>
#include <cstring>
#include <cstdio>


//nasobení matic... mozna optimalizace pro diagonalni matice
//predelano na indexovani od 1
/*float ** MatrixMultiply(float ** matA, float ** matB, float** matC, int rowCnt, bool matBisDiagonal=false){
    if(matC==0){
        matC=new float*[rowCnt+1];
        for(int i=1;i<=rowCnt;i++){
            matC[i]=new float[rowCnt+1];
        }
    }
    for(int i=1;i<=rowCnt;i++){
        for(int j=1;j<=rowCnt;j++){
            matC[i][j]=0;
            for(int k=1;k<=rowCnt;k++){
                matC[i][j]+=matA[i][k]*matB[k][j];
            }
        }
    }
    return matC;
}*/

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
    return position+1; //indexovani od 1;
}

//TODO Zkontrolovat
//vypocet souradnic v realnem obrazku z pozice v poli
void NCut::countCoords(int &x, int &y, int position){
    position-=1; //indexovani od 1;
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
    int size=nodesCnt+1; //indexovani od 1
    affinityMatrix = new float*[size];
    for(int i=0;i<size;i++){
    	affinityMatrix[i] = new float[size];
    	for(int j=i;j<size;j++){
            affinityMatrix[i][j]=weightFunction(i,j);
	}
    }
}
	
// vytvori degree matici
// predelano na indexovani od 1
void NCut::CreateDegreeMatrix(){
    int size=nodesCnt+1; // kvuli indexovani od 1
    degreeMatrix = new float*[size];
    for(int i=0;i<size;i++){
	degreeMatrix[i] = new float[size];
	memset(degreeMatrix[i],0,size);	
    }
    for(int item=1;item<size;item++){
	for(int i=1;i<nodesCnt+1;i++){
            if(i==item)continue; // hadam ze se nema zapocitavat on sam
            degreeMatrix[item][item]+=weightFunction(item,i);
	}
    }
}
// A = D^(-1/2)*(D-A)*D^(-1/2) 
// ulozi do affinityMatrix
// je pak možné počítat A*x = labda*x
// predelano na indexovani od 1
void NCut::SimplifyEquation(){
    //A=(D-A)
    for(int i=1;i<nodesCnt+1;i++){
        for(int j=1;j<nodesCnt+1;j++){
            affinityMatrix[i][j]=degreeMatrix[i][j]-affinityMatrix[i][j];
        }
    }
    //D=sqrt(D)
    //D=D^-1
    for(int i=1;i<nodesCnt+1;i++){
        degreeMatrix[i][i]=sqrt(degreeMatrix[i][i]);
        degreeMatrix[i][i]=1.0/degreeMatrix[i][i];
    }    

    float ** tmp=new float*[nodesCnt+1];
    for(int i=0;i<nodesCnt+1;i++){
        tmp[i]=new float[nodesCnt+1];
    }
    //A = multiply(multiply(D,A),D)
    //tmp = D*A
    MatrixMultipl(degreeMatrix, nodesCnt,nodesCnt,affinityMatrix, nodesCnt, nodesCnt, tmp);
    //MatrixMultiply(degreeMatrix,affinityMatrix,tmp,nodesCnt); -- stara funkce pak smazat
    //A=tmp*D
    MatrixMultipl(tmp, nodesCnt,nodesCnt,degreeMatrix, nodesCnt, nodesCnt, affinityMatrix);
    //MatrixMultiply(tmp,degreeMatrix, affinityMatrix,nodesCnt); -- stara funkce pak smazat
    for(int i=1;i<nodesCnt+1;i++){
        delete []tmp[i];
    }
    delete[] tmp;
}

// vypocita vlastni cislo (2nd)
void NCut::ComputeEigenValue(){
    float *wr = new float[nodesCnt];
    float *wi = new float[nodesCnt];
    //prevede do hessenbergovy matice
    //elmhes(affinityMatrix, nodesCnt);
    //vypocita vlastni cisla
    //void hqr(TREAL **a, int n, TREAL wr[], TREAL wi[]);
    //seradi vlastni cisla
    //void eigsrt(TREAL *wr, TREAL *wi, int n);
    
    //melo by udelat vse najednou
    //eigs_qr(affinityMatrix, int n, TREAL wr[], TREAL wi[], bool sort);
}
// vypocita vlastni vektor
void NCut::ComputeEigenVector(){
    // vypocitat vektor
}
//provede rez
void NCut::Cut(){
    // rozdělit na 2 grafy a pripadne rekurzivně zavolat podle poctu clusterů
}

NCut::NCut(float *** input,int lenght1, int lenght2, int lenght3,int clustersCnt){
    this->clusterCnt=clustersCnt;
    nodes= new Node*[(lenght1*lenght2)+1];
    nodesCnt=0;
    for(int i=0;i<lenght1;i++){
    	for(int j = 0;j<lenght2;j++){
        	float color=RGBtoGrey(input[0][i][j],input[1][i][j],input[2][i][j]);
                nodes[nodesCnt+1]= new Node(i+1,j+1,color);
                nodesCnt++;
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
    ComputeEigenValue();
    ComputeEigenVector();
    Cut();
}

int** NCut::getResult(){

    return 0;
}
