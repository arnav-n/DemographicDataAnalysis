#ifndef COMBOH_H
#define COMBOH_H

#include <memory>
#include <string>
#include <iostream>
#include "hospitalData.h"

/*
  aggregated hospital data for a given regional level (county or state)
*/
class comboHospitalData : public hospitalData {
public:

  comboHospitalData(string ident, string countyName, string stateName, string inType):hospitalData(stateName,countyName, inType){
    numHospitals = 0;
    validMCount = 0;
    validRCount = 0;
    validRateCount = 0;
    identifier = ident;
  }
  comboHospitalData(string ident, string inN, string inType):hospitalData(inN, inType){
    numHospitals = 0;
    validMCount = 0;
    validRCount = 0;
    validRateCount = 0;
    identifier = ident;
  }
  double getNumH() const { return numHospitals; }

  int getRCount() const { return validRCount; }
  int getMCount() const{ return validMCount; }
  int getReal() const { return validRateCount; }

  double getOverallRate() const { return overallRate; }
  rating getMortality() const { return mortality; }
  rating getReadmit() const { return readmission; }

  void setMcount(int x){ validMCount = x;};
  void setRcount(int x){ validRCount = x;};
  void setReal(int x){ validRateCount = x;};
  void setMAgg(double x){ mortality.setRatingNum(x);}
  void setRAgg(double x){ readmission.setRatingNum(x);}
  void addHospitaltoRegion(hospitalData* localhosp);

  string getState()const {return placename;}
  string getRegion() const { 
    if(identifier=="state") return placename;
    else return localName;
  }
  friend std::ostream& operator<<(std::ostream &out, const comboHospitalData &HD);

protected:
    string identifier;
    double numHospitals;
    int validRateCount;
    int validMCount;
    int validRCount;
};
#endif
