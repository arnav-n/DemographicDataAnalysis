#ifndef VREPORT_H
#define VREPORT_H
#include "visitor.h"


#include <iostream>
class visitorReport: public Visitor {
    public:
        void visit(hospitalData *h){
            cout<<"Special report hospital data:"<<endl;
            cout<<"Hospital Info: "<<h->getName()<<endl;
            cout<<"Overall rating (out of 5): "<<h->getOverallRate()<<endl;
        }
        void visit(demogData *d){
            cout<<"Special report demog Data:"<<endl;
            cout<<"Demographics Info (State): " <<d->getName()<<endl;
            cout<<"Education info:"<<endl;
            cout<<"(\% Bachelor degree or more): "<<d->getBAup()<<endl;
            cout<<"(\% high school or more): "<<d->getHSup()<<endl;
            cout<<"\% below poverty: "<<d->getBelowPoverty()<<endl;
        }
};
#endif
