#include "Movie.h"
/*
Diego Reyna Reyes
A01657387
Project
Mexico City, 08/06/2020
*/
Movie::Movie(string data[5],int new_rating, int new_year, int new_budget):Video(data)//Data has this info id,name,genre,initial_letter,length and rating for the movie is given, the year of release and the budget
{
    rating=new_rating;
    year=new_year;
    budget=new_budget;
}
Movie::~Movie()
{

}
int Movie::getRating()//Rturns rating
{
    return rating;
}
void Movie::setRating(int new_rating)//Set rating
{
    rating=new_rating;
}
string Movie::toString()//Returns all information of the Movie
{
    string msg;
    msg="Title:\t\t"+name+"\n";
    msg+="ID:\t\t"+ID+"\n";
    msg+="Genre\t\t"+genre+"\n";
    msg+="Lentgh:\t\t"+to_string(length)+" min\n";
    msg+="Release date:\t"+to_string(year)+"\n";
    msg+="Budget:\t\t$"+to_string(budget);
    return msg;
}
string Movie::display()//Returns Title and rating only
{
    string msg;
    msg="Title:\t"+name+"\n";
    msg+="Rating:\t"+to_string(rating);
    return msg;
}