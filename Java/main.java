import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.*;

class DijkstraSSS {

    int numNodes, sourceNode, minNode, currentNode, newCost;
    int[][] costMatrix;
    int[] fatherAry;
    int[] markedAry;
    int[] bestCostAry;
    Scanner read;

    DijkstraSSS(File data) {

        try {
            read = new Scanner(data);
            numNodes = read.nextInt();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        System.out.println("Number of Nodes: " + numNodes);

        //STEP 1// Load Cost Matrix from Input File
        loadCostMatrix(data);
        sourceNode = 1;  //Begin source node at 1

        //STEP 9-10// Repeat algorithm for each source node to find all best paths
        while (sourceNode <= numNodes) {
            Dijkstra(sourceNode);
            sourceNode++;
        }

    }

    void Dijkstra(int sourceNode) {

        //STEP 2// Load arrays with incoming sourceNode
        loadBestCostAry(sourceNode);
        loadFatherAry(sourceNode);
        loadMarkedAry();
        debugPrint();

        //STEP 3-6// Repeat until all nodes are marked, Dijkstras Algorithm
        markMinNode(sourceNode - 1);
        while (!allMarked()) {

            minNode = findMin();
            markMinNode(minNode);
            debugPrint();

            for (int k = 0; k < numNodes; k++) {
                if (markedAry[k] == 0) {
                    currentNode = k;
                }
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
        while (currentNode < numNodes) {
            printShortestPath(currentNode);
            //recursive method to print node links
            //System.out.println(currentNode+1);
            //printsp(currentNode);
            //System.out.println();

            main.out1.print("\n");
            currentNode++;
        }

        main.out1.print("\n");
    }

    void printsp(int node) {

        if (fatherAry[node] == sourceNode - 1) {
            // cout<<" <-- "<<fatherAry[node]+1;
            return;
        } else {
            //cout<<" <-- "<<fatherAry[node]+1;
            //return (printsp(fatherAry[node]));
        }

    }

    void printShortestPath(int node) {
        //TEMP INT TO HOLD ORIGINAL VALUE OF fatherAry[node], in order to iterate through all nums
        int temp = fatherAry[node];
        main.out1.print("Shortest Path from " + sourceNode + " to " + node + 1 + ":  ");
        main.out1.print(node + 1 + " <-- ");
        //While father of node does not equal sourcenode, modify father = 'grandfather' and check again
        while (fatherAry[node] != sourceNode - 1) {
            main.out1.print(fatherAry[node] + 1 + " <-- ");
            fatherAry[node] = fatherAry[fatherAry[node]];
        }
        main.out1.print(sourceNode + " |COST: " + bestCostAry[node] + "|");
        //RESTORE ORIGINAL VALUE FOR NEXT ITERATION
        fatherAry[node] = temp;

    }

    //Function to check if all 'nodes' in markedAry are marked
    boolean allMarked() {
        for (int i = 0; i < numNodes; i++) {
            if (markedAry[i] == 0)
                return false;
        }
        return true;
    }

    //Function to find smallest, unmarked index remaining
    int findMin() {
        int minVal = 9999;
        int minIndex = 0;
        for (int i = 0; i < numNodes; i++) {
            if (bestCostAry[i] < minVal && markedAry[i] != 1) {
                minVal = bestCostAry[i];
                minIndex = i;
            }
        }
        return minIndex;
    }

    void debugPrint() {
        main.out2.print("sourceNode is: " + sourceNode);
        main.out2.print("\nFather Array: ");
        printAry(fatherAry);
        main.out2.print("\nBest Cost Array: ");
        printAry(bestCostAry);
        main.out2.print("\nMarked Array: ");
        printAry(markedAry);
        main.out2.print("\n\n");
    }

//    void matrixPrint() {
//        cout<<endl<<endl<<"      1    2    3    4    5    6    7    8";
//        for(int i=0; i<numNodes; i++) {
//            cout<<endl<<endl<<i+1<<"  ";
//            for(int k=0; k<numNodes; k++) {
//                cout<<setw(4)<<costMatrix[i][k]<<" ";
//            }
//        }
//        cout<<endl<<endl;
//    }

    void printAry(int ary[]) {
        for (int i = 0; i < numNodes; i++) {
            main.out2.print(ary[i] + " ");
        }
    }

    void loadCostMatrix(File data) {

        int row = 0, col = 0, cost = 0;

        costMatrix = new int[numNodes][numNodes];

        for (int i = 0; i < numNodes; ++i) {
            costMatrix[i] = new int[numNodes];

            for (int k = 0; k < numNodes; ++k) {
                costMatrix[i][k] = 9999;
                costMatrix[i][i] = 0;
            }
        }
        while (read.hasNext()) {

            row = read.nextInt();
            col = read.nextInt();
            cost = read.nextInt();

            costMatrix[row - 1][col - 1] = cost;

        }
    }

    //- loadBestCostAry (sourceNode) // copy the row of source node from costMatrix,
    void loadBestCostAry(int sourceNode) {

        bestCostAry = new int[numNodes];

        for (int k = 0; k < numNodes; k++) {
            bestCostAry[k] = costMatrix[sourceNode - 1][k];
        }

    }

    void loadFatherAry(int sourceNode) {
        fatherAry = new int[numNodes];
        for (int i = 0; i < numNodes; i++) {
            fatherAry[i] = sourceNode - 1;
        }
    }

    void loadMarkedAry() {
        markedAry = new int[numNodes];
        for (int i = 0; i < numNodes; i++) {
            markedAry[i] = 0;
        }
    }

    int computeCost(int minNode, int currentNode) {
        return bestCostAry[minNode] + costMatrix[minNode][currentNode];
    }

    void markMinNode(int minNode) {
        markedAry[minNode] = 1;
        //    - markMinNode (minNode) // mark the minNode  in markedAry

    }

    void changeFather(int node, int minNode) {
        fatherAry[node] = minNode;
        //    - changeFather (node, minNode) // set node’s father be minNode in fatherAry

    }

    void changeCost(int node, int newCost) {
        bestCostAry[node] = newCost;

    }

};

public class main {

    public static PrintWriter out1;
    public static PrintWriter out2;

    public static void main(String[] args) throws Exception {

        if (args.length < 2) {
            throw new FileNotFoundException("Insufficient Arguments Passed");
        }

        File in1 = new File(args[0]);
        out1 = new PrintWriter(args[1]);
        out2 = new PrintWriter(args[2]);

        DijkstraSSS dij = new DijkstraSSS(in1);

        out1.close();
        out2.close();
    }
}