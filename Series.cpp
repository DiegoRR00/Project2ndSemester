#include "Series.h"
/*
Diego Reyna Reyes
A01657387
Project
Mexico City, 10/06/2020
*/
bool compareStrings(string string_1, string string_2, double searched_percentage)//This compares to string and if they have a percentage of similarity bigger than the one provided, it will return true
{
    /*
    This is not meant to be a very complex comparison.
    It's for 2 things.
    1. The user doesn't have to capitalize each letter in the title when he/she types it
    2. When I press enter, it's pretty common I press "}" at the same time, so my entry is "Title}", with this, at least that would count as the same, it also works if you make a typo like "Titlw" instead of "Title", basically is Anti-Diego protection(✿◠‿◠)
    Sadly it doesn't work with small words, the smallest one hast to be of at least 5 characters
    */
    stringstream s_1(string_1);//Change it to stringstream to count the words
    stringstream s_2(string_2);//Change it to stringstream to count the words
    int words_in_1=0, words_in_2=0;//Ints to store the number of words
    string word;//Variable to store the words in the get line
    while (getline(s_1,word,' '))//For every word in 1
    {
        words_in_1++;//Add it to the counter
    }
    while (getline(s_2,word,' '))//For every word in 2
    {
        words_in_2++;//Add it to the counter
    }
    if (words_in_1==words_in_2)//If they have the same number of words
    {
        int first_size=string_1.size();//Variable to store the number of characters in the first string
        int second_size=string_2.size();//Variable to store the number of characters in the second string
        int biggest,smallest;//Variable to store the values of the biggest number of characters and the smallest
        if (first_size>=second_size)//If the first one is bigger or they're of the same size
        {
            biggest=first_size;//Set the variables with the correct number
            smallest=second_size;//Set the variables with the correct number
        }
        else//If the second one is biggest
        {
            biggest=second_size;//Set the variable with the correct number
            smallest=first_size;//Set the variable with the correct number
        }
        
        if(string_2.size()==string_1.size() || biggest-1==smallest)//If they're the same size or the biggest is only one character larger than the smallest
        {
            double num_repeated=0;//Variable for the number of repeated characters
            for (int l=0;l<biggest;l++)//For each character in the biggest
            {
                if (toupper(string_2[l])==toupper(string_1[l]))//If the capitalized character of both is the same
                {
                    num_repeated++;//Add to the number of repeated
                }
            }
            if (num_repeated/biggest>=searched_percentage)//If the number of repeated between the biggest is higher or equal to the seacrhed percentage
            {
                return true;
            }
            else//If not
            {
                return false;
            }
            
        }
        else//If the size are not similar
        {
            return false;
        }
        
        
    }
    else//If they dont have the same number of words
    {
        return false;
    }
}
double getSimilarity(string string_1, string string_2)//Returns the similarity between 2 string which it receives
{
    int first_size=string_1.size();//Variable to store the number of characters in the first string
    int second_size=string_2.size();//Variable to store the number of characters in the second string
    int biggest,smallest;//Variable to store the values of the biggest number of characters and the smallest
    if (first_size>=second_size)//If the first one is bigger or they're of the same size
    {
        biggest=first_size;//Set the variables with the correct number
        smallest=second_size;//Set the variables with the correct number
    }
    else//If the second one is biggest
    {
        biggest=second_size;//Set the variable with the correct number
        smallest=first_size;//Set the variable with the correct number
    }    
    double num_repeated=0;
    for (int l=0;l<biggest;l++)
    {
        if (toupper(string_2[l])==toupper(string_1[l]))//If the capitalized character of both is the same
        {
            num_repeated++;//Add to the number of repeated
        }
    }
    double similarity=num_repeated/biggest;//Divide the number of the same letters to the biggest string
    return similarity;//Return the similarity
}
Series::Series(int new_num_seasons, int new_num_episodes, string new_name, string episode_names[], string new_genre, double episode_length[], int new_rating[],string new_ID, int new_year, int new_budget)//Receives the number of season of the series, the number of episodes per season, series name, a list with all episodes names, the genre of the series, an array with the length of each episode, the ID of the series, the realese year and the budget
{
    //Set variables
    num_episodes=new_num_episodes;
    num_seasons=new_num_seasons;
    name=new_name;
    string initial_letter_series(1,name[0]);
    initial_letter=initial_letter_series;
    genre=new_genre;
    budget=new_budget;
    year=new_year;
    general_rating=0;//The general rating will be 0
    int counter=0;//Counts the number of episodes
    episodes=new Episode**[num_seasons];//Declare my array with the number of lines equal to the number of season
    for (int s=0;s<num_seasons;s++)//For each season
    {
        episodes[s]=new Episode*[num_episodes];//Each season has the number of episodes
        for (int e=0;e<num_episodes;e++)//Fpr each episode
        {
            string data[5];//Create a string array for the data of each episode
            string first_letter(1,episode_names[counter][0]);//Convert the fisrt letter of the name from char to string
            data[0]=new_ID+"S"+to_string(s+1)+"E"+to_string(e+1);//ID
            data[1]=episode_names[counter];//Name
            data[2]=genre;//Genre
            data[3]=first_letter;//Initial letter
            data[4]=to_string(episode_length[counter]);///length
            episodes[s][e]=new Episode(data,new_rating[counter],s+1,e+1);//Create a new episode
            counter++;//Get next episode data
        }
    }
    for (int s=0;s<num_seasons;s++)//For each season
    {
        for (int e=0;e<num_episodes;e++)//For each episode
        {
            general_rating=(*episodes[s][e])+general_rating;//Add the rating of each episode
        }
    }
    general_rating=general_rating/(num_episodes*num_seasons);//The rating is divided between the number of episodes
}
Series::~Series()
{

}
string Series::display()//Returns all the episodes and their rating
{
    string msg;
    msg="";
    for (int s=0;s<num_seasons;s++)//For each season
    {
        msg+="\n\tSeason "+to_string(s+1)+"\n";//Add the season number
        for (int e=0;e<num_episodes;e++)//For each episode
        {
            //add number_episode. Episode name  Rating: episode rating
            msg+="\t\t"+to_string(e+1)+". "+episodes[s][e]->getName()+"\n\t\t\tRating: "+to_string(episodes[s][e]->getRating())+"\n";
        }
    }
    return msg;
}
string Series::displayGeneralInfo()//Returns the name and general rating
{
    string msg="Title:\t"+name;//Add title of series
    msg+="\nRating:\t"+to_string(general_rating);//add general rating
    return msg;
}
string Series::getInitialLetter()//Returns the initial letter
{
    return initial_letter;
}
string Series::displayAllVideos()//Returns a string with all videos information, each one as an individual video
{
    string msg="";//Create msg
    for (int s=0;s<num_seasons;s++)//For each season
    {
        for (int e=0;e<num_episodes;e++)//For each episode
        {
            msg+=episodes[s][e]->display()+"\n";//Add name and rating
        }
    }
    return msg;
}
string Series::toString()//Returns a string with the series information and each episodes info
{
    string msg="Title:\t\t\t"+name+"\n";//Add title
    msg+="Rating:\t\t\t"+to_string(general_rating)+"\n";//Add general rating
    msg+="Number of seasons:\t"+to_string(num_seasons)+"\n";//Add number of seasons
    msg+="Number of episodes:\t"+to_string(num_seasons*num_episodes)+"\n";//Add number of episodes
    msg+="Release yer:\t\t"+to_string(year)+"\n";
    msg+="Budget: \t\t$"+to_string(budget)+"\n";
    msg+="Episodes info:\n\n";//Add episode info
    for (int s=0;s<num_seasons;s++)//For each season
    {
        msg+="Season "+to_string(s+1)+"\n";//Add season number
        for (int e=0;e<num_episodes;e++)//For each episode inside a season
        {
            msg+=episodes[s][e]->toString()+"\n\n";//Add it's info
        }
        if (s!=num_seasons-1)//If it's not the last one
        {
            msg+="\n\n";//Separate seasons
        }
    }
    return msg;//return
}
string Series::getGenre()//Returns the genre of the series
{
    return genre;
}
string Series::videosToString()//Returns the information of the videos only, not the series

