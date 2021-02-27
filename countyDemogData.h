#ifndef CDEMOG_H
#define CDEMOG_H

#include <string>
#include <iostream>
#include "demogData.h"

using namespace std;

/*
  county demographic data used to represent the CORGIS data
*/
class countyDemogData : public demogData {
public:
  countyDemogData(string inName, string inState, int in65, int in18,
        int in5, int inBA, int inHS, int belowPov, int totalPop14):demogData( inState,  in65,  in18,
         in5,  inBA,  inHS,  belowPov,  totalPop14){
    countyName=inName;
  }
  countyDemogData(string inName, string inState):demogData(inState){
    countyName=inName;
  }
  string getCountyName(){ return countyName;}
protected:
    string countyName;
};
#endif
