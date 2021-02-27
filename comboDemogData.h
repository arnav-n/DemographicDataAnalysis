#ifndef COMBOD_H
#define COMBOD_H

#include <memory>
#include <string>
#include <iostream>
#include "demogData.h"
#include "placeData.h"

/*
  aggregated demographic data for a given regional level (state - or larger region)
*/
class comboDemogData : public demogData  {
  public:
  comboDemogData(string ident, string inS):demogData(inS) {
    identifier = ident;
  }
  //aggregator method
  void addDemogtoRegion(demogData* local);

  protected:
    string identifier;
};
#endif
