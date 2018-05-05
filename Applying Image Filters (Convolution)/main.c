#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct {
    char fileName[199];
    FILE *file;
    char magicNum[199];
    int width;
    int height;
    int MaxGrayVal;
    int matrix[129][128];
}File;

typedef struct{
    char fileName[199];
    FILE *file;
    int N;
    double matrix[9][9];
}FilterFile;

void printMatrix(double matrix[9][9], int N) //print ant NxN matrix
{
    int col,row;

    printf("/");
    for (col = 0; col < N; col++){
        printf("        ");
    }
    printf(" \\\n");
    for(row = 0; row< N; row++){
        printf("|");
        for(col = 0; col<N; col++){
            printf(" %+7.2f",matrix[row][col]);
        }printf(" |\n");
    }

    printf("\\");
    for (col = 0; col < N; col++){
        printf("        ");
    }
    printf(" /\n");
}

void convolution(int A[128][128], double B[9][9], int row, int col, int N,int maxGray){
    int i,j,k,l;
    int X = row-N+1, Y = col-N+1;
    double newMat[X][Y];//matrix to store filtered values.

    for(i = 0; i < X; i++){ //initialize newMat matrix elements to 0.
        for(j = 0; j < Y; j++){
            newMat[i][j] = 0;
        }
    }


    FILE *fptr;

    if(!(fptr = fopen("output.pgm","w"))){ //return an error if the program is unable to open file.
        printf("Error writing PGM file [output.pgm]");
        return;
    }

    fprintf(fptr,"P2\n%d %d\n%d\n",Y,X,maxGray);//PGM format definition
    for(i = 0; i < X; i++){// i and j is for scanning the unfiltered sub-sets
        for(j = 0; j < Y; j++){
            for(k = 0; k < N; k++){// k and l is for iterating through each pair before multiplying
                for(l = 0; l < N; l++){
                    newMat[i][j] = newMat[i][j] + (B[k][l] * A[i+k][j+l]);
                }
            }

            if(newMat[i][j] < 0){
                newMat[i][j] = 0;
            }
            if(newMat[i][j] > 255){
                newMat[i][j] = 255;
            }
        }
    }

    for(i = 0; i < X; i++){//print filtered values to the PGM file.
        for(j = 0; j < Y; j++){
            fprintf(fptr,"%d ",(int)newMat[i][j]);
        }
        fprintf(fptr,"\n");
    }
    fclose(fptr);
    return;
}

int main()
{
    int i,j;

    printf("Math Tool Box\n");
    printf("/\\/\\/\\/\\/\\/\\/\n");
    printf("Phase 3B\n");

    File Image;
    FilterFile Filter;

    printf("Image filename: ");
    scanf("%s",&Image.fileName);//user input of unfiltered image file's name.

    if(!(Image.file = fopen(Image.fileName,"r"))){//return an error if there is a problem with opening the file.
        printf("Error reading PGM file [%s]",Image.fileName);
        return 0;
    }

    fscanf(Image.file, "%s\n%d %d\n%d\n",&Image.magicNum,&Image.width,&Image.height,&Image.MaxGrayVal);//scan for contents that should be included in a PGM file.

    if((Image.file == NULL)||(!isascii(Image.width))||(!isascii(Image.height))||(Image.MaxGrayVal <= 0) || (Image.MaxGrayVal >= 65536) ){//else, return an error.
        printf("Error reading PGM file [%s]",Image.fileName);
        return 0;
    }

    for(i = 0; i < Image.height; i++){//scan the unfiltered image pixel values from the file.
        for(j = 0; j < Image.width; j++){
            fscanf(Image.file,"%d ",&Image.matrix[i][j]);
        }
    }
    fclose(Image.file);//close




    printf("Filter filename: ");
    scanf("%s",&Filter.fileName);//user input of the filter file's name

    if(!(Filter.file = fopen(Filter.fileName,"r"))){//return an error if there is a problem with the opening of the file.
        printf("Error reading filter file [%s]",Filter.fileName);
        return 0;
    }
    fscanf(Filter.file, "%d\n",&Filter.N);//scan for the size of the matrix

    for(i = 0; i < Filter.N; i++){//scan the filter data and store in a matrix
        for(j = 0; j < Filter.N; j++){
            fscanf(Filter.file,"%lf.1 ",&Filter.matrix[i][j]);
        }
    }

    if((Filter.N == 0)||(Filter.file == NULL)){//return an error if an error is encountered.
        printf("Error reading filter file [%s]",Filter.fileName);
        return 0;
    }

    fclose(Filter.file);//close the file.
    printMatrix(Filter.matrix,Filter.N);//print the filter matrix.


    convolution(Image.matrix,Filter.matrix,Image.height,Image.width,Filter.N,Image.MaxGrayVal);//apply 2D matrix convolution.



    return 0;
}
