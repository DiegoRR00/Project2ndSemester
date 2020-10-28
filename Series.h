#include "Episode.h"
#include <string>
#include <sstream>
#include <vector>
using namespace std;
#ifndef __SERIES
#define __SERIES
/*
Diego Reyna Reyes
A01657387
Project
Mexico City, 08/06/2020
Description:
It has a list of series which administers, it can print them, seacrh them by rating or return them as Videos
*/
class Series
{
    public:
        Series(int new_num_seasons, int new_num_episodes, string new_name, string episode_names[], string new_genre, double episode_length[], int new_rating[],string new_ID, int new_year, int new_budget);//Receives the number of season of the series, the number of episodes per season, series name, a list with all episodes names, the genre of the series, an array with the length of each episode and the ID of the series
        ~Series();
        string display();//Returns all the episodes and their rating
        string displayGeneralInfo();//Returns the name and general rating
        string getInitialLetter();//Returns the initial letter
        string displayAllVideos();//Returns a string with all videos information, each one as an individual video
        string toString();//Returns a string with the series information and each episodes info
        string getGenre();//Returns the genre of the series
        string videosToString();//Returns the information of the videos only, not the series
        string videosInRating(int searched_rating);//Returs the information of the videos that have an specific rating
        void setRating(int new_rating);//Vhanges the rating of the series
        void rateEpisode();//Ask for the season and episode number, or the name, asks for a new rating, changes it and recalculates the series rating
        Video* getEpisode(int season, int episode);//Returns the pointer to the episode with season and episode
        int getSeason();//Returns the number of seasons
        int getEpisodes();//returns the number of episodes per season
    protected:
        Episode*** episodes;//Where i store all episodes
        int num_seasons;//Number of seasons in the series
        int num_episodes;//Number of episodes per season
        string name;//Name of the series
        int general_rating;//Rating for the overall series
        string genre;
        string initial_letter;
        int year;
        int budget;
};

#endif