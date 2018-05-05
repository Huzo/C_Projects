
//Find out the minimum spanning tree (MST) of a graph which is stored in **AM1
//The MST will be stored in AM2.
//The output format should follow the specification


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define INFINITY    0
#define MAXNODE        26

// Pointer to the file you want to read and write.
FILE *fp;

int NumberOfNode = 0;

// Initialize the Adjacency table **AM
// In this function, you should set all elements in the Adjacency table to INFINITY
void InitAM(int **AM) {
    int i, j;
    for (i = 0; i < MAXNODE; i++) {
        for (j = 0; j < MAXNODE; j++) {
            AM[i][j] = INFINITY;
        }
    }
}


//Read the Graph from the input file to **AM
//
int ReadGraph(int **AM) {
    //open file
    fp = fopen("DataIn.txt", "r");

    if (fp == NULL) {
        printf("Unable to open file.");
        return 0;
    } else {
        int i = 0;
        // get the number of nodes of the graph
        fscanf(fp, "%d\n", &NumberOfNode);

        for (; i < NumberOfNode; i++) {
            int NodeOfLine = 0;
            int NumberOfNodesLine = 0;
            int node = 0;
            int weight = INFINITY;

            //get the current node
            fscanf(fp, "%d", &NodeOfLine);

            if (NodeOfLine == (i + 1)) {
                int j = 0;

                //get the number of nodes connected to the current node
                fscanf(fp, "%d", &NumberOfNodesLine);


                for (; j < NumberOfNodesLine; j++) {
                    //get the weight of the link
                    fscanf(fp, "%d", &node);
                    fscanf(fp, "%d", &weight);
                    AM[i][node] = weight;
                }

                fscanf(fp, "\n");

            } else {
                return 0;
            }
        }

    }

    fclose(fp);
    return 1;


}

//find the minimum spanning tree (MST) from **AM1, and store the MSP in **AM2
//
int MPS_tree(int **AM1, int **AM2) {
    int isCircle[NumberOfNode+1];
    int i, j,TMPi,TMPj,isCircle_i,isCircle_j,edgeCount = 0,MINi,MINj, minTmp = 9999;

    //isCircle array will keep track of each spanning tree's nodes' descendants.


    for(i=0;i<=NumberOfNode;i++){//initialize isCircle array;
        isCircle[i] = 0;
    }


    while(edgeCount <= NumberOfNode-1){//iterate through the adjacency matrix.
        minTmp = 9999;
        for (i = 0; i < NumberOfNode; i++) {
            for (j = 1; j <= NumberOfNode; j++) {
                if (AM1[i][j] <= minTmp && AM1[i][j] != INFINITY) {
                    //take note of the entry to further check if it would cause a circle.
                    minTmp = AM1[i][j];
                    MINi = i;
                    MINj = j;
                    isCircle_i = i+1;
                    isCircle_j = j;
                }
            }

        }

        while(isCircle[isCircle_i]){//check if there is a circle
            isCircle_i=isCircle[isCircle_i];

        }

        while(isCircle[isCircle_j]){//check if there is a circle
            isCircle_j=isCircle[isCircle_j];
        }

        if(isCircle_i!=isCircle_j) {//if the new edge doesnt cause a circle, add it.
            AM2[MINi][MINj] = minTmp;
            AM2[MINj-1][MINi+1] = minTmp;

            edgeCount++;
            if(edgeCount==NumberOfNode-1)break;

            isCircle[isCircle_j] = isCircle_i;
        }
        AM1[MINi][MINj]=9999;
        AM1[MINj-1][MINi+1]=9999;
    }


}


//print out the minimum spanning tree in **AM, as specified in Q4
//
void WriteMPS(int **AM) {
    int k, j, NumberOfNodesPrinted=0,totalWeight=0;

    printf("Source Vertex   To Vertex   Weight\n");
    while(NumberOfNodesPrinted<=NumberOfNode-1){
        if(NumberOfNodesPrinted==NumberOfNode-1)break;

        for (j = 0; j < NumberOfNode; j++) {
            if(NumberOfNodesPrinted==NumberOfNode-1)break;

            for (k = 1; k <= j; k++) {
                if(NumberOfNodesPrinted==NumberOfNode-1)break;

                if (AM[j][k] != INFINITY) {
                    printf("%d               ", j + 1);
                    printf("%d               ", k);
                    printf("%d               \n", AM[j][k]);
                    NumberOfNodesPrinted++;
                    totalWeight= totalWeight + AM[j][k];
                }
            }
        }
    }
    printf("Total weight of spanning tree: %d",totalWeight);

}

///print out the graph in **AM, for testing
// In this function, all you have to do is to print every element in the  Adjacency table **AM
//
void WriteGraph(int **AM) {
    int i, j;
    for (i = 0; i < NumberOfNode; i++) {
        for (j = 1; j <= NumberOfNode; j++) {
            printf("%d ", AM[i][j]);
        }
        printf("\n");
    }
}

int main() {
    //create two-dimensional array AM1, AM2
    //
    int **AM1 = (int **) malloc(sizeof(int *) * MAXNODE);
    int **AM2 = (int **) malloc(sizeof(int *) * MAXNODE);
    int i;
    for (i = 0; i < MAXNODE; i++) {
        AM1[i] = (int *) malloc(sizeof(int) * MAXNODE);
        AM2[i] = (int *) malloc(sizeof(int) * MAXNODE);
    }

    InitAM(AM1);
    InitAM(AM2);

    if (ReadGraph(AM1) == 0) {
        return 1;
    }
    //WriteGraph(AM1);
    printf("\n");
    if (MPS_tree(AM1, AM2) == 0) {
        printf("There is no minimum spanning tree!");
        return 1;
    }
    //WriteGraph(AM2);
    WriteMPS(AM2);

    for (i = 0; i < MAXNODE; i++) {
        free(AM1[i]);
        free(AM2[i]);
    }
    free(AM1);
    free(AM2);

    return 0;
}
