#ifndef DEMOGD_H
#define DEMOGD_H

#include <memory>
#include <string>
#include <iostream>
#include "placeData.h"

/*
  class to represent generic demographic data all regional level
*/
class demogData: public placeData {
  public:
    demogData(string inS) :
            popOver65(0), popUnder18(0),
            popUnder5(0), bachelorDegreeUp(0), highSchoolUp(0),
            belowPoverty(0), population2014(0){
              placename=inS;
    }
    demogData(string inS, int in65, int in18,
        int in5, int inBA, int inHS, int belowPov, int totalPop14) :
            popOver65(in65), popUnder18(in18),
            popUnder5(in5), bachelorDegreeUp(inBA), highSchoolUp(inHS),
            belowPoverty(belowPov), population2014(totalPop14) {
              placename = inS;
    }
    string getState() {return placename;}

    double getpopOver65()  const { return 100.0f*(double)(popOver65)/population2014; }
    double getpopUnder18() const { return 100.0f*(double)(popUnder18)/population2014; }
    double getpopUnder5() const{ return 100.0f*(double)(popUnder5)/population2014; }
    double getBAup() const { return 100.0f*(double)(bachelorDegreeUp)/population2014; }
    double getHSup() const { return 100.0f*(double)(highSchoolUp)/population2014; }
    double getBelowPoverty() const { return 100.0f*(double)(belowPoverty)/population2014; }

    int getpopOver65Count() const { return popOver65; }
    int getpopUnder18Count() const { return popUnder18; }
    int getpopUnder5Count() const { return popUnder5; }
    int getBAupCount() const { return bachelorDegreeUp; }
    int getHSupCount() const { return highSchoolUp; }
    int getBelowPovertyCount() const { return belowPoverty; }
    int getPop() { return population2014;}
    friend std::ostream& operator<<(std::ostream &out, const demogData &DD);

    void accept(class Visitor &v);


  protected:
    //age, education, income data
     int popOver65;
     int popUnder18;
     int popUnder5;
     int bachelorDegreeUp;
     int highSchoolUp;
     int belowPoverty;
    int population2014;
  };
#endif
