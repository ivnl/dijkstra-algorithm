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

        //STEP 1// Load Cost Matrix from Input File
        loadCostMatrix(data);
        sourceNode = 1;  //Begin source node at 1

        //STEP 9-10// Repeat algorithm for each source node to find all best paths
        while(sourceNode<=numNodes) {
            Dijkstra(sourceNode);
            sourceNode++;
        }

    }

    //DESTRUCTOR
    ~DijkstraSSS() {
        for(int k = 0; k < numNodes; k++) {
            delete [] costMatrix[k];
        }
        delete [] costMatrix;
        delete [] fatherAry;
        delete [] bestCostAry;
        delete [] markedAry;
    }

    void Dijkstra(int sourceNode) {

        //STEP 2// Load arrays with incoming sourceNode
        loadBestCostAry(sourceNode);
        loadFatherAry(sourceNode);
        loadMarkedAry();
        debugPrint();

        //STEP 3-6// Repeat until all nodes are marked, Dijkstras Algorithm
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

        //STEP 7-8// Print shortest paths from currentNode to sourceNode in reverse
        currentNode = 0;
        cout<<endl;
        while(currentNode<numNodes) {
            printShortestPath(currentNode);

            //recursive method to print node links
            cout<<endl<<currentNode+1;
            printsp(currentNode);
            cout<<endl;

            out_data1<<endl;
            currentNode++;
        }
        out_data1<<endl;
    }

        void printsp(int node) {

            if(fatherAry[node]==sourceNode-1) {
                cout<<" <-- "<<fatherAry[node]+1;
                return;
            }
            else {
                cout<<" <-- "<<fatherAry[node]+1;
                return (printsp(fatherAry[node]));
            }

        }

        void printShortestPath(int node) {
            //TEMP INT TO HOLD ORIGINAL VALUE OF fatherAry[node], in order to iterate through all nums
            int temp = fatherAry[node];
            out_data1<<"Shortest Path from "<<sourceNode<< " to "<<node+1<<":   ";
            out_data1 << node + 1 << " <-- ";
            //While father of node does not equal sourcenode, modify father = 'grandfather' and check again
            while (fatherAry[node] != sourceNode - 1) {
                out_data1 << fatherAry[node] + 1 << " <-- ";
                fatherAry[node] = fatherAry[fatherAry[node]];
            }
            out_data1 << sourceNode << " |COST: "<< bestCostAry[node]<<"|";

            //RESTORE ORIGINAL VALUE FOR NEXT ITERATION
            fatherAry[node]=temp;

        }

        //Function to check if all 'nodes' in markedAry are marked
        bool allMarked(){
            for(int i = 0; i<numNodes; i++){
                if(markedAry[i] == 0)
                    return false;
            }
            return true;
        }

        //Function to find smallest, unmarked index remaining
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

            out_data2<<"sourceNode is: "<<sourceNode;
            out_data2<<endl<<"Father Array: ";
            printAry(fatherAry);
            out_data2<<endl<<"Best Cost Array: ";
            printAry(bestCostAry);
            out_data2<<endl<<"Marked Array: ";
            printAry(markedAry);
            out_data2<<endl<<endl;

        }

        void matrixPrint() {
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
            for(int i=0;i<numNodes;i++) {
                out_data2<<ary[i]<<" ";
            }
        }

        void loadCostMatrix(ifstream& data) {

            int row = 0,col = 0,cost = 0;

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

    //- loadBestCostAry (sourceNode) // copy the row of source node from costMatrix,
    void loadBestCostAry(int sourceNode) {

            bestCostAry= new int[numNodes];

            for(int k=0;k<numNodes;k++) {
                bestCostAry[k] = costMatrix[sourceNode-1][k];
            }

        }

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
        }

        int computeCost (int minNode, int currentNode) {

            //    - computeCost (minNode, currentNode) method,
            //it compute the currentNode’s cost
            // ( bestCostArray[minNode] +  cost from minNode to currentNode, in costMatrix)
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

    };

    int main(int argc, char *argv[]) {

        if(argc<4) {
            cout<<"Insufficient arguments passed. (argv1:input,argv2:output1,argv2:output2";
        }

        in_data1.open(argv[1]);
        out_data1.open(argv[2]);
        out_data2.open(argv[3]);

        DijkstraSSS dij(in_data1);

        in_data1.close();
        out_data1.close();
        out_data2.close();

        return 0;
    };