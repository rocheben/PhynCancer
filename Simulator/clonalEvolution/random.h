//
//  random.h
//  clonalEvolution
//
//  Created by Benjamin ROCHE on 14/03/2018.
//  Copyright © 2018 Benjamin ROCHE. All rights reserved.
//

#ifndef random_h
#define random_h


#include <cstdlib>
#include <stdlib.h>
#include <string.h>
#include <ctime>

class Random {
    
private:
    unsigned int seed;
public:
    Random (double pSeed,char* pOutput){
        unsigned int lTemp=(unsigned int)pSeed;
        for(int lIndex=0;lIndex<(int)strlen(pOutput);lIndex++){
            lTemp+=(unsigned int)pOutput[lIndex];
        }
        seed=(unsigned int)lTemp;
        //seed=1272664111;
        srand(seed);
    }
    double getUnif(){
        double lReturn=0.0;
        lReturn=rand()/(double)RAND_MAX;
        return lReturn;
    }
    unsigned int getSeed(){return seed;}
};

#endif /* random_h */
