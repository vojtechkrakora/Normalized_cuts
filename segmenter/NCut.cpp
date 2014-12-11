#include "NCut.h"
#include "Maths.h"
#include <map>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>
#include <iostream>
#include <climits>

using namespace Eigen;
using Eigen::MatrixXd;

bool AreSameFloats(float a, float b) {
    return std::fabs(a - b) < std::numeric_limits<float>::epsilon();
}

/* Vypocte median, s input pracuje jako input[1..size]*/
float NCut::get_median(const float * input, const int size)
{
    float * sorted = new float[size+1];
    sorted[0] = 0.0;
    float result;
    
    for(int i = 1; i < size +1; i ++)
    {
        sorted[i] = input[i];
    }

    std::sort(sorted, sorted + size, std::greater<float>());
    
    result = sorted[size/2];
    
    /* Nula je spatne cislo na vypocet ratia, proto hranici posuneme. */
    if(AreSameFloats(result,0.0)){
        return 1.0;
    }
    delete [] sorted;
    return result;
}

void print_matrix(float ** matrix, int size)
{
    printf("{");
    for(int i = 1; i <= size; i++)
    {
        printf("{");
        for(int j = 1; j<= size; j++)
        {
            printf("%f,",matrix[j][i]);
        }
        printf("\n");
        printf("},");
    }
    printf("}");
}

float RGBtoGreyLuminosity(float r, float g, float b){
    return ((0.21*r)+(0.72*g)+(0.07*b))/3;
}

float RGBtoGrey(float r, float g, float b){
    return (r+g+b)/3.0;
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
    for(int i=1;i<size;i++){
    	affinityMatrix[i] = new float[size];
    	for(int j=1;j<size;j++){
            affinityMatrix[i][j]=weightFunction(i,j);
	}
    }
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
    //A=tmp*D
    MatrixMultipl(tmp, nodesCnt,nodesCnt,degreeMatrix, nodesCnt, nodesCnt, affinityMatrix);
    for(int i=0;i<nodesCnt+1;i++){
        delete []tmp[i];
    }
    delete[] tmp;
}

// vypocita vlastni vektor
void NCut::ComputeEigenVector(int eigvalOffset){
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
    EigenSolver<MatrixXd> es(matrix);
    
    /* Ulozeni hodnot do vlastniho vektoru. .real() tam je aby to nebylo v 
     * komplexnim cisle, tak vyjadrujeme pouze jeji realnou slozku.
     */
    float * eigenvalues = new float[nodesCnt];
    //nacte eigenvalues
    for(int i=0;i<nodesCnt;i++){
        eigenvalues[i]=es.eigenvalues().real()(i);
    }
    //seradi je podle velikosti
    std::sort(eigenvalues, eigenvalues + nodesCnt, std::greater<float>());
    //druhe nejmensi
    eigenvalue=eigenvalues[nodesCnt-1];
    int eigenvalueIndex=-1;
    //najde kde se nachazii druhe nejmensi vlastni cislo
    for(int i = 0;i<nodesCnt;i++){
        if(AreSameFloats(es.eigenvalues().real()(i),eigenvalue)){
            eigenvalueIndex=i;
            break;
        }
    }
    
    eigenvalueIndex+=eigvalOffset;
    
    //vlastni vektor
    for(int i = 1; i < nodesCnt+1; i++){
        eigenvector[i] = es.eigenvectors().real()(i-1,eigenvalueIndex)*1000;
    }
    delete []eigenvalues;
}

