#include "comboDemogData.h"
#include "demogData.h"
#include <sstream>
#include <string>
#include <assert.h>
#include <iomanip>


void comboDemogData::addDemogtoRegion(demogData* CI) {
    // assert(placename.compare(CI->getState()) == 0);
	popOver65 += CI->getpopOver65Count();
	popUnder18 += CI->getpopUnder18Count();
	popUnder5 += CI->getpopUnder5Count();
	bachelorDegreeUp += CI->getBAupCount();
	highSchoolUp += CI->getHSupCount() ;
    belowPoverty += CI->getBelowPovertyCount();
	population2014 += CI->getPop();
}