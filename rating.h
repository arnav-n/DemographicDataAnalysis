#ifndef RATING_H
#define RATING_H

#include <string>
#include<iostream>

using namespace std;

class rating {
  public:
    rating(){
        aggregated=-1;
        phrase = "None";
    }

    //constructor that takes in a number
    rating(double inRating)  {
        //TODO fill in
        aggregated = inRating;
        phrase = "";
    }

    //constructor that takes in a string
    rating(string inRating) {
        //TODO fill in
        phrase = inRating;
        //to do: depending on the rating, add a value to the aggregated score
        if(inRating=="Below")
            aggregated=3;
        else if (inRating=="Same")
            aggregated=6;
        else if (inRating=="Above")
            aggregated=9;
        else aggregated=-1;
    }

    //a method to return a string based on the current rating TODO complete
    const string getRating() const;
    double getRatingNum() const;

    friend std::ostream& operator<<(std::ostream &out, const rating &r) {
        // out<< r.aggregated << ", ";
        out << r.phrase;
        return out;
    }
    void setRatingNum(double input);

    friend void operator+=(rating &r, const rating &r2){
        r.setRatingNum(r.aggregated+r2.aggregated);
    }
    friend void operator/=(rating &r, double x){
        r.setRatingNum(r.aggregated/x);
    }
    friend void operator*=(rating &r, double x){
        r.setRatingNum(r.aggregated*x);
    }
    
     friend bool operator<(const rating &r, const rating &r2){
        return r.aggregated<r2.aggregated;
    }
    
    //TODO write operator overload


private:
     //TODO decide what data to represent
    double aggregated;
    string phrase;
};
#endif
