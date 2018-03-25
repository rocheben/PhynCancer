//
//  Cell.cpp
//  clonalEvolution
//
//  Created by Benjamin ROCHE on 14/03/2018.
//  Copyright © 2018 Benjamin ROCHE. All rights reserved.
//

#include "Cell.hpp"

using namespace std;
/** Constructor from parameters*/
Cell::Cell(Model* pModel,Cell* pParentCell)
{
    model=pModel;
    genome=new int[pModel->getGenomeLength()];
    parent=pParentCell;
    if(parent!=NULL){
        int* lGenomeParent=parent->getGenome();
        for(int lIndex=0;lIndex<pModel->getGenomeLength();lIndex++){
            genome[lIndex]=lGenomeParent[lIndex];
        }
    }
    else{
        for(int lIndex=0;lIndex<pModel->getGenomeLength();lIndex++){
            genome[lIndex]=ceil(pModel->getRandom()->getUnif()*4)-1;
        }
    }
}

Cell::~Cell(){
    delete [] genome;
}

int* Cell::getGenome(){
    return genome;
}

void Cell::cellMutation(bool pEpochal){
    if(pEpochal){
        int baseMutation=ceil(model->getRandom()->getUnif()*4);
        genome[baseMutation]=genome[baseMutation]+1;
        if(genome[baseMutation]==4){
            genome[baseMutation]=0;
        }
    }
    else{
        int baseMutation=ceil(model->getRandom()->getUnif()*(model->getGenomeLength()-4));
        genome[baseMutation+4]=genome[baseMutation]+1;
        if(genome[baseMutation+4]==4){
            genome[baseMutation+4]=0;
        }
    }
}

void Cell::setCloneIdentity(Clone* pClone){
    cloneIdentity=pClone;
}

Cell* Cell::getParent(){
    return parent;
}

void Cell::setID(long pID){
    ID=pID;
}

long Cell::getID(){
    return ID;
}

/** This function is the first called on object by the model scheduler: It sets 'time' of change (if it occurs) and implements all events*/
void Cell::cellStep()
{
    double lProbDivision=cloneIdentity->getDivisionRate();
    //If there is enough resources for division
    if(getCloneIdentity()->getResourceConsumption()<model->getResources()){
        if(model->getRandom()->getUnif()< lProbDivision){
            //Division
            model->setResources(model->getResources()-cloneIdentity->getResourceConsumption());
            double lProbaMutationEpochal=model->getEpochalMutation();
            Clone* lCloneIdentity=cloneIdentity;
            if(model->getRandom()->getUnif()< lProbaMutationEpochal){
                //Emergence of a new clone
                Clone* lNewClone=new Clone();
                double fitnessEffetRC=(model->getRandom()->getUnif()-0.5)/2;    //25% change maximum
                lNewClone->setResourceConsumption(cloneIdentity->getResourceConsumption()* fitnessEffetRC);
                double fitnessEffetRP=(model->getRandom()->getUnif()-0.5)/2;    //25% change maximum
                lNewClone->setResourceProduction(cloneIdentity->getResourceProduction()* fitnessEffetRP);
                double fitnessEffetDR=(model->getRandom()->getUnif()-0.5)/2;    //25% change maximum
                lNewClone->setResourceProduction(cloneIdentity->getDivisionRate()* fitnessEffetDR);
                model->addClone(lNewClone);
                lCloneIdentity=lNewClone;
            }
            Cell* lNewCell=new Cell(model,this);
            lNewCell->setCloneIdentity(lCloneIdentity);
            int lID=model->addCell(lNewCell);
            lNewCell->setID(lID);
            if(lCloneIdentity!=cloneIdentity){
                lNewCell->cellMutation(true);
            }
            double lProbaMutation=cloneIdentity->getMutationProbability();
            if(model->getRandom()->getUnif()< lProbaMutation){
                lNewCell->cellMutation(false);
            }
        }
    }
    else{
        cout<<"Resources limitation"<<endl;
    }
    //Resources production by the cell
    model->setResources(model->getResources()+cloneIdentity->getResourceProduction());
}

/** This function is called when function Update is called on all objects: It changes the state of agent initialize by function agentStep*/
void Cell::CellUpdate()
{
    
}


Clone* Cell::getCloneIdentity(){
    return cloneIdentity;
}
/** Gettors*/

