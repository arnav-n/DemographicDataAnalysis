#ifndef HOSP_H
#define HOSP_H

#include <string>
#include <iostream>
#include <utility>
#include "rating.h"
#include "placeData.h"

using namespace std;
/*
  class to represent hospital data
*/
class hospitalData : public placeData  {
  public:
    hospitalData(string inN, string local, string inType){
      localName = local;
      type = inType;
      placename = inN;
      overallRate = 0;
    }
    hospitalData(string inN, string inType){
      localName = "";
      type = inType;
      placename = inN;
      overallRate = 0;
    }
    hospitalData(string inN, string local, string inType, int inOv, string inMort, string inReadmit) :
            type(inType), overallRate(inOv), mortality(inMort), readmission(inReadmit) {
              localName = local;
              placename=inN;
    }

    double getOverallRate() const { return overallRate; }
    rating getMortality() const { return mortality; }
    rating getReadmit() const { return readmission; }
    friend std::ostream& operator<<(std::ostream &out, const hospitalData &HD);
    void accept(class Visitor &v);
    string getLocalName() { return localName; }
    
    string getArea() const{
      if (localName=="" ) return placename;
      return localName;
    }
  protected:
  //rating info
    string localName;
    string type;
    double overallRate;
    rating mortality;
    rating readmission;
};

#endif
