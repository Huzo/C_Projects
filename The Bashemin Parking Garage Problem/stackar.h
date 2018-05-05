        typedef int ElementType;
/* START: fig3_45.txt */
        #ifndef _Stack_h
        #define _Stack_h
		
		#include "car.h"

		
        struct StackRecord
        {
            int Capacity;
            int TopOfStack;
            Car Array;
        };
		
        typedef struct StackRecord *Stack;

        int IsEmpty( Stack S );
        int IsFull( Stack S );
        Stack CreateStack( int MaxElements );
        void DisposeStack( Stack S );
        void MakeEmpty( Stack S );
        void Push( Car X, Stack S );
        Car Top( Stack S );
        void Pop( Stack S );
        Car TopAndPop( Stack S );
		int Find(char *CarLin, Stack S);

        #endif  /* _Stack_h */

/* END */
