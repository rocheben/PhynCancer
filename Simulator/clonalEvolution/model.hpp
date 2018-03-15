//
//  model.hpp
//  clonalEvolution
//
//  Created by Benjamin ROCHE on 14/03/2018.
//  Copyright © 2018 Benjamin ROCHE. All rights reserved.
//

#ifndef model_h
#define model_h

class Model;

#include "Cell.hpp"
#include "clone.hpp"
#include "random.h"
#include "ListPerso.hpp"

#define MAX_LENGTH 1000
class Model{
private:
    /** Parameters*/
    Random* randomObject;
    /** ListPerso of all agents*/
    char output[1024];
    
    ListPerso* listClones;
    ListPerso* listCells;
    double randomSeed;
    float timeStep;
    double tMax;
    double epochalMutationRate;
    double genomeLength;
    double resourcesAmount;
    double initialDivisionRate;
    double neutralMutationProbability;
    int nbClonesInitial;
    
public:
    Model(char* poutputFile,float pTimeStep,double pTMax,double pEpochalMutationRate,double pNeutralMutationProbability,double pGenomeLength,double pResourcesAmount,double pInitialDivisionRate,int nbClonesInitial);
    ~Model();
    void Init();
    void addClone(Clone*);
    long addCell(Cell*);
    void setResources(double);
    double getResources();
    double getGenomeLength();
    double getEpochalMutation();
    void writeData();
    Random* getRandom();
    void go();
    void conversionSequence(int* pSeqInt,char* pSeqChar);
};

#endif /* model_h */