{
    string msg="";
    for (int s=0;s<num_seasons;s++)//For each season
    {
        for (int e=0;e<num_episodes;e++)//For each episode inside a season
        {
            msg+=episodes[s][e]->toString()+"Release date:\t"+to_string(year)+"\nBudget:\t\t$"+to_string(budget)+"\n\n";//Add it's info
        }
    }
    return msg;//return
}
string Series::videosInRating(int searched_rating)//Returs the information of the videos that have an specific rating
{
    string msg="";
    for (int s=0;s<num_seasons;s++)//For each season
    {
        for (int e=0;e<num_episodes;e++)//For each episode inside a season
        {
            if (episodes[s][e]->getRating()==searched_rating)//If it has the rating
            {
                msg+=episodes[s][e]->toString()+"Release date:\t"+to_string(year)+"\nBudget:\t\t$"+to_string(budget)+"\n\n\n";//Add it's info
            }
        }
    }
    return msg;//return
}
void Series::setRating(int new_rating)//Vhanges the rating of the series
{
    general_rating=new_rating;
}
void Series::rateEpisode()//Ask for the season and episode number, or the name, asks for a new rating, changes it and recalculates the series rating
{
    bool valid_input=true;//While conditional
    string input;
    while (valid_input)
    {
        //Ask if the user wants to search by name or number
        cout<<"If you want to select the episode using it's seasons number and it's episode number select 1\nIf you want to select the episode using it's name select 2"<<endl;
        cin>>input;//Receive input
        if (input=="1")//If they want to search by number
        {
            valid_input=false;//End while
            //Select season and episode
            bool valid_season=true;//While conditional
            
            while (valid_season)
            {
                //Notify the user how many seasons there are
                cout<<"This series has "<<num_seasons<<" seasons, select the one in which your episode is in"<<endl;
                cin>>input;//receive his input
                int selected_season=0;//Season of the episode
                for (int s=1;s<num_seasons+1;s++)//For each valid season number
                {
                    if (input==to_string(s))//If it's the same
                    {
                        selected_season=s;//Save the season number
                        s=num_seasons+2;//End for
                    }
                }
                if (selected_season!=0)//If theres a season selected
                {
                    bool valid_episode=true;//While conditional
                    int selected_episode=0;//Variable for the episode slected
                    while (valid_episode)
                    {
                        //Notify the number of episodes
                        cout<<"This season has "<<num_episodes<<" episodes, select the episode number of the video you want to rate"<<endl;
                        cin>>input;//Receive input
                        for (int e=1;e<num_episodes+1;e++)//For each valid season number
                        {
                            if (input==to_string(e))//If it's the same
                            {
                                selected_episode=e;//Save the season number
                                e=num_episodes+2;//End for
                            }
                        }
                        if (selected_episode!=0)//If there was a selected episode
                        {
                            bool valid_rating=true;//While conditional
                            while (valid_rating)
                            {
                                bool is_rating=false;
                                //Show the episode and ask the user to rate it, if he made a mistake, he can choose again
                                cout<<"The selected episode is "<<episodes[selected_season-1][selected_episode-1]->getName()<<"\nIf you want to rate in write the rating now, if not, press C to select again"<<endl;
                                cin>>input;//Receive input
                                for (int r=1;r<6;r++)
                                {
                                    if (input==to_string(r))
                                    {
                                        is_rating=true;//Enable the rating
                                        valid_rating=false;//End while
                                    }
                                }
                                if (is_rating)
                                {
                                    valid_season=false;//End the outer while
                                    valid_episode=false;//End while
                                    episodes[selected_season-1][selected_episode-1]->setRating(stoi(input));//Change the rating
                                    cout<<"The video has been rated"<<endl;
                                    string megasode_data[5]={"0","0","0","0","0"};//Data to create the temporal megasode
                                    Episode megasode(megasode_data,0);//Megasode will store the sum of all the ratings as it's own rating, hence the megasode
                                    //Recalculate the series rating
                                    for (int s=0;s<num_seasons;s++)//For each season
                                    {
                                        for (int e=0;e<num_episodes;e++)//For each episode
                                        {
                                            megasode=megasode+episodes[s][e];//redifine megasode as the sum of the past episodes rating +this episodes rating
                                        }
                                    }
                                    general_rating=megasode.getRating()/(num_episodes*num_seasons);//Get the rating of the megasode and divide it by the number of episodes in the whole series
                                    megasode.~Episode();//Delete the megasode
                                    cout<<"The new rating of the series is "<<general_rating<<endl;//Notify the user the change
                                }
                                else if (input=="C")
                                {
                                    valid_rating=false;
                                    valid_episode=false;
                                    cout<<"Choose again"<<endl;//This will return the user to the select season while
                                }
                                else
                                {
                                    cout<<"Invalid input, try again"<<endl;//Notify the user
                                }
                                
                            }
                        }
                        else
                        {
                            cout<<"Invalid input, try again"<<endl;//Notify the user
                        }
                        
                    }
                }
                else
                {
                    cout<<"Invalid input, try again"<<endl;//Notify the user
                }


            }
        }
        else if (input=="2")
        {
            valid_input=false;//End while
            bool valid_name=true;//While conditional
            int selected_season=0;//Number of season
            int selected_episode=0;//Number of episode
            double similarity_percentage=0.8;//Percentage searched between user input and the name
            cout<<"This are the available episodes:"<<endl;//Show the names of the episodes
            for (int s=0;s<num_seasons;s++)//For each season
            {
                cout<<"Season "<<s+1<<endl;//Pritn the season number
                for (int e=0;e<num_episodes;e++)//For each episode
                {
                    cout<<"\t"<<e+1<<". "<<episodes[s][e]->getName()<<endl;//Print the number of episode and the title
                }
                cout<<endl;//Add a space between seasons
            }
            getline(cin,input);//Getline, I need to get it here because the first time i use it it returns ""
            while(valid_name)
            {
                //Select name
                cout<<"Write the name of the episode:"<<endl;
                getline(cin,input);//I have to use getline instead of cin because if a write a two word title, it'll take the first word as an input and the second one as another different one, if use getline, where the source is cin and it puts it ininput, i can multiword titles
                bool is_an_episode=false;//IF true, it means the name is the name of an espisode
                vector <string> possible_names;//I store all possible names, I need to do this becauuse theres cases where are names that are two similar like Civil war part 1 and Civil war part 2
                vector <int> possible_seasons;//I store all possible season number
                vector <int> possible_episodes;//I store all possible episode number
                for (int s=0;s<num_seasons;s++)//Check each season
                {
                    for (int e=0;e<num_episodes;e++)//Check each episode
                    {
                        if (compareStrings(input,episodes[s][e]->getName(),similarity_percentage))//I call the funtion to find if they are similar enough
                        {
                            is_an_episode=true;//Eneable the change rating sections
                            possible_seasons.push_back(s);//Save the season
                            possible_episodes.push_back(e);//Save the episode
                            possible_names.push_back(episodes[s][e]->getName());//Save the name
                        }
                    }
                }
                if (is_an_episode)//If the name is the name of an episode
                {
                    if (possible_names.size()!=1)//If theres more than one possible episode
                    {
                        int best_coincidence_index=0,counter=0;//Save the index of the best coincidence and the counter
                        double best_similarity=0;//Store the best similarity between the input and all the episodes names
                        for (string option:possible_names)//For each string in possible names
                        {
                            if (getSimilarity(input,option)>best_similarity)//If the similarity is biggest than the best one
                            {
                                best_similarity=getSimilarity(input,option);//Set the new best similarity
                                best_coincidence_index=counter;//Set the index
                            }
                            counter++;//Upsate counter
                        }
                        selected_season=possible_seasons[best_coincidence_index];//Set the selected season
                        selected_episode=possible_episodes[best_coincidence_index];//Set the selected episode
                    }
                    else//If theres only one
                    {
                        selected_episode=possible_episodes[0];//Set the selected episode
                        selected_season=possible_seasons[0];//Set the selected episode
                    }
                    cout<<"Episode selected: "<<episodes[selected_season][selected_episode]->getName()<<endl;//Show the selected episode
                    bool valid_rating=true;//While conditional
                    valid_name=false;
                    while (valid_rating)
                    {
                        bool is_rating=false;//Store if i have a valid rating
                        cout<<"Write the rating you want to give this episode:"<<endl;//Ask for rating
                        cin>>input;//receive rating
                        for (int r=1;r<6;r++)//For each posible rating
                        {
                            if (input==to_string(r))//if it's the same
                            {
                                is_rating=true;//I have a valid rating
                                r=7;//End for
                            }
                        }
                        if (is_rating)//If i have a valir rating
                        {
                            valid_rating=false;//End while
                            episodes[selected_season][selected_episode]->setRating(stoi(input));//Chnage the rating
                            cout<<"The video has been rated"<<endl;//Notify the user
                            string megasode_data[5]={"0","0","0","0","0"};//Data to create the temporal megasode
                            Episode megasode(megasode_data,0);//Megasode will store the sum of all the ratings as it's own rating, hence the megasode
                            //Recalculate the series rating
                            for (int s=0;s<num_seasons;s++)//For each season
                            {
                                for (int e=0;e<num_episodes;e++)//For each episode
                                {
                                    megasode=megasode+episodes[s][e];//redifine megasode as the sum of the past episodes rating +this episodes rating
                                }
                            }
                            general_rating=megasode.getRating()/(num_episodes*num_seasons);//Get the rating of the megasode and divide it by the number of episodes in the whole series
                            megasode.~Episode();//Delete the megasode
                            cout<<"The new rating of the series is "<<general_rating<<endl;//Notify the user the change
                        }
                        else
                        {
                            cout<<"Invalid input, try again"<<endl;//Notify the user
                        }
                        
                    }
                    
                }
                else
                {
                    cout<<"Invalid input, try again"<<endl;//Notify the user
                }
                
            }
        }
        else
        {
            cout<<"Invalid input, try again"<<endl;//Notify the user
        }
        
    }
    
}
Video* Series::getEpisode(int season, int episode)//Returns the pointer to the episode with season and episode
{
    string data[5];//Create and array for the information for the episode
    data[0]=episodes[season][episode]->getID();//Add ID
    data[1]=episodes[season][episode]->getName();//Add name
    data[2]=episodes[season][episode]->getGenre();//Add genre
    data[3]=episodes[season][episode]->getInitialLetter();//Add initial_letter
    data[4]=to_string(episodes[season][episode]->getLength());//Add length
    Video* temporary=new Episode(data, episodes[season][episode]->getRating(),season+1,episode+1);//Create using the second contructor
    return temporary;
}
int Series::getSeason()//Returns the number of seasons
{
    return num_seasons;
}
int Series::getEpisodes()//returns the number of episodes per season
{
    return num_episodes;
}