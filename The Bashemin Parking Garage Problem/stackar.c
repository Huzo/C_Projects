#include "car.h"
#include "stackar.h"
#include "fatal.h"
#include <stdlib.h>
#include "string.h"

#define EmptyTOS ( -1 )
#define MinStackSize ( 5 )


/* START: fig3_48.txt */
int
IsEmpty( Stack S )
{
    return S->TopOfStack == EmptyTOS;
}
/* END */

int
IsFull( Stack S )
{
    return S->TopOfStack == S->Capacity - 1;
}


/* START: fig3_46.txt */
Stack
CreateStack( int MaxElements )
{
    Stack S;

/* 1*/      if( MaxElements < MinStackSize )
/* 2*/          Error( "Stack size is too small" );

/* 3*/      S = malloc( sizeof( struct StackRecord ) );
/* 4*/      if( S == NULL )
/* 5*/          FatalError( "Out of space!!!" );

/* 6*/      S->Array = malloc( sizeof( struct CarNode ) * MaxElements );
/* 7*/      if( S->Array == NULL )
/* 8*/          FatalError( "Out of space!!!" );
/* 9*/      S->Capacity = MaxElements;
/*10*/      MakeEmpty( S );

/*11*/      return S;
}
/* END */

/* START: fig3_49.txt */
void
MakeEmpty( Stack S )
{
    S->TopOfStack = EmptyTOS;
}
/* END */

/* START: fig3_47.txt */
void
DisposeStack( Stack S )
{
    if( S != NULL )
    {
        free( S->Array );
        free( S );
    }
}
/* END */

/* START: fig3_50.txt */
void
Push( Car X, Stack S )
{
    if( IsFull( S ) )
        Error( "Full stack" );
    else
    {
        strcpy(S->Array[ ++S->TopOfStack ].CarLicense, X->CarLicense);
        S->Array[ S->TopOfStack ].Movement= X->Movement;
    }
}
/* END */


/* START: fig3_51.txt */
Car
Top( Stack S )
{
    if( !IsEmpty( S ) )
        return &(S->Array[ S->TopOfStack ]);
    Error( "Empty stack" );
    return NULL;  /* Return value used to avoid warning */
}
/* END */

/* START: fig3_52.txt */
void
Pop( Stack S )
{
    if( IsEmpty( S ) )
        Error( "Empty stack" );
    else
        S->TopOfStack--;
}
/* END */

/* START: fig3_53.txt */
Car
TopAndPop( Stack S )
{
    if( !IsEmpty( S ) )
        return &(S->Array[ S->TopOfStack-- ]);
    Error( "Empty stack" );
    return NULL;  /* Return value used to avoid warning */
}
/* END */

int
Find(char *CarLin, Stack S)
{
    int i = S->TopOfStack;

    while(i>=0)
    {
        if (strcmp(CarLin, S->Array[ i ].CarLicense)!=0)
            i--;
        else
            return i;
    }

    return -1;//fail to find
}