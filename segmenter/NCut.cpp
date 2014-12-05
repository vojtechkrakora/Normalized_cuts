#include "NCut.h"
#include "Maths.h"
#include <cmath>
#include <cstring>
#include <cstdio>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace Eigen;
using Eigen::MatrixXd;

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

void print_matrix(float ** matrix, int size)
{
    for(int i = 1; i <= size; i++)
    {
        for(int j = 1; j<= size; j++)
        {
            printf("%f ",matrix[j][i]);
        }
        printf("\n");
    }
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
    //n1->print();
    //n2->print();
    float distance = sqrt((n1->x-n2->x)*(n1->x-n2->x)
        + (n1->y-n2->y)*(n1->y-n2->y));
    distance/=sigma;
    distance = exp((-1)*fabs(distance));
    float affinity=fabs(n1->color-n2->color);
    affinity/=sigma;
    affinity=exp((-1)*affinity);
    
    //printf("Weight %f.\n",affinity*distance);
    return affinity*distance;
}

// vytvori matici podobnosti
void NCut::CreateAffinityMatrix(){
    int size=nodesCnt+1; //indexovani od 1
    affinityMatrix = new float*[size];
    for(int i=1;i<size;i++){
    	affinityMatrix[i] = new float[size];
    	for(int j=1;j<size;j++){
            affinityMatrix[i][j]=weightFunction(i,j);
	}
    }
    
    //print_matrix(affinityMatrix,nodesCnt);
}
	
// vytvori degree matici
// predelano na indexovani od 1
void NCut::CreateDegreeMatrix(){
    int size=nodesCnt+1; // kvuli indexovani od 1
    float tmp = 0.0;
    degreeMatrix = new float*[size];
    
    for(int i=0;i<size;i++){
	degreeMatrix[i] = new float[size];
        for(int j = 0;j <size; j++)
            degreeMatrix[i][j] = 0;
    }
    
    for(int item=1;item<size;item++){
	for(int i=1;i<nodesCnt+1;i++){
            if(i==item)continue; // hadam ze se nema zapocitavat on sam
            degreeMatrix[item][item]+=weightFunction(item,i);
            tmp +=weightFunction(item,i);
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
        degreeMatrix[i][i]= sqrt(degreeMatrix[i][i]);
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
    float ** tmp_matrix; // protoze eigs_qr vstupni matici znici
    
    tmp_matrix = new float*[nodesCnt];
    for(int i=0;i<nodesCnt+1;i++){
    	tmp_matrix[i] = new float[nodesCnt+1];
    }
    
    for(int i = 1; i < nodesCnt+1; i++)
    {
        for(int j = 1; j < nodesCnt+1;j++)
            tmp_matrix[j][i] = affinityMatrix[j][i];
    }
    
    // Do wr[] vypocte vsechna vlastni cisla a seradi je sestupne.
    eigs_qr(tmp_matrix, nodesCnt, wr, wi, SORT);
    
    /*Radeji kontrola, protoze z wr budeme brat vzdy hodnotu na druhem miste */
    if(nodesCnt <= 1)
        printf("Error nodesCnt is low value: %d. Eigenvalue can't be valid.\n",
                nodesCnt);
    
    /*Nastaveni druheho nejmensiho vlastniho cisla*/
    eigenvalue = wr[nodesCnt-1];
}
// vypocita vlastni vektor
void NCut::ComputeEigenVector(){
    MatrixXd matrix(nodesCnt,nodesCnt);
    
    /* Naplni se matrix hodnotama affinityMatrix 
     * MatrixXd ma obracene souradnice a cisluje od nuly
     * viz http://eigen.tuxfamily.org/dox/group__matrixtypedefs.html#ga0750af9a6b82761985a15fe77256de87
     */
    for(int i = 0; i < nodesCnt; i++)
    {
        for(int j = 0; j < nodesCnt; j++)
        {
            matrix(i,j) = affinityMatrix[j+1][i+1];
        }
    }
    
    /* Vyreseni veskerych vlastnich cisel a vektoru, ulozeno v promenne
     * solved_eigen_problem.
     * http://eigen.tuxfamily.org/dox/classEigen_1_1EigenSolver.html
     */
    EigenSolver<MatrixXd> solved_eigen_problem(matrix);
    
    /* Ulozeni hodnot do vlastniho vektoru. .real() tam je aby to nebylo v 
     * komplexnim cisle, tak vyjadrujeme pouze jeji realnou slozku.
     */
    for(int i = 1; i < nodesCnt; i++)
    {
        eigenvector[i] = solved_eigen_problem.eigenvectors().real()(i-1,nodesCnt-1-1);
    }
}
//provede rez
void NCut::Cut(){
    
    //float threshold = eigenvector[16*32+1];
    float threshold = 0.0;
    
    for(int i = 1; i < nodesCnt+1; i++)
    {
        threshold += eigenvector[i];
    }
    //threshold /= nodesCnt;
    
    for(int i = 1; i < nodesCnt+1; i++)
    {
        if(eigenvector[i] < threshold) /*TODO*/
        {
            nodes[i]->cluster = 0;
        } else
        {
            nodes[i]->cluster = 1;
        }
    }
    
    for(int i = 1; i < nodesCnt+1; i++)
    {
        if((i-1)%3 == 0)
        {
            printf("\n");
        }
        
        //printf("%.2f|",nodes[i]->color);
        printf("%d ",nodes[i]->cluster);
    }
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
    this->eigenvector = new float[nodesCnt+1];
}   
NCut::~NCut(){
    //TODO
}
void NCut::Segmentation(){
    CreateAffinityMatrix();
    CreateDegreeMatrix();
    SimplifyEquation();
   // ComputeEigenValue();
    ComputeEigenVector();
    Cut();
}

int** NCut::getResult(){

    return 0;
}
