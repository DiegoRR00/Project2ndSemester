#include "Video.h"
using namespace std;
#ifndef __EPISODE
#define __EPISODE
/*
Diego Reyna Reyes
A01657387
Project
Mexico City, 08/06/2020
Description:
Child class fo Video, it has a rating, a year of release, a budget, a season number and an episode number
It has the operator + overloeaded twice, one for int and one for Episodes
*/
class Episode:public Video
{
    public:
        Episode(string data[5], int new_rating, int new_season, int new_episode_num);//Data has this info id,name,genre,initial_letter,length; rating for the episode, season number and episode number is given
        Episode(string data[5],int new_rating);//Constructor for operator
        ~Episode();
        int getSeason();//Returns season
        int getEpisodeNumber();//Returns episode_num
        void setEpisodeNumber(int new_episode_num);//Changes episode_num
        void setSeason(int new_season);//Changes season
        string toString();//Returns all info of the episode
        int getRating();//Returns rating
        void setRating(int new_rating);//Cahnges rating
        string display();//Returns the video title and it's rating
        Episode operator+(const Episode* another)//Adds the rating of two episodes
        {
            string data[5]={"0","0","0","0","0"};
            Episode result(data,this->rating+another->rating);
            return result;
        }
        int operator+(const int& another)//Adds the rating of two episodes and returns that value
        {
            int result=this->rating+another;
            return result;
        }
    protected:
        int season;
        int episode_num;
        int rating;
};
#endif