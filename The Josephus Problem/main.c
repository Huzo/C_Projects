/* The 
Josephus problem is the following game: N people, numbered 1 to N, are sitting 
in a circle. Starting at person 1, a hot potato is passed. After M passes, the person holding 
the  hot  potato  is  eliminated,  the  circle  closes  ranks,  and  the  game  continues  with  the  
person  who  was  sitting  after  the  eliminated person  picking  up  the  hot  potato.  The  last 2
remaining  person  wins.  Thus,  if  M=0  and  N=5,  players  are  eliminated  in  order,  and  
player 5 wins. If M=1 and N=5, the order of elimination is 2, 4, 1, 5 and winner is 3. 

Write a C program to solve the Josephus problem for general values of M and N. 
Try to make your program as efficient as possible. Make sure you disclose of cells eliminated
*/

#include <stdio.h>
#include <stdlib.h>

int N, M;//global variables

typedef struct Node { //node structure
    int value;
    struct Node *next;
    struct Node *previous;
} node;

void createList(int n, node **head) {
    struct Node *tmp = *head;//tmp variable to iterate through the list

    int i;

    for (i = 1; i <= n; i++) {
        if (tmp == NULL) {
            //create the head node if there are no
            //other nodes in the linked list.
            struct Node *node = malloc(sizeof(*node));
            node->previous = NULL;
            node->next = NULL;
            node->value = i;

            *head = node;
            tmp = node;

        } else {
            //if there are nodes in the list, append
            //at the end of the linked list.
            struct Node *node = malloc(sizeof(*node));
            node->previous = tmp;
            node->next = NULL;
            node->value = i;

            tmp->next = node;
            tmp = tmp->next;
        }

    }
    //link the head with the tail to create a circular linked list.
    tmp->next = *head;
    (*head)->previous = tmp;


}

void deleteNode(node *nd) { //function to delete node
    //link the previous node to the next node.
    //And delete the desired node
    nd->previous->next = nd->next;
    nd->next->previous = nd->previous;
    N--;
    free(nd);
}


int main() {

    node *head = malloc(sizeof(*head));
    head = NULL;


    printf("Input N and M: ");
    scanf("%d %d", &N, &M);
    createList(N, &head);



    //create a temporary pointer node called tmp
    node *tmp;
    node *tmp2;
    tmp = head;

    int i;

    //eliminate nodes and print them.
    printf("Order of elimination: ");
    //loop until one winner is left
    while (N > 1) {
        for (i = 1; i <= M; i++) {
            //loop to pass the potato to the next one
            tmp = tmp->next;
        }
        printf("%d ", tmp->value);
	tmp2 = tmp->next
        deleteNode(tmp->next->previous);//delete and eliminate the target
        tmp = tmp2;//start the potato from the next one
    }
    printf("\nThe winner is: %d\n", tmp->value);
    free(tmp);
    free(tmp2);

}
