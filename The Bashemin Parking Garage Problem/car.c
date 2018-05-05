#include "car.h"
#include "fatal.h"
#include <stdlib.h>


Car
CreateCar( char *CarLin )
{
    Car C;
    int i = 0;

    C = malloc( sizeof( struct CarNode ) );
    if( C == NULL )
        FatalError( "Out of space!!!" );

    for(;i<6;i++ )
    {
        C->CarLicense[i] = CarLin[i];
    }
    C->CarLicense[6]='\0';

    C->Movement=0;

    return C;
}

void
DisposeCar( Car C )
{
    if( C != NULL )
    {
        free( C );
    }
}