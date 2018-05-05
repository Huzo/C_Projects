/*The linked list, L, and linked list, P, contain integers sorted in ascending order. The operation 
PrintLots(L,P) will print the elements in L that are in positions specified by P. 
For instance, if P = 1, 3, 4, 6, the first, third, fourth, and sixth elements in L are printed. 
Write  the  procedure  PrintLots(L,P). You  should  use  only  the  basic  list  operations  you  
define. */

#include <stdio.h>
#include "list.h"

// Pointer to the file you want to read and write.
FILE *fp;

void PrintLots(List L, List P){
    //Point to the first element of both lists
    Position Pt1 = First(L);
    Position Pt2 = First(P);

    while(Pt2){
        int i;
        //Get the current element of P and iterate in List L
        //according to the element size.
        for(i = 1; i < Retrieve(Pt2); i++){
            Pt1 = Advance(Pt1);
        }
        printf("%d ",Retrieve(Pt1));//Print the element that we need

        Pt1 = First(L);//Point back to the first element of L
        Pt2 = Advance(Pt2);//Go to the next element of P
    };

}


// Print the list
void
PrintList( const List L )
{
    Position P = Header( L );

    if( IsEmpty( L ) )
        printf( "PrintEmpty\n" );
    else
    {
        do
        {
            P = Advance( P );
            printf( "%d ", Retrieve( P ) );
        } while( !IsLast( P, L ) );
        printf( "\n" );
    }
}



//to read list
void ReadList( List L, int size )
{
    //start;
    int i =0;
    Position Pt = Header( L );

    while (i<size)
    {
        int tempC;
        fscanf(fp, "%d", &tempC);
        Insert(tempC,L,Pt);
        Pt = Advance(Pt);
        //printf("%d\n",tempC);
        i++;
    }

}



int main(){
    //size of the list
    int size1 = 0, size2 = 0;

    //Linked list
    List L;
    List P;

    L = MakeEmpty(NULL);
    P = MakeEmpty(NULL);

    //open file
    fp = fopen("DataIn.txt","r");
    if(fp == NULL)
        printf("Unable to open file.");//check if the file opened
    else{
        // get the number of data items of L
        fscanf(fp,"%d",&size1);

        // get the number of data items of P
        fscanf(fp,"%d",&size2);

        if(size1<size2){
            printf("Error in the sequence size!");//check if the file opened
        }
        else{
            ReadList(L,size1);
            ReadList(P,size2);

            PrintList(L);
            PrintList(P);

            // Print the list L based on P
            PrintLots(L,P);
        }
    }
    fclose(fp);
    DeleteList(L);
    DeleteList(P);
    return 0;
}
