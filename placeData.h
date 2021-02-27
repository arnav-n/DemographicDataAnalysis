#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <iostream>

using namespace std;

/* very general data type for any kind of place data - very simple for lab04 */
class Visitor;
class placeData {
  public:
    string getName(){ return placename;}
    virtual void accept(class Visitor &v) = 0;
  protected:
    //place name
    string placename;
};
#endif
