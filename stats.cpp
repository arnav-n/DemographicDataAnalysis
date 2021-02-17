#include "stats.h"
#include <vector> 
#include <numeric>
#include <algorithm>
#include <cmath>
#include <iostream> 

using namespace std;

double stats::computeMean(vector<double> theNums){

	double sum = std::accumulate(theNums.begin(), theNums.end(), 0.0);
	return sum / theNums.size();
}

double stats::computePopMean(vector<double> theNums, int totPop){

	double sum = std::accumulate(theNums.begin(), theNums.end(), 0.0);
	return sum / totPop;
}


double stats::computeStdDevPop(std::vector<double> theNums) {

	double m = stats::computeMean(theNums);
	double accum = 0.0;
	std::for_each (std::begin(theNums), std::end(theNums), 
					[&](const double d) { accum += (d - m) * (d - m); }	
				  );

	return sqrt(accum / theNums.size());
}

double stats::computeStdDevSample(vector<double> theNums) {

	double m = stats::computeMean(theNums);
	double accum = 0.0;
	std::for_each (std::begin(theNums), std::end(theNums), 
					[&](const double d) { accum += (d - m) * (d - m); }	
				  );

	return sqrt(accum / (theNums.size()-1));

}


double stats::computeCorCoeff(std::vector<double> inX, std::vector <double> inY) {

	double sumX = std::accumulate(inX.begin(), inX.end(), 0.0);
	double sumY = std::accumulate(inY.begin(), inY.end(), 0.0);

	double iP = std::inner_product(inX.begin(), inX.end(), inY.begin(), 0);

	double sumSqX = std::inner_product(inX.begin(), inX.end(), inX.begin(), 0);
	double sumSqY = std::inner_product(inY.begin(), inY.end(), inY.begin(), 0);

	double n = inX.size();
	double corr = (n* iP - sumX*sumY)/
					sqrt((n*sumSqX - sumX*sumX)*(n*sumSqY - sumY*sumY));
	return corr;
}




