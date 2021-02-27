#ifndef VCOMBOS_H
#define VCOMBOS_H

#include "hospitalData.h"
#include "demogData.h"
#include "visitor.h"
#include <memory>

class visitorCombineState : public Visitor {
//TODO fill in
    public:
    void visit(demogData *d) {
        // cout<<"started"<<endl;
        string stateName = d->getState();
        //if first state entry, create it
        if (allStateDemogData.count(stateName) < 1) {
            // cout << "Making a new state entry: " << stateName << endl;
            allStateDemogData[stateName] = new comboDemogData("state", stateName);
        }
        //either way now add this county info 
        //this keeps a running total

        //this function takes in a shared pointer
        allStateDemogData[stateName]->addDemogtoRegion(d);
    }

    void visit(hospitalData *h) {
        string stateName = h->getName();
        //if first state entry, create it
        if (allStateHospData.count(stateName) < 1) {
           //cout << "Making a new state entry: " << stateName << endl;
           allStateHospData[stateName] = new comboHospitalData("state", stateName, "");
        }
        //either way now add this county info 
        //this keeps a running total

        //this function takes in a shared pointer
        allStateHospData[stateName]->addHospitaltoRegion(h);
    } 

    std::map<string, comboDemogData*> stateDmap(){ return allStateDemogData; }
    std::map<string, comboHospitalData*> stateHmap() const { return allStateHospData; }
    comboDemogData* stateDmapEntry(string stateName){ 
        return allStateDemogData[stateName]; 
        } 
    comboHospitalData* stateHmapEntry(string stateName){ 
        return allStateHospData[stateName]; 
        }

    private:
        std::map<string, comboDemogData*> allStateDemogData;
        std::map<string, comboHospitalData*> allStateHospData;

};

#endif
