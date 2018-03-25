#include <iostream>
#include <stdio.h>
#include <string.h>

using namespace std;

#include "model.hpp"

int main(int argc,char* argv[])
{
    cout << "Individual-based model for clonal evolutionary dynamics" << endl;
    Model* lModel;
    char loutputFile[256];
    strcpy(loutputFile,"testClonalEvolution");
    float lTimeStep=1;
    double lTimeMax=2000;
    double lEpochalMutationRate=0.0000;
    double lGenomeLength=100000;
    double lResourcesAmount=30;
    double lInitialDivisionRate=0.002;
    double lNeutralMutationProbability=0.01;
    int lNbClonesInitial=2;
    
    //If paramfile, timestep and outputfile are filled
    if(argc==9){
        strcpy(loutputFile,argv[1]);
        lTimeStep=atof(argv[2]);
        lTimeMax=atof(argv[3]);
        lEpochalMutationRate=atof(argv[4]);
        lNeutralMutationProbability=atof(argv[5]);
        lGenomeLength=atof(argv[6]);
        lResourcesAmount=atof(argv[7]);
        lInitialDivisionRate=atof(argv[8]);
        lNbClonesInitial=atof(argv[9]);
    }
    else{
        cout<<"No parameters, laoding defaults. Syntax: "<<argv[0]<<" outputFile timeStep timeMax epochalMutationProbability neutralMutationProbability genomeLength resourcesAmount initialDivisionRate nbClonesInitial"<<endl;

    }
    //Build model object
    lModel=new Model(loutputFile,lTimeStep,lTimeMax,lEpochalMutationRate,lNeutralMutationProbability,lGenomeLength,lResourcesAmount,lInitialDivisionRate,lNbClonesInitial);
    lModel->Init();
    //Launch the simulation
    lModel->go();
    
    //Write Data
    lModel->writeData();

    delete lModel;

    return 0;
}

