#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
#include <math.h>
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
#include "statTool.h"
#include "statGatherer.h"

using namespace std;


int main() {

    std::vector<shared_ptr<placeData>> pileOfData;

    //set up outpout format
    cout << std::setprecision(2) << std::fixed;

    //read in the hospital data
    read_csv(pileOfData, "hospitals.csv", HOSPITAL);


    //read in the demographic data
    read_csv(pileOfData, "county_demographics.csv", DEMOG); 

    //create a visitor to combine the state data
    visitorCombineState theStates;
    //create the state demographic data
    statTool::createStateData(pileOfData, theStates);
    //theStates.printAllStates();

    //create a visitor to combine the county data (need aux map city-> county)
    visitorCombineCounty theCounties("simple_uscities.csv");
    statTool::createCountyData(pileOfData, theCounties);
    //theCounties.printAllCounties();

    //create statGathers to help make the data one for states one for counties
    stateGather fillStates;
    countyGather fillCounties;

    // std::map<string, comboDemogData*> countyD = theCounties.countyDmap();
    // int n=0;
    // map<string, comboDemogData*>:: iterator it;
    // for (it = countyD.begin(); it!=countyD.end(); it++){
    //     cout<<it->first<<endl;
    //     // cout<<endl;
    //     n++;
    // }

    map<string, comboHospitalData*>:: iterator it2;
    std::map<string, comboHospitalData*> countyH = theCounties.countyHmap();
    map<string, comboHospitalData*>:: iterator it3;
    for (it2 = countyH.begin(); it2!=countyH.end(); it2++){
        int z = it2->second->getOverallRate();
        if(z==0) cout<<*(it2->second)<<endl;
    }

    vector<double> dataX;
    vector<double> dataY;

    fillCounties.gatherPerStats(&theCounties, dataX, dataY, &demogData::getBelowPoverty, &comboHospitalData::getOverallRate);

    double mX = stats::computeMean(dataX); 
    double mY = stats::computeMean(dataY);  
    double cc = stats::computeCorCoeffSample(dataX, dataY);
    cout<<mX<<" = "<<16.489<<endl;
    cout<<mY<<" = "<<2.5392<<endl;
    cout<<cc<<" = "<<-0.0948<<endl;
    // cout<<"num of counties:"<<n<<endl;
    // ASSERT_EQUALS(mX, 16.489);
    // ASSERT_EQUALS(mY, 2.5392);
    // ASSERT_EQUALS(cc, -0.0948);


    // debug print
    // std::map<string, comboHospitalData*> stateHosp = theStates.stateHmap();
    // map<string, comboHospitalData*>:: iterator it3;
    // for (it3 = stateHosp.begin(); it3!=stateHosp.end(); it3++){
    //     cout<<*(it3->second)<<endl;
    //     cout<<endl;
    // }
    //Do stats work here these are examples...
    // visitorReport v;
    // for(int i = 0; i<pileOfData.size(); i++){
    //     pileOfData[i]->accept(v);
    //     cout<<endl;
    // }

    cout<<endl;
    //mixed data use 'sample'
    // cout << "State data over 65  and overall rate: " << endl;
    // statTool::computeStatsMixRegionData(&theStates, &fillStates, &demogData::getpopOver65, &comboHospitalData::getOverallRate);
    // cout<<endl;

    // cout << "County data over 65 and number Hospitals: " << endl;
    // statTool::computeStatsMixRegionData(&theCounties, &fillCounties, &demogData::getHSup, &comboHospitalData::getOverallRate);
    // cout<<endl;

    // //demogxdemog sample
    // cout << "below 18 and below 5: " << endl;
    // statTool::computeStatsDemogRegionData(&theStates, &fillStates, &demogData::getpopUnder18, &demogData::getpopUnder5,
    //     &demogData::getpopUnder18Count, &demogData::getpopUnder5Count);
    // cout<<endl;

    // cout << "County data below 18 and below 5: " << endl;
    // statTool::computeStatsDemogRegionData(&theCounties, &fillCounties, &demogData::getHSup, &demogData::getBelowPoverty,
    //     &demogData::getHSupCount, &demogData::getBelowPovertyCount);

    return 0;
}



