#ifndef STATS_H
#define STATS_H

#include <vector> 

/* tool for computing various statistic */
class stats {
 public:
	static double computeMean(std::vector<double> theNums);
	static double computePopMean(std::vector<double> theNums, int totPop);
	static double computeStdDevSample(std::vector<double> theNums);
	static double computeStdDevPop(std::vector<double> theNums);
	static double computeCorCoeff(std::vector<double> inX, std::vector <double> inY);
};
#endif