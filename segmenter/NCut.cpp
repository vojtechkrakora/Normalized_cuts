#include "NCut.h"
#include <cmath>
#include <cstring>

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

/*
void Node::createEdges(Node * nodes){
    edges = new Edges[8];
    int myPosition=countPosition(x,y);
    int destPosition;
    double weight;

    for(int i=x-1;i<=x+1;i++){
    	if(i<0)i++;
    	if(i>lenght1)break;
    	for(int j=y-1;j<=y+1;j++){
            if(j<0)j++;
            if(j>lenght2)break;
            destPosition = countPosition(x-1,y-1);
            weight = fabs(nodes[myPosition].color - nodes[destPosition].color);
            edges[edgesCnt++] = new Edge(myPosition, destPosition,weight);
        }	
}*/


//funkce vypoctu podobnosti 2 pixelu (rozdil barvy/vzdalenosti)
double NCut::weightFunction(int x1, int y1, int x2, int y2){
    double distance = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
    double color1 = inputMatrix[x1][y1];
    double color2 = inputMatrix[x2][y2];
    return fabs(color1-color2)/distance;
}

// vytvori matici podobnosti
void NCut::CreateAffinityMatrix(){
    int size=lenght1*lenght2;
    affinityMatrix = new double*[size];
    for(int i=0;i<size;i++){
    	affinityMatrix[i] = new double[size];
    	for(int j=0;j<size;j++){
            int x1,y1,x2,y2;
            countCoords(x1,y1,i);
            countCoords(x2,y2,j);
            affinityMatrix[i][j]=weightFunction(x1,y1,x2,y2);
	}
    }
}
	
// vytvori degree matici
void NCut::CreateDegreeMatrix(){
    int size=lenght1*lenght2;
    degreeMatrix = new double*[size];
    for(int i=0;i<size;i++){
	degreeMatrix[i] = new double[size];
	memset(affinityMatrix[i],0,size);	
    }
    for(int item=0;item<size;item++){
    	int x1,y1;
	countCoords(x1,y1,item);
	for(int i=0;i<size;i++){
            if(i==item)continue; // hadam ze se nema zapocitavat on sam
            int x2,y2;
            countCoords(x2,y2,item);
            degreeMatrix[item][item]+=weightFunction(x1,y1,x2,y2);
	}
    }
}

// vypocita vlastni cislo (2nd)
void NCut::ComputeEigenValue(){
    int size=lenght1*lenght2;
    double ** dSubAMatrix=new double*[size]; // (D-A)
    for(int i=0;i<size;i++){
	dSubAMatrix[i]=new double[size];
    }
    for(int i=0;i<size;i++){
	for(int j=0;j<size;j++){
            dSubAMatrix[i][j]=degreeMatrix[i][j] - affinityMatrix[i][j];
	}
    }
	
}
// vypocita vlastni vektor
void NCut::ComputeEigenVector(){

}
//provede rez
void NCut::Cut(){

}

NCut::NCut(double *** input,int lenght1, int lenght2, int lenght3,int clustersCnt){
    this->inputMatrix=new double*[lenght1];
    for(int i=0;i<lenght1;i++){
    	inputMatrix[i]=new double[lenght2];
    	for(int j = 0;j<lenght2;j++){
        	inputMatrix[i][j]=RGBtoGrey(input[i][j][0],input[i][j][1],input[i][j][2]);
	}
    }
    this->lenght1=lenght1;
    this->lenght2=lenght2;
    
    /*int size=lenght1*lenght2;	
    nodes = new Nodes[size];
    int index=0;
    for(int i=0;i<lenght1;i++){
    	for(int j=0;j<lenght2;j++){
    		nodes[index++]=new Node(i,j,(input[i][j][0]+input[i][j][1]+input[i][j][2])/3.0);
    	}
    }
    for(int i=0;i<size;i++){
    	nodes[i]=createEdges(nodes);
    }*/
}   
void NCut::Segmentation(){

}

int** NCut::getResult(){

    return 0;
}
