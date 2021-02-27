/* helper routines to read out csv data */
// #include "dataAQ.h"
#include "demogData.h"
#include "comboDemogData.h"
#include "comboHospitalData.h"
#include "countyDemogData.h"
#include "comboHospitalData.h"
#include "hospitalData.h"
#include "cityHospitalData.h"
#include "parse.h"
#include <algorithm>
#include <cmath>

//TODO fix once you have new types 


/* helper to strip out quotes from a string */
string stripQuotes(std::string temp) {
    temp.erase(
        remove(temp.begin(), temp.end(), '\"' ),
        temp.end());
    return temp;
}

/* helper: get field from string stream */
/* assume field has quotes for CORGIS */
string getField(std::stringstream &ss) {
    string data, junk;
    //ignore the first quotes
    std::getline(ss, junk, '\"');
    //read the data (not to comma as some data includes comma (Hospital names))
    std::getline(ss, data, '\"');
    //read to comma final comma (to consume and prep for next)
    std::getline(ss, junk, ',');
    //data includes final quote (see note line 18)
    return stripQuotes(data);
}


string getFieldNQ(std::stringstream &ss) {
    string temp;
    std::getline(ss, temp, ',');
    //std::cout << temp << std:: endl;
    return temp;
}

/* helper: read out column names for CSV file */
void consumeColumnNames(std::ifstream &myFile) {
    std::string line;
    std::string colname;

    // Extract the first line in the file
    std::getline(myFile, line);

    // Create a stringstream from line
    std::stringstream ss(line);

    // Read the column names (for debugging)
    // Extract each column name for debugging
    while(std::getline(ss, colname, ',')) {
    //    std::cout << colname << std::endl;
    }
}

/* Read one line from a CSV file for county demographic data specifically */
shared_ptr<demogData> readCSVLineDemog(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string state = getField(ss);

    //turn into mathematical percent
    double popOver65 = stod(getField(ss))/100.0;
    double popUnder18 = stod(getField(ss))/100.0;;
    double popUnder5 = stod(getField(ss))/100.0;;
    double bachelorDegreeUp = stod(getField(ss))/100.0;;
    double highSchoolUp = stod(getField(ss))/100.0;;

    //now skip over some data
    for (int i=0; i < 20; i++)
        getField(ss);

    //turn into mathematical percent
    double belowPoverty = stod(getField(ss))/100;

    //now skip over some data 
    for (int i=0; i < 10; i++)
        getField(ss);

    int totalPop2014 = stoi(getField(ss));

    //store demographic data as counts
    return make_shared<countyDemogData>(name, state, round(popOver65*totalPop2014), 
            round(popUnder18*totalPop2014),
            round(popUnder5*totalPop2014), 
            round(bachelorDegreeUp*totalPop2014), 
            round(highSchoolUp*totalPop2014), 
            round(belowPoverty*totalPop2014), 
            totalPop2014);
}


//read from a CSV file (for a given data type) return a vector of the data
// DO NOT modify 
std::vector<shared_ptr<placeData>> read_csv(std::vector<shared_ptr<placeData>> &theData, std::string filename, typeFlag fileType) {

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create demographic dataobject
        while(std::getline(myFile, line)) {
            if (fileType == DEMOG)  theData.push_back(readCSVLineDemog(line));
            else if (fileType == HOSPITAL) 
            theData.push_back(readCSVLineHospital(line));
            else {
                cout << "ERROR - unknown file type" << endl;
                exit(0);
            }
        }

        // Close file
        myFile.close();
    }

    return theData;
}

//COMMENTINGOUT ALL HOSPITAL PARSING

/* Read one line from a CSV file for hospital data specifically */
shared_ptr<hospitalData> readCSVLineHospital(std::string theLine) {
    std::stringstream ss(theLine);
    
    string name = getField(ss);
    string city = getField(ss); 
    string state = getField(ss);
    string type  = getField(ss);
    string temp = getField(ss);
    int overallRate = stoi(temp);

    string mort = getField(ss);
    //safety should be ignored?
    string safety = getField(ss);
    string readmit = getField(ss);
 
    //TODO you need to read rating data

    return make_shared<cityHospitalData>(city, state, type, overallRate, mort, readmit);
}

// read from a CSV file (for a given data type) return a vector of the 
// hospital data
// DO NOT modify 
std::vector<shared_ptr<hospitalData>> read_csvHospital(std::string filename, typeFlag fileType) {
    //the actual data
    std::vector<shared_ptr<hospitalData>> theData;

    // Create an input filestream
    std::ifstream myFile(filename);

    // Make sure the file is open
    if(!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    if(myFile.good()) {
        consumeColumnNames(myFile);

        // Helper vars
        std::string line;

        // Now read data, line by line and create a county info object
        while(std::getline(myFile, line)) {
            theData.push_back(readCSVLineHospital(line));
        }

        // Close file
        myFile.close();
    }

    return theData;
}
