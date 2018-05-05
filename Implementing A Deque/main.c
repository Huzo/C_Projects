/*A  
deque is  a  data  structure  consisting  of  a  list  of  items,  on  which  the  following  
operations are possible: 
Push(X,D):  Insert item X on the front end of 
deque D. 
Pop(D):  Remove the front item from 
deque D and return it. 
Inject(X,D):  Insert item X on the rear end of 
deque D. 
Eject(D):  Remove the rear item from 
deque D and return it. 
Write  routines  to  support  the  
deque 
that  take  O(1)  time  per  operation.  Your  main  program      
will print out the items in 
deque after each operation. 
Deque can have at most 30 items. */


#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *next;
    struct Node *prev;
}node;

typedef struct {
    node *front;
    node *rear;
}deque;

void Push(int x, deque * dq){
    //Insert item x on the front end of deque
    node * tmp = (node*)malloc(sizeof(node));
    tmp->data = x;
    if(dq->front == NULL || dq->rear == NULL){//if the deque is empty
        dq->front = tmp;
        dq->rear = tmp;
    }
    else {
        dq->front->next = tmp;
        tmp->prev = dq->front;
        dq->front = tmp;
    }
}

int Pop(deque *dq) {
    //Remove the front item from deque and return it.
    if (dq->front == NULL || dq->rear == NULL) {//if the deque is empty
        return NULL;
    }
    else if(dq->front == dq->rear){//if the deque has only one item
        node * tmp = dq->front;
        int x = tmp->data;
        free(tmp);
        dq->rear = NULL;
        dq->front = NULL;
        return x;
    }
    else {
        node *tmp = dq->front;
        int x = tmp->data;
        dq->front = tmp->prev;
        free(tmp);
        if (dq->front->prev == NULL) {//if only one element exists in deque after popping
            dq->rear = dq->front;
        }
        return x;
    }


}

void Inject(int x, deque *dq){
    //Insert item x on the rear end of deque.
    node *tmp = (node*)malloc(sizeof(node));
    tmp->data = x;
    if(dq->rear == NULL || dq->front == NULL){//if the deque is empty
        dq->rear = tmp;
        dq->front = tmp;
    }
    else{
        tmp->next = dq->rear;
        dq->rear->prev = tmp;
        dq->rear = tmp;
    }

}

int Eject(deque *dq){
    //Remove the rear item from deque and return it.
    if(dq->front == NULL || dq->rear == NULL){//if the deque is empty
        return NULL;
    }
    else if(dq->front == dq->rear){//if the deque has only one item
        node * tmp = dq->rear;
        int x =tmp->data;
        free(tmp);
        dq->rear = NULL;
        dq->front = NULL;
        return x;
    }
    else{
        node * tmp = dq->rear;
        int x = tmp->data;
        dq->rear = dq->rear->next;
        dq->rear->prev=NULL;
        free(tmp);
        return x;
    }
}


void printDeque(deque *dq){
    //Print items in deque;
    if(dq->front == NULL || dq->rear ==NULL){
        printf("\nList is empty");
    }
    else {
        node *tmp = dq->front;
        while (tmp != NULL) {
            printf("%d ", tmp->data);
            tmp = tmp->prev;
        }
        free(tmp);
    }
}

int main() {
    deque * myq = (deque*)malloc(sizeof(deque));
    myq->rear = NULL;
    myq->front = NULL;
    int N=3;
    int switch_,data;
    printf("Input the number of operations: ");
    scanf("%d",&N);
    if(N>30){
        printf("\nDeque can have at most 30 items");
        return 0;
    }

    while(N){
        printf("\n\n1 - Push,   2 - Pop,   3 -Inject,   4 - Eject\nEnter an operation and a value if applicable: ");
        scanf("%d",&switch_);
        switch(switch_){
            case 1:
                scanf(" %d",&data);
                Push(data,myq);
                printf("Push: ");
                printDeque(myq);
                break;
            case 2:
                Pop(myq);
                printf("Pop: ");
                printDeque(myq);
                break;
            case 3:
                scanf(" %d",&data);
                Inject(data,myq);
                printf("Inject: ");
                printDeque(myq);
                break;
            case 4:
                Eject(myq);
                printf("Eject: ");
                printDeque(myq);
                break;
            default:
                printf("Wrong entry");
        }
        N--;

    }

    return 0;
}
