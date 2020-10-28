#include "Video.h"
using namespace std;

#ifndef __MOVIE
#define __MOVIE
/*
Diego Reyna Reyes
A01657387
Project
Mexico City, 08/06/2020
Description:
Child class fo Video, it has a rating, a year fo release and a budget
*/
class Movie:public Video
{
    public:
        Movie(string data[5], int new_rating, int new_year, int new_budget);//Data has this info id,name,genre,initial_letter,length and rating for the movie is given, the year of release and the budget
        ~Movie();
        int getRating();//Rturns rating
        void setRating(int new_rating);//Set rating
        string toString();//Returns all information of the Movie
        string display();//Returns Title and rating only
    protected:
        int rating;
        int year;
        int budget;
};
#endif