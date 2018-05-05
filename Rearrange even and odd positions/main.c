#include <stdio.h>
#include <stdlib.h>

/* Given  a  list  of  integers,  write  a  C  function,  similar  to  the  partition  process  in
QuickSort, that will rearrange the integers so that either all the integers in even-
numbered  positions  will  be  even  or  all  the  integers  in  odd-numbered  positions
will  be  odd.  (Your  function  will  provide  a  proof  that  one  or  the  other  of  these
goals can always be attained, although it may not be possible to establish both at
once.) Your main program will read a set of values from DataIn file, and print out
the list after reordering them as the above.
*Note:  sample data input in DataIn file for Q4
11
3 1 4 5 9 6 8 0 7 13 16 */


void printList(int data[], int inpsize) {//function to print the list of numbers.
    int i;
    for (i = 0; i < inpsize; i++) {
        printf("%d ", data[i]);
    }
}

void swap(int *a, int *b) {//function to swap the place of two entries.
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void oddPartition(int data[], int high) {
    //in this algorithm "low" index iterates through odd indexes;
    // and "high" indexes iterates through even indexes
    int l = 0;//l checks odd indexes
    int h = high;//h checks even indexes

    if (h % 2 == 0) {//check and make sure that our "high" index is at an even index.
        h = h - 1;
    }


    while (l < high && h > 0) {
        if (data[l] % 2 == 1) {//if our odd checker finds odd, move index.
            l = l + 2;
        }
        if (data[h] % 2 == 0) {//if our even checker finds even, move index.
            h = h - 2;
        }
        if (data[l] % 2 == 0 && data[h] % 2 == 1) {//if odd checker is even; and even checker is odd, swap.
            swap(&data[l], &data[h]);
        }
    }
    printf("\n\nOdd indexes hold odd numbers for sure:\n");
    printList(data, high + 1);
}

void evenPartition(int data[], int high) {
    //in this algorithm "low" index iterates through even indexes;
    // and "high" indexes iterates through odd indexes

    int l = 1;//l checks odd indexes
    int h = high;//h checks even indexes

    if (h % 2 == 1) {//check and make sure that our "high" index is at an odd index.
        h = h - 1;
    }


    while (l < high && h > 1) {
        if (data[l] % 2 == 0) {//if our even checker finds even, move index.
            l = l + 2;
        }
        if (data[h] % 2 == 1) {//if our odd checker finds odd, move index.
            h = h - 2;
        }
        if (data[l] % 2 == 1 && data[h] % 2 == 0) {//if even checker is odd; and odd checker is even, swap.
            swap(&data[l], &data[h]);
            l = l + 2;
            h = h + 2;
        }
    }
    printf("\n\nEven indexes hold even numbers for sure:\n");
    printList(data, high + 1);
}


int main() {
    int inpsize, tmp, oddcount = 0, evencount = 0;

    FILE *fp;
    fp = fopen("DataIn.txt", "r");

    //read integers and keep track of evencount and oddcount.
    fscanf(fp, "%d\n", &inpsize);
    int data[inpsize];
    int i;
    for (i = 0; i < inpsize; i++) {
        fscanf(fp, "%d ", &tmp);
        data[i] = tmp;
        if (tmp % 2 == 1) {
            oddcount++;
        } else {
            evencount++;
        }
    }

    printf("Initial Data:\n");
    printList(data, inpsize);

    if (oddcount > evencount) {
        oddPartition(data, inpsize - 1);
    } else {
        evenPartition(data, inpsize - 1);
    }


    return 0;
}
