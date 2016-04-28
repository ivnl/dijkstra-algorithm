#include <iostream>
#include <fstream>
#include <iomanip>


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

        data >> numNodes; //store first int
        cout << "Number of Nodes: " << numNodes;

        //STEP 1//
        loadCostMatrix(data);
        sourceNode = 1;  //Begin source node at 1

        //STEP 9-10//
        while(sourceNode<=numNodes) {
            cout<<endl<<endl<<"Source Node: "<<sourceNode<<endl<<endl;
            Dijkstra(sourceNode);
            sourceNode++;
        }


    }

        void printShortestPath(int node) {
            //TEMP INT TO HOLD ORIGINAL VALUE OF fatherAry[node], in order to iterate through all nums
            int temp = fatherAry[node];

            cout << node + 1 << " <-- ";
            while (fatherAry[node] != sourceNode - 1) {
                cout << fatherAry[node] + 1 << " <-- ";
                fatherAry[node] = fatherAry[fatherAry[node]];
            }
            cout << sourceNode << endl;

            //RESTORE ORIGINAL VALUE FOR NEXT ITERATION
            fatherAry[node]=temp;

        }


        bool allMarked(){
            for(int i = 0; i<numNodes; i++){
                if(markedAry[i] == 0)
                    return false;
            }
            return true;
        }

        int findMin() {
            int minVal = 9999;
            int minIndex = 0;
            for(int i =0;i<numNodes;i++) {
                if(bestCostAry[i]<minVal && markedAry[i]!=1) {
                    minVal = bestCostAry[i];
                    minIndex = i;
                }
            }
            return minIndex;
        }

        void debugPrint() {

            cout<<endl<<endl<<"Father Array:";
            printAry(fatherAry);
            cout<<endl<<endl<<"Best Cost Array:";
            printAry(bestCostAry);
            cout<<endl<<endl<<"Marked Array:";
            printAry(markedAry);

            //    - debugPrint method, this method
            //    Print sourceNode to output-2 (with proper heading, ie., the sourceNode is: )
            //    Print fatherAry to output-2 (with proper heading)
            //    Print bestCostAry to output-2 (with proper heading)
            //    Print markedAry to output-2 (with proper heading)
            //    - printShorestPaths (sourceNode)

        }

        void testPrint() {
            cout<<endl<<endl<<"      1    2    3    4    5    6    7    8";
            for(int i=0; i<numNodes; i++) {
                cout<<endl<<endl<<i+1<<"  ";
                for(int k=0; k<numNodes; k++) {
                    cout<<setw(4)<<costMatrix[i][k]<<" ";
                }
            }
            cout<<endl<<endl;
        }

        void printAry(int ary[]) {
            cout<<endl;
            for(int i=0;i<numNodes;i++) {
                cout<<ary[i]<<" ";
            }
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
                costMatrix[row-1][col-1] = cost;

            }
        }

        void loadBestCostAry(int sourceNode) {

            bestCostAry= new int[numNodes];

            for(int k=0;k<numNodes;k++) {
                bestCostAry[k] = costMatrix[sourceNode-1][k];
            }

        }
        //- loadBestCostAry (sourceNode) // copy the row of source node from costMatrix,


        void loadFatherAry (int sourceNode) {

            fatherAry = new int[numNodes];
            for(int i=0;i<numNodes;i++) {
                fatherAry[i] = sourceNode-1;
            }
        }

        void loadMarkedAry() {

            markedAry = new int[numNodes];
            for(int i=0;i<numNodes;i++) {
                markedAry[i] = 0;
            }
            //    - loadMarkedAry ( ) // set all to 0,

        }

        int computeCost (int minNode, int currentNode) { //the fuck

            //    - computeCost (minNode, currentNode) method,
            //it compute the currentNode’s cost ( bestCostArray[minNode] +  cost from minNode to currentNode, in costMatrix)
            return bestCostAry[minNode] + costMatrix[minNode][currentNode];
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

        void Dijkstra(int sourceNode) {

            //STEP 2//
            loadBestCostAry(sourceNode);
            loadFatherAry(sourceNode);
            loadMarkedAry();

            debugPrint();

            //STEP 3-6//
            markMinNode(sourceNode-1);
            while(!allMarked()) {

                minNode = findMin();
                markMinNode(minNode);

                debugPrint();

                for (int k = 0; k < numNodes; k++) {
                    if (markedAry[k] == 0) { currentNode = k; }
                    newCost = computeCost(minNode, currentNode);

                    if (newCost < bestCostAry[currentNode]) {
                        changeFather(currentNode, minNode);
                        changeCost(currentNode, newCost);
                        debugPrint();
                    }

                }
            }
            cout<<endl<<endl;

            //STEP 7-8//
            currentNode = 0;
            while(currentNode<numNodes) {
                printShortestPath(currentNode);
                currentNode++;
            }
        }

    };

    int main(int argc, char *argv[]) {
        in_data1.open(argv[1]);
        out_data1.open(argv[2]);
        out_data2.open(argv[3]);

        DijkstraSSS dij(in_data1);

        return 0;
    };