//
//  clone.cpp
//  clonalEvolution
//
//  Created by Benjamin ROCHE on 14/03/2018.
//  Copyright © 2018 Benjamin ROCHE. All rights reserved.
//

#include "clone.hpp"

Clone::Clone(){
    
}

Clone::~Clone(){
    
}

void Clone::setmutationProbability(double pMutationProbability){
    mutationProbability=pMutationProbability;
}

double Clone::getResourceConsumption(){
    return(resourceConsumption);
}

double Clone::getResourceProduction(){
    return(resourceProduction);
}

double Clone::getDivisionRate(){
    return(divisionRate);
}

void Clone::setResourceConsumption(double presourceConsumption){
    resourceConsumption=presourceConsumption;
}

void Clone::setResourceProduction(double presourceProduction){
    resourceConsumption=presourceProduction;
}

void Clone::setDivisionRate(double pdivisionRate){
    divisionRate=pdivisionRate;
}

double Clone::getMutationProbability(){
    return mutationProbability;
}
