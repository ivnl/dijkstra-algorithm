#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>

using namespace std;
ifstream in_data1;
ofstream out_data1;
ofstream out_data2;

class DijkstraSSS {

public:

    int numNodes, sourceNode, minNode, currentNode, newCost;
    int** costMatrix;
    int * fatherAry;
    int * markedAry;
    int * bestCostAry;

    DijkstraSSS(ifstream& data) {

        //rotate through all source nodes

        data>>numNodes; //store first int
        cout<<numNodes;

        int temp = 0;
        loadCostMatrix(data);

        sourceNode = 1;
        loadBestCostAry(sourceNode);


    }

    //Print out cost matrix for debugging
    void testPrint() {
        int count = 1;
        cout<<endl<<endl;
        cout<<"      1    2    3    4    5    6    7    8";
        for(int i=0; i<numNodes; i++) {
            cout<<endl<<endl;
            cout<<i+1<<"  ";
            for(int k=0; k<numNodes; k++) {
                cout<<setw(4)<<costMatrix[i][k]<<" ";
            }
        }
        cout<<endl<<endl;
    }

    void loadCostMatrix(ifstream& data) {

        int row = 0;
        int col = 0;
        int cost = 0;

        costMatrix = new int*[numNodes]();

        for(int i = 0; i < numNodes; ++i)  {
            costMatrix[i] = new int[numNodes];

            for(int k=0;k<numNodes; ++k) {

                costMatrix[i][k]= 9999;
                costMatrix[i][i] = 0;


            }

        }

        while(!data.eof()) {

            data>>row;
            data>>col;
            data>>cost;

            cout<<"\nrow "<<row<<" col "<<col<<" cost "<<cost;
            costMatrix[row-1][col-1] = cost;

        }
    }

    void loadBestCostAry(int sourceNode) {

        bestCostAry= new int[numNodes];

            for(int k=0;k<numNodes;k++) {
                bestCostAry[k] = costMatrix[sourceNode][k];
            }

        }
        //- loadBestCostAry (sourceNode) // copy the row of source node from costMatrix,


    void loadFatherAry (int sourceNode) {

        fatherAry = new int[numNodes];
        for(int i=0;i<numNodes;i++) {
            fatherAry[i] = sourceNode;
        }

    }

    void loadMarkedAry() {

        markedAry = new int[numNodes];
        for(int i=0;i<numNodes;i++) {
            markedAry[i] = 0;
        }
        //    - loadMarkedAry ( ) // set all to 0,

    }

    void computeCost (int minNode, int currentNode) { //the fuck

        bestCostAry[minNode] + costMatrix[minNode][currentNode];
        //    - computeCost (minNode, currentNode) method,
        //it compute the currentNode’s cost ( bestCostArray[minNode] +  cost from minNode to currentNode, in costMatrix)

    }

    void markMinNode (int minNode) {

        markedAry[minNode] = 1;
        //    - markMinNode (minNode) // mark the minNode  in markedAry

    }

    void changeFather ( int node, int minNode) {

        fatherAry[node] = minNode;
        //    - changeFather (node, minNode) // set node’s father be minNode in fatherAry

    }

    void changeCost( int node, int newCost) {

        bestCostAry[node] = newCost;

    }

    void Dijkstra() {

        //    - Dijkstras’ method // the Dijkstra’s algorithm

    }


//    - debugPrint method, this method
//    Print sourceNode to output-2 (with proper heading, ie., the sourceNode is: )
//    Print fatherAry to output-2 (with proper heading)
//    Print bestCostAry to output-2 (with proper heading)
//    Print markedAry to output-2 (with proper heading)
//    - printShorestPaths (sourceNode)


};

int main(int argc, char *argv[]) {
    in_data1.open(argv[1]);
    out_data1.open(argv[2]);
    out_data2.open(argv[3]);

    DijkstraSSS dij(in_data1);
    dij.testPrint();



    cout << "\nHello, World!" << endl;
    return 0;

};