//
//  clone.hpp
//  clonalEvolution
//
//  Created by Benjamin ROCHE on 14/03/2018.
//  Copyright © 2018 Benjamin ROCHE. All rights reserved.
//

#ifndef clone_hpp
#define clone_hpp

class Clone;

#include <stdio.h>
#include "model.hpp"

class Clone{
private:
    /** Pathogens in Infectious state*/

    Model* model;
    double resourceConsumption;
    double resourceProduction;
    double divisionRate;
    double mutationProbability;
public:
    
    /** Constructor (first function called at the object's creation)*/
    Clone();
    ~Clone();
    double getResourceConsumption();
    double getResourceProduction();
    double getDivisionRate();
    void setResourceConsumption(double);
    void setResourceProduction(double);
    void setDivisionRate(double);
    void setmutationProbability(double);
    double getMutationProbability();
};



#endif /* clone_hpp */