//provede rez
void NCut::Cut(){      
    float threshold = 0.00;
    float cluster1_max = INT_MIN, cluster2_max = INT_MIN, 
            cluster1_min = INT_MAX, cluster2_min = INT_MAX;
    float ratio1, ratio2;
    float * median_Arr = new float[nodesCnt];
    int median_Arr_size = 1;
    
    for(int i = 1; i < nodesCnt; i++)
    {
        if(nodes[i]->isInCluster == false)
        {
            median_Arr[median_Arr_size++] = eigenvector[i];
        }
    }
//    for(int i = 1; i < nodesCnt+1; i++)
//    {
//        threshold += eigenvector[i];
//    }
//    threshold /= nodesCnt;
    //threshold = eigenvector[191];
    threshold = get_median(median_Arr,median_Arr_size-1);
    
    printf("Threshold is %f .\n",threshold);
    for(int i = 1; i < nodesCnt+1; i++)
    {
        // uzel uz je v kompletnim clusteru
        if(nodes[i]->isInCluster)
            continue;
        
        if(eigenvector[i] < threshold) /*TODO*/
        {
            nodes[i]->cluster = this->nextClusterID;
            if(eigenvector[i] > cluster1_max)
                cluster1_max = eigenvector[i];
            if(eigenvector[i] < cluster1_min)
                cluster1_min = eigenvector[i];
        } else
        {
            nodes[i]->cluster = this->nextClusterID+1;
            if(eigenvector[i] > cluster2_max)
                cluster2_max = eigenvector[i];
            if(eigenvector[i] < cluster2_min)
                cluster2_min = eigenvector[i];
        }
    }
    
    
    // vypocita pomery obou clusteru
    ratio1 = getClusterRatio(cluster1_max, cluster1_min);
    ratio2 = getClusterRatio(cluster2_max, cluster2_min);
    
    //cluster, ktery ma vetsi ratio je napevno ustalen
    printf("? ratio1(%f) > ratio2(%f).\n",ratio1,ratio2);
    if(ratio1 > ratio2)
    {
        for(int i = 1; i < nodesCnt+1; i++)
        {
            if(nodes[i]->cluster == nextClusterID)
                nodes[i]->isInCluster = true;
        }
    } else
    {
        for(int i = 1; i < nodesCnt+1; i++)
        {
            if(nodes[i]->cluster == nextClusterID+1)
            {   
                /* 
                 * Aby cisla clusteru sla po sobe, je treba v tomto pripade, 
                 * ze obstoji druhy cluster jeho cislo zmensit na ukor
                 * prohravajiciho.
                 */
                nodes[i]->cluster = nextClusterID;
                nodes[i]->isInCluster = true;
            } else
            {
                if(nodes[i]->isInCluster == false)
                    nodes[i]->cluster = nextClusterID+1;
            }
        }
    }
    
    // nastaveni cisla dalsiho clusteru
    this->nextClusterID++;

    
    for(int i = 1; i < nodesCnt+1; i++)
    {
        if((i-1)%lenght1 == 0)
        {
            printf("\n");
        }
        printf("%d ",nodes[i]->cluster);
    }
           
}
void NCut::recursive_Cut(int cl){
    float threshold = 0.00;
    float * median_Arr = new float[nodesCnt];
    int median_Arr_size = 1;
    float cluster1_max = INT_MIN, cluster2_max = INT_MIN, 
            cluster1_min = INT_MAX, cluster2_min = INT_MAX;
    float ratio1, ratio2;
    float actual_clust_id;
    
    if(this->tmp_clusterCnt == clusterCnt)
        return;
    
    for(int i = 1; i < nodesCnt; i++)
    {
        if(nodes[i]->cluster == cl)
        {
            median_Arr[median_Arr_size++] = eigenvector[i];
        }
    }

    threshold = get_median(median_Arr,median_Arr_size-1);
    
    printf("Threshold is %f .\n",threshold);
    tmp_clusterCnt += 1;
    
    for(int i = 1; i < nodesCnt+1; i++)
    {      
        
        if(eigenvector[i] < threshold) /*TODO*/
        {
            if(nodes[i]->cluster == cl){
            nodes[i]->cluster = this->nextClusterID;
            if(eigenvector[i] > cluster1_max)
                cluster1_max = eigenvector[i];
            if(eigenvector[i] < cluster1_min)
                cluster1_min = eigenvector[i];
            }
        } else
        {
            if(nodes[i]->cluster == cl){
            nodes[i]->cluster = this->nextClusterID+1;
            if(eigenvector[i] > cluster2_max)
                cluster2_max = eigenvector[i];
            if(eigenvector[i] < cluster2_min)
                cluster2_min = eigenvector[i];
            }
        }
    }
    
     for(int i = 1; i < nodesCnt+1; i++)
    {
        if((i-1)%lenght1 == 0)
        {
            printf("\n");
        }
        printf("%d ",nodes[i]->cluster);
    }
    // vypocita pomery obou clusteru
    ratio1 = getClusterRatio(cluster1_max, cluster1_min);
    ratio2 = getClusterRatio(cluster2_max, cluster2_min);
    
    //cluster, ktery ma vetsi ratio je napevno ustalen
    printf("? ratio1(%f) > ratio2(%f).\n",ratio1,ratio2);
    
    actual_clust_id = this->nextClusterID;
    this->nextClusterID += 2;
    
    if(ratio1 < 0.01)
        recursive_Cut(actual_clust_id);
    
    if(ratio2 < 0.01)
        recursive_Cut(actual_clust_id+1);
}            
float k_nn(float***img,int shrinkRatio,int color ,int j, int k){                
    float value=0;
    int maxCount=0;
    std::map<float, int> m;
    std::map<float , int>::iterator it;
    for(int x=shrinkRatio*j;x<(shrinkRatio*j+shrinkRatio);x++){
        for(int y=shrinkRatio*k;y<(shrinkRatio*k+shrinkRatio);y++){
            it=m.find(img[color][x][y]);
            if(it!=m.end()){
                it->second=it->second+1;
            }else{
                m[img[color][x][y]]=1;
            }
        }
    }
    for(it = m.begin(); it != m.end(); it++) {
        if(it->second>maxCount){
            maxCount=it->second;
            value=it->first;
        }
    }
    return value;
}
float *** NCut::resizeInput(float ***img,int &lenght1, int &lenght2){
    int resizeTo=RESIZE;
    
    this->originalLenght1=lenght1;
    this->originalLenght2=lenght2;
    if(lenght1<=resizeTo) return img;
    
    lenght1=resizeTo;
    lenght2=resizeTo;
    int shrinkRatio=originalLenght1/lenght1;
    
    float *** input = new float**[3];
    for(int i=0;i<3;i++){
        input[i]=new float*[lenght1];
        for(int j=0;j<lenght1;j++){
            input[i][j]=new float[lenght2];
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<lenght1;j++){
            for(int k=0;k<lenght2;k++){
                input[i][j][k]=k_nn(img,shrinkRatio,i,j,k);
            }
        }
    }
    printf("image resized");
    return input;
}

