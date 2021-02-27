#include "hospitalData.h"
#include "visitor.h"
#include <sstream>


/* print hospital data */
std::ostream& operator<<(std::ostream &out, const hospitalData &HD) {
    out << "Hospital Info: " << HD.getArea();
    out << "\nType: " << HD.type;
    out << "\nOverall rating (out of 5): "<<HD.overallRate;
    out << "\nmortality rating: " <<HD.mortality;
    out << "readmission rating:" <<HD.readmission ;
    return out;
}
void hospitalData::accept(class Visitor &v){
    // cout<<"accepting visitor"<<endl;
    v.visit(this);
}
