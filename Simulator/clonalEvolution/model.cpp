//
//  model.cpp
//  clonalEvolution
//
//  Created by Benjamin ROCHE on 14/03/2018.
//  Copyright © 2018 Benjamin ROCHE. All rights reserved.
//

#include <stdio.h>
#include "model.hpp"
#include <string.h>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;

/** Constructor*/
Model::Model(char* poutputFile,float pTimeStep,double pTMax,double pEpochalMutationRate, double pNeutralMutationProbability,double pGenomeLength,double pResourcesAmount,double pInitialDivisionRate,int pNbClonesInitial){
    strcpy(output,poutputFile);
    resourcesAmount=pResourcesAmount;
    epochalMutationRate=pEpochalMutationRate;
    genomeLength=pGenomeLength;
    resourcesAmount=pResourcesAmount;
    neutralMutationProbability=pNeutralMutationProbability;
    timeStep=pTimeStep;
    randomSeed=time(0);
    initialDivisionRate=pInitialDivisionRate;
    tMax=pTMax;
    nbClonesInitial=pNbClonesInitial;
    listClones=new ListPerso();
    listCells=new ListPerso();
}

void Model::addClone(Clone* pClone){
    listClones->add(pClone);
}

long Model::addCell(Cell* pCell){
    listCells->add(pCell);
    return listCells->length();
}

/** Initialization function*/
void Model::Init(){
    //Object initialization
    for(int i=0;i<nbClonesInitial;i++){
        Clone* lNewClone=new Clone();
        lNewClone->setResourceConsumption(randomObject->getUnif()/2);
        lNewClone->setResourceProduction(randomObject->getUnif()/2);
        lNewClone->setDivisionRate(initialDivisionRate);
        lNewClone->setmutationProbability(neutralMutationProbability);
        addClone(lNewClone);
        Cell* lNewCell=new Cell(this,NULL);
        lNewCell->setCloneIdentity(lNewClone);
        long lId=addCell(lNewCell);
        lNewCell->setID(lId);
    }
    
    randomObject=new Random(randomSeed,output);
}

double Model::getEpochalMutation(){
    return epochalMutationRate;
}

void Model::setResources(double pResources){
    resourcesAmount=pResources;
}

double Model::getResources(){
    return resourcesAmount;
}
double Model::getGenomeLength(){
    return genomeLength;
}

Random* Model::getRandom(){
    return randomObject;
}

/** Destructor*/
Model::~Model(){
    
    for(int i=0;i<listClones->length();i++){
        delete (Clone*)listClones->getElement(i);
    }
    for(int i=0;i<listCells->length();i++){
        delete (Cell*)listCells->getElement(i);
    }
}


/** Simulation behavior for one thread version*/
void Model::go(){
    //Start the simulation
    for(double t=0;t<tMax;t+=timeStep){
        if( ((long)t % (long)100) == 0){
            cout<<t<<endl;
        }
        
        for(int lIndex=0;lIndex<listCells->length();lIndex++){
            Cell* lCell=((Cell*)(listCells->getElement(lIndex)));
            lCell->cellStep();
        }
    }
}

void Model::conversionSequence(int* pSeqInt,char* pSeqChar){
    for(int i=0;i<genomeLength;i++){
        if(pSeqInt[i]==0){
            pSeqChar[i]='A';
        }
        if(pSeqInt[i]==1){
            pSeqChar[i]='C';
            
        }
        if(pSeqInt[i]==2){
            pSeqChar[i]='T';
            
        }
        if(pSeqInt[i]==3){
            pSeqChar[i]='G';
            
        }
    }
    pSeqChar[(long)genomeLength]='\0';
}

/** Write all data about each agent*/
void Model::writeData(){
    char* lLine=new char[genomeLength*2];
    char* lSequence=new char[genomeLength*2];
    char lFileName[2048];
    
    sprintf(lFileName,"%s_sequences.dat",output);
    FILE* lFileSeq=fopen(lFileName,"wt");
    sprintf(lFileName,"%s_tree.dat",output);
    FILE* lFileTree=fopen(lFileName,"wt");
    cout<<"Writing file..."<<endl;
    //Write sequence file
    for(int i=0;i<listCells->length();i++){
        //Sequence recuperation
        Cell* lCell=(Cell*)listCells->getElement(i);
        conversionSequence(lCell->getGenome(),lSequence);
        sprintf(lLine,"%d\n%s\n",i,lSequence);
        fwrite(lLine,1,strlen(lLine),lFileSeq);
        //Parent recuperation
        Cell* lCellParent=lCell;
        sprintf(lLine,"%ld",lCellParent->getID());
        lCellParent=lCellParent->getParent();
        if(lCellParent!=NULL){
            sprintf(lLine,"%s,%ld",lLine,lCellParent->getID());
        }
        sprintf(lLine,"%s\n",lLine);
        fwrite(lLine,1,strlen(lLine),lFileTree);
    }
    fclose(lFileSeq);
    fclose(lFileTree);
    //Write relationship file
    delete [] lLine;
    delete [] lSequence;
}

