//
//  Cell.hpp
//  clonalEvolution
//
//  Created by Benjamin ROCHE on 14/03/2018.
//  Copyright © 2018 Benjamin ROCHE. All rights reserved.
//

#ifndef Cell_hpp
#define Cell_hpp

class Cell;

#include <stdio.h>
#include "model.hpp"
#include "clone.hpp"
#include <iostream>
#include <math.h>

/* */
class Cell{
private:
    /** Pathogens in Infectious state*/
    Clone* cloneIdentity;
    int* genome;
    Model* model;
    Cell* parent;
    long ID;
public:
    
    /** Constructor (first function called at the object's creation)*/
    Cell(Model* pModel,Cell*);
    ~Cell();
    void cellStep();
    void CellUpdate();
    void cellMutation(bool);
    void setCloneIdentity(Clone*);
    Clone* getCloneIdentity();
    int* getGenome();
    Cell* getParent();
    void setID(long);
    long getID();
};


#endif /* Cell_hpp */
