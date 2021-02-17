

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"
#include "tddFuncs.h"
#include "visitorReport.h"
#include "visitorCombineState.h"
#include "visitorCombineCounty.h"
#include "stats.h"
using namespace std;

int main() {


  cout << "Testing stats on Data" << endl;


  std::vector<shared_ptr<placeData>> pileOfData;

  //read in the hospital data
  read_csv(pileOfData, "hospitals.csv", HOSPITAL);
   
  //read in the demographic data
  read_csv(pileOfData, "county_demographics.csv", DEMOG); 

  //create a visitor to combine the state data
  visitorCombineState theStates;
  //use visitor pattern to be able to aggregate
  for (const auto &obj : pileOfData) {
        obj->accept((visitorCombineState&)theStates);
  }
  visitorCombineCounty theCounties("simple_uscities.csv");
  //use visitor pattern to be able to aggregate
  for (const auto &obj : pileOfData) {
        obj->accept((visitorCombineCounty&)theCounties);
  }

  vector<double> dataX;
  vector<double> dataY;
  for (auto entry : theCounties.allCountyHData) {
    if (theCounties.allCountyDData.count(entry.first) > 0) {
        dataY.push_back((theCounties.allCountyDData[entry.first])->getBelowPoverty());
        dataX.push_back((theCounties.allCountyDData[entry.first])->getHSup());
    }
  }

   double meanX = stats::computeMean(dataX);
   double stdDevX =  stats::computeMean(dataY);
   double meanY = stats::computeStdDevSample(dataX);
   double stdDevY = stats::computeStdDevSample(dataY);

/*
  ASSERT_EQUALS(meanX, ?);
  ASSERT_EQUALS(stdDevX, ?);
  ASSERT_EQUALS(meanY, ?);
  ASSERT_EQUALS(stdDevY, ?);
  */

  return 0;
}
