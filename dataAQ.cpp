/* aggregate data */
#include "dataAQ.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"
#include "visitorReport.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#define DEBUG false

dataAQ::dataAQ() {}

/* necessary function to aggregate the data - this CAN and SHOULD vary per
   student - depends on how they map, etc. */

void dataAQ::stateReport(double minPovertyLine){
  VisitorReport v;
  int total = 0;
  map<string, comboDemogData*>:: iterator it;
  cout<<endl;
    for (it = allStateDemogData.begin(); it!=allStateDemogData.end(); it++){
        if(it->second->getBelowPoverty()>minPovertyLine){
            it->second->accept(v);
            allStateHospData[it->first]->accept(v);
            total++;
        }
    }
    cout<<"Generated a report for a total of: "<<total<<endl;
}
void dataAQ::createStateDemogData(std::vector<shared_ptr<demogData>>& theData) {
	    //process the vector in our county data aggregate 
    for (const auto &obj : theData) {
        string stateName = obj->getState();
        //if first state entry, create it
        if (allStateDemogData.count(stateName) < 1) {
           //cout << "Making a new state entry: " << stateName << endl;
           allStateDemogData[stateName] = new comboDemogData("state", stateName);
        }
        //either way now add this county info 
        //this keeps a running total
        allStateDemogData[stateName]->addDemogtoRegion(obj);
    }
}


void dataAQ::createStateHospData(std::vector<shared_ptr<hospitalData>>& theData) {
  for (const auto &obj : theData) {
        string stateName = obj->getName();
        //if first state entry, create it
        if (allStateHospData.count(stateName) < 1) {
           //cout << "Making a new state entry: " << stateName << endl;
           allStateHospData[stateName] = new comboHospitalData("state", stateName, "");
        }
        //either way now add this county info 
        //this keeps a running total
        allStateHospData[stateName]->addHospitaltoRegion(obj);
    } 
}


void dataAQ::createCountyHospData(std::vector<shared_ptr<hospitalData>>& theHospitalData) {
  for (const auto &obj : theHospitalData) {
        string cityName = obj->getLocalName();
        string stateName = obj->getName();
        string countyName = cityToCounty[cityName+stateName];

        //if first state entry, create it
        if (allCountyHData.count(countyName) < 1) {
           //cout << "Making a new state entry: " << stateName << endl;
           allCountyHData[countyName] = new comboHospitalData("county", countyName+" County", stateName,"");
        }
        //either way now add this county info 
        //this keeps a running total
        allCountyHData[countyName]->addHospitaltoRegion(obj);
  } 
}



bool compareOverall(std::pair<std::string, hospitalData *> left1, std::pair<std::string, hospitalData *> right1) {
    return (left1.second->getOverallRate() < right1.second->getOverallRate());
}

bool compareVecOverall(hospitalData* left, hospitalData* right) {
    double l = left->getOverallRate(); 
    double r = right->getOverallRate();
    if(l==r){
      string lName = left->getArea();
      string rName = right->getArea();
      return lName>rName;
    }
    else return l<r;
}

bool comparePov(demogData* left, demogData* right) {
    double Lpovc = left->getBelowPovertyCount();
    double Lcount = left->getPop();
    double LbelowPercent = Lpovc/Lcount;

    double Rpovc = right->getBelowPovertyCount();
    double Rcount = right->getPop();
    double RbelowPercent = Rpovc/Rcount;


    return LbelowPercent < RbelowPercent;
}
void dataAQ::sortHospRatingLowHigh(std::vector<comboHospitalData *>& hospLowToHigh, 
  string regionType) {
    map<string, comboHospitalData*>:: iterator it;
    for (it = allStateHospData.begin(); it!=allStateHospData.end(); it++){
        hospLowToHigh.push_back(it->second);
    }
    std::sort(hospLowToHigh.begin(), hospLowToHigh.end(), compareVecOverall);
}


void dataAQ::sortHospRatingHighLow(std::vector<comboHospitalData *>& hospHighToLow, 
  string regionType) {
    map<string, comboHospitalData*>:: iterator it;
    for (it = allStateHospData.begin(); it!=allStateHospData.end(); it++){
        hospHighToLow.push_back(it->second);
    }
    std::sort(hospHighToLow.begin(), hospHighToLow.end(), compareVecOverall);
    std::reverse(hospHighToLow.begin(), hospHighToLow.end());
}


/* for a specific state... */
void dataAQ::sortHospRatingHighLowForState(std::vector<comboHospitalData *>& hospHighToLow, string state) {
  // cout<<"size of county map: "<<allCountyHData.size()<<endl;
  map<string, comboHospitalData*>::iterator it;
  for(it = allCountyHData.begin();it!=allCountyHData.end();it++){
    // cout<<it->second->getName()<<endl;
    if(it->second->getName()==state){
      // cout<<"pushing "<<it->second->getArea()<<endl;
      // cout<<"county "<<it->second->getLocalName()<<" found in "<<it->second->getName()<<endl;
      hospHighToLow.push_back(it->second);
    }
  }
  std::sort(hospHighToLow.begin(), hospHighToLow.end(), compareVecOverall);
  std::reverse(hospHighToLow.begin(), hospHighToLow.end());
}




 void dataAQ::sortDemogPovLevelLowHigh(std::vector<demogData *>& povLevelLowHigh) {
  map<string, comboDemogData*>:: iterator it;
    for (it = allStateDemogData.begin(); it!=allStateDemogData.end(); it++){
        povLevelLowHigh.push_back(it->second);
    }

    std::sort(povLevelLowHigh.begin(), povLevelLowHigh.end(), comparePov);
}




 void dataAQ::sortDemogPovLevelHighLow(std::vector<demogData *>& povLevelHighLow) {
    map<string, comboDemogData*>:: iterator it;
    for (it = allStateDemogData.begin(); it!=allStateDemogData.end(); it++){
        povLevelHighLow.push_back(it->second);
    }

    std::sort(povLevelHighLow.begin(), povLevelHighLow.end(), comparePov);
    std::reverse(povLevelHighLow.begin(), povLevelHighLow.end());
}



/*functions to parse city to county helper map */
void dataAQ::read_csvCityCounty(std::string filename) {

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line, state, junk;

        // Now read data, line by line and enter into the map
        while(std::getline(myFile, line)) {

          std::stringstream ss(line);

          string city = getFieldNQ(ss);
          state = getFieldNQ(ss);
          junk = getFieldNQ(ss);
          string county = getFieldNQ(ss);

          string cityKey = city+state;

          cityToCounty[cityKey] = county;

          //cout << "line: " << line << endl;
          //cout << "pair (city, county): " << city << ", " << county << " state " << junk << endl;
        }

        // Close file
        myFile.close();
    }

}
