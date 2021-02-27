#ifndef CITYHOSP_H
#define CITYHOSP_H

#include <string>
#include <iostream>
#include <utility>
#include "rating.h"

using namespace std;

/*
  city hospital data for specifics of CORGIS data
*/
class cityHospitalData : public hospitalData   {
public:
  string getCityName(){return cityName;}
  cityHospitalData(string name, string state, string inType, int inOv, string inMort, string inReadmit):
    hospitalData(state, name, inType, inOv, inMort, inReadmit){
    cityName = name;
  }
protected:
    string cityName;
};

#endif
