
#include "comboHospitalData.h"
#include <sstream>
#include <string>
#include <assert.h>


std::ostream& operator<<(std::ostream &out, const comboHospitalData &HD){
    out << "Combined hospital data at level: " << HD.getRegion()<< " in "<<HD.placename;
    out << "\nincludes num hospitals: " << HD.numHospitals;
    out << "\nOverall rating (out of 5): "<<HD.overallRate;
    out << "\nmortality rating: " <<HD.mortality;
    out << "\nreadmission rating:" <<HD.readmission;
    out << endl;
    return out;
}


void comboHospitalData::addHospitaltoRegion(hospitalData* localhosp) {
    //double check that the hospital's state is this one

    //if the star rating exists, calculate the new average rating
    //otherwise ignore the rating
    int localRate = localhosp->getOverallRate();
    if (localRate!=-1){
        double temp = 
        (overallRate*getReal())+(localhosp->getOverallRate()); 
        temp = temp/(getReal()+1);
        // overallRate += localRate;
        overallRate = temp;
        setReal(getReal()+1);
    }

    int localMortNum = localhosp->getMortality().getRatingNum();
    int validMcount = getMCount();
    //if rating is valid, add to current average
    if (localMortNum>0){
        //convert average to total
        mortality*=validMcount;
        //add local count to total
        mortality+=localhosp->getMortality();
        //increase the valid counter, convert total back to average
        validMcount++;
        mortality/=validMcount;
        //set variable to new mCount
        setMcount(validMcount);
    }

    int localReNum = localhosp->getReadmit().getRatingNum();
    int validRcount = getRCount();
    if (localReNum>0){
        readmission*=validRcount;
        readmission+=localReNum;
        validRcount++;
        readmission/=validRcount;
        setRcount(validRcount);
    }
    numHospitals++;
}