NCut::NCut(float *** img,int lenght1, int lenght2, int clustersCnt){
    float *** input;
    input=resizeInput(img,lenght1,lenght2);
    this->clusterCnt=clustersCnt;
    nodes= new Node*[(lenght1*lenght2)+1];
    nodesCnt=0;
    for(int i=0;i<lenght1;i++){
    	for(int j = 0;j<lenght2;j++){
        	float color=RGBtoGreyLuminosity(input[0][i][j],input[1][i][j],input[2][i][j]);
                nodes[nodesCnt+1]= new Node(i+1,j+1,color);
                nodesCnt++;
                printf("%02.1f ",color);
        }
        printf("\n");
    }
    this->tmp_clusterCnt = 1;
    this->lenght1=lenght1;
    this->lenght2=lenght2;
    this->eigenvector = new float[nodesCnt+1];
    this->nextClusterID = 0;
    if(this->originalLenght1!=lenght1){
        for(int i=0;i<3;i++){
            for(int j=0;j<lenght1;j++){
                delete [] input[i][j];
            }
            delete[]input[i];
        }        
        delete[] input;
    }
}   
NCut::~NCut(){
    //TODO
        
    for(int i=0;i<nodesCnt+1;i++){
            delete [] degreeMatrix[i];
            
            if(i > 0)
                delete [] affinityMatrix[i];
    }
    
    
    for(int i = 1; i < nodesCnt+1;i++)
    {
        delete nodes[i];
    }
    
    delete [] nodes;
    delete [] affinityMatrix;
    delete [] degreeMatrix;
    delete [] eigenvector;
}
void NCut::Segmentation(){
    CreateAffinityMatrix();
    CreateDegreeMatrix();
    SimplifyEquation();
    for(int i = 0; i< clusterCnt-1; i++)
    {
        ComputeEigenVector(i);
        Cut();
    }
    //ComputeEigenVector();
    //recursive_Cut(0);
}

//TODO otestovat
int** NCut::getResult(){
    int ** result = new int*[originalLenght1];
    for(int i = 0;i<originalLenght1;i++){
        result[i]= new int[originalLenght1];
    }
    int shrinkRatio=originalLenght1/lenght1;
    int nodeCounter=1;
    for(int i=0;i<lenght1;i++){
        for(int j=0;j<lenght2;j++){
            for(int x=i*shrinkRatio;x<(i*shrinkRatio+shrinkRatio);x++){
                for(int y=j*shrinkRatio;y<(j*shrinkRatio+shrinkRatio);y++){
                    result[x][y]=nodes[nodeCounter]->cluster;
                }
            }
            nodeCounter++;
        }
    }    
    return result;
}

float NCut::getClusterRatio(float max, float min)
{
    float tmp;
    
    if(max < 0 && min > 0)
    {
        printf("Error. Probably are swaped input variables max(=%f) and"
                " min(=%f).\n",max,min);
        return (1);
    }
    
    // pripad opacnych znamenek by nemel byt v jednom clusteru
    if(max > 0 && min < 0)
        return 0.0; 
    
    //min a max jsou zaporna, vypocteme abs hodnotu a vymenime min a max
    if(max < 0.0)
    {
        tmp = fabs(max);
        max = fabs(min);
        min = tmp;
    }
    
    if(AreSameFloats(max,0.0))
    {
        printf("Error. Max is %f (Min is %f). Can't divide with zero.\n",max,
                min);
        return (1);
    }
    
    return (min/max);
}

void NCut::SetProbs(float*** probs){
    int shrinkRatio=originalLenght1/lenght1;
    for(int i=1;i<nodesCnt+1;i++){
        int x=nodes[i]->x-1;
        int y=nodes[i]->y-1;
        int clust = nodes[i]->cluster%clusterCnt;
        for(int k=x*shrinkRatio;k<(x*shrinkRatio+shrinkRatio);k++){
            for(int j=y*shrinkRatio;j<(y*shrinkRatio+shrinkRatio);j++){
               probs[clust][k][j]=1; 
               //printf("clust(%d),k(%d),j(%d)",clust,k,j);
            }
        }
    }
}