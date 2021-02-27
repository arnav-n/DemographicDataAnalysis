#include "dataAQ.h"
#include "parse.h"
#include <iostream>
#include "tddFuncs.h"
using namespace std;

int main() {


// cout << "Testing hospital sort..." << endl;

	dataAQ theAnswers;
  std::vector<shared_ptr<placeData>> theDemogData;

    std::vector<shared_ptr<placeData>> theHospitalData = read_csv(
            "hospitals.csv", HOSPITAL);

    //create the state hospital data
    theAnswers.createStateHospData((std::vector<shared_ptr<hospitalData>>&)theHospitalData);

    theAnswers.createCountyHospData((std::vector<shared_ptr<hospitalData>>&)theHospitalData);

    std::vector<comboHospitalData*> hospHighToLow;
    theAnswers.sortHospRatingHighLow((std::vector<comboHospitalData *>& )hospHighToLow, "state");

  // Test case #1
  // string topHosp[] {"WI", "SD", "UT", "HI", "ID"};
  // for (int i=0; i < 5; i++) {
  // 	ASSERT_EQUALS(topHosp[i], hospHighToLow.at(i)->getState());
  // }


/* NEW - sorted hospital county info by state - Specifically, CA */
    std::vector<comboHospitalData*> CAhospHighToLow;
    theAnswers.sortHospRatingHighLowForState((std::vector<comboHospitalData *>& )CAhospHighToLow, "CA");

    for (int i = 0; i < CAhospHighToLow.size(); i++) {
      // cout<<*CAhospHighToLow[i]<<endl;
    }
      
  return 0;
}
