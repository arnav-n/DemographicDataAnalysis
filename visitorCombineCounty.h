#ifndef VCOMBOC_H
#define VCOMBOC_H

#include "hospitalData.h"
#include "cityHospitalData.h"
#include "demogData.h"
#include "countyDemogData.h"
#include "visitor.h"
#include "parse.h"
#include <memory>
#include <fstream>

class visitorCombineCounty : public Visitor {
//TODO fill in
    public:
    visitorCombineCounty(string filename){
        // Create an input filestream
        std::ifstream myFile(filename);
        // Make sure the file is open
        if(!myFile.is_open()) throw std::runtime_error("Could not open file");
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

    void visit(hospitalData *obj) {
        string cityName = obj->getLocalName();
        string stateName = obj->getName();
        string countyName = cityToCounty[cityName+stateName]+" County";

        if (allCountyHData.count(countyName) < 1) {
           allCountyHData[countyName] = new comboHospitalData("county", countyName+" County", stateName,"");
        }
        //either way now add this county info 
        //this keeps a running total
        allCountyHData[countyName]->addHospitaltoRegion(obj);
    }
    void visit(demogData *d){
        countyDemogData* cD = dynamic_cast<countyDemogData*> (d);
        string countyName = cD->getCountyName();
        string stateName = cD->getName();
        allCountyDData[countyName] = new comboDemogData("county", countyName+" County");
        allCountyDData[countyName]->addDemogtoRegion(d);
        // cout<<"county demog visitor incomplete"<<endl;
    }
    
    std::map<string, comboDemogData*> countyDmap(){ return allCountyDData; }
    std::map<string, comboHospitalData*> countyHmap() const { return allCountyHData; }
    comboDemogData* countyDmapEntry(string countyName){ 
        return allCountyDData[countyName]; 
    } 
    comboHospitalData* countyHmapEntry(string countyName){ 
        return allCountyHData[countyName]; 
    }

    private:
        std::map<string, comboDemogData*> allCountyDData;
        std::map<string, comboHospitalData*> allCountyHData;
        std::map<string, string> cityToCounty;
};

#endif
