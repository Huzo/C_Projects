/* START: */
        #ifndef _Car_h
        #define _Car_h

       struct CarNode
        {
			char CarLicense[7];
			int Movement;
        };
		
        typedef struct CarNode * Car;
        
        Car CreateCar(char *CarLin);
        void DisposeCar(Car C );        

        #endif  /* _Car_h */

/* END */
