#include "rating.h"

/* 
A class to represent a rating system that uses both words and numbers
(see CORGIS hospital data for an example)
Rating.Overall  Integer     Overall rating between 1 and 5 stars, with 5 stars being the highest rating; -1 represents no rating.
Rating.Mortality    String  Above, Same, Below, or Unknown comparison to national hospital mortality
Rating.Safety   String  Above, Same, Below, or Unknown comparison to national hospital safety 
*/
const string rating::getRating() const {
	//TODO implement
	return phrase;
}

double rating::getRatingNum() const{
	return aggregated;
}

void rating::setRatingNum(double input){
	aggregated = input;
	if (aggregated<0) phrase = "None";
	else if(aggregated>=3 and aggregated<5) phrase="Below";
	else if(aggregated>=5 and aggregated<7) phrase="Same";
	else if(aggregated>7) phrase="Above";
}


