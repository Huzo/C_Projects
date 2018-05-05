/*The Bashemin Parking Garage contains a single lane that holds up to ten cars. There is 
only a single entrance/exit to the garage at one end of the lane. If a customer arrives to pick 
up a car that is not nearest the exit, all cars blocking its path are moved out, the customer’s 
car is driven out, and the other cars are restored in the same order that they were in originally. 
Write a C program that processes a group of input lines. Each input line contains an ‘A’ for 
arrival  or  a  ‘D’  for  departure,  and  a  license  
plate  number.  Cars  are  assumed  to  arrive  and  
depart  in  the  order  specified  by  the  input.  The  program  should  print  a  message  whenever  a  
car arrives or departs. When a car arrives, the message should specify whether or not there is 
room for the car in the garage. If there is no room, the car leaves without entering the garage. 
When a car departs, the message should include the number of times that the car was moved 
out of the garage to allow other cars to depart
 */
#include <stdio.h>
#include "car.h"
#include "stackar.h"
#include "fatal.h"
#include "stdlib.h"
#include <string.h>

int main() {

    char Status;
    char CarLin[7];
    //Pointer to the file you want to read and wirte.
    FILE *fp;

    //open file
    fp = fopen("DataIn.txt", "r");

    if (fp == NULL) {
        printf("Unable to open file."); //check if the file opened
    } else {
        Stack S; //Stack for Garage
        Stack T; //Stack for temp

        S = CreateStack(10);
        T = CreateStack(9);

        while (!feof(fp)) {

            //get the number of data items of L
            fscanf(fp, "%c", &Status);

            //get the number of data items of P
            fscanf(fp, "%s\n", CarLin);

            CarLin[6] = '\0';

            if ('A' == Status) //arrival
            {
                if (IsFull(S)) {//If the garage is full
                    printf("Sorry! no room.\n");
                } else {//park the car
                    Push(CreateCar(CarLin), S);
                    printf("Enter, please!\n");
                }


            }


            if ('D' == Status) //depature
            {
                struct CarNode *tmp;
                do {//move out the cars until the desired car leaves.
                    tmp = Top(S);
                    Push(TopAndPop(S), T);
                } while (strcmp(tmp->CarLicense, CarLin) != 0);
                printf("Moved %d, Bye!\n", tmp->Movement);
                Pop(T);//desired car leaves.

                while (!(IsEmpty(T))) {
                    //move back the other cars.
                    tmp = Top(T);
                    tmp->Movement++;
                    Push(TopAndPop(T), S);

                }

            }
        }
    }
    fclose(fp);
    return 0;
}
