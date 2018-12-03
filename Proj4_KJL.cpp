/*
Keith Livingston
COSC 120
Professor Bardzell
Project 4
This program will take in two different text files and output the information to an output file. The file names are tropical.txt and hurricane.txt.
The tropical file holds a list of tropical storm ID's in ascending order. The hurricane list holds the name, ID, life in days, 5 wind speeds, 2 rain fall totals
and the amount of tornadoes spawned for each storm in the list. There is a max of 200 storms allowed in the list. The program will take in the information
from the hurricanes.txt file and manipulate the information in different ways. First it will print all the storms to the output file called list.txt.
This will show the storms name, ID, life in days, date, average wind speed, average rain fall, tornadoes spawned, and storm level. The program
will also print the total number of records, inputed through the file, the amount of the records that were hurricanes and the number of tropical
storms in the file. The program will then print the hurricanes based on level. First the level 1's then level 2's and so on. Each level will also have the
total number of hurricanes in that level, average life span in days, average rain fall, average tornadoes, and wind speed for all the hurricanes in that
particular level. Once all 5 levels have been printed the program will print out the exception reports showing if any hurricane.txt in the list had the same ID
as a storm in the tropical.txt list or if the storm level was 0. Finally a summary is printed which tells the wind average for all hurricanes, the highest and lowest
wind average,the standard deviation of the wind speed and the number of hurricanes recorded in each level.
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <cctype>
#include <string.h>

using namespace std;

struct hurricane
{
    char name[11];                                          //Lines 30-41 are the variables being declared in my structure called hurricane.
    int ID;
    int life;
    int date;
    int wind;
    float rain;
    int tornadoe;
    int totalWind = 0;
    float totalRain = 0;
    int windAverage = 0;
    float rainAverage = 0;
    int level = 0;
};

    ifstream tropical_file;                             //ifstream and ofstream will set the names used in the program to open and close
    ifstream hurricane_file;                            //my input and output files to be used in the program.
    ofstream output_file;

    struct hurricane hurrArray[200];                    //This an array that will hold the various different hurricanes in each element of the array.
    int tropicalArray[200];                             //TropicalArray is an array that holds all of the tropical ID's from tropical.txt.
    int storm_Level(int);

    void header();                                          //lines 52-60 are all different function prototypes used throughout the program,
    void sortLevel(hurricane[], int, int);                  //for more information on how these work goto the function header.
    void exceptionReport1(int [], hurricane[], int, int);
    void exceptionReport2(hurricane[], int);
    void hurrWindAvg(float);
    void highestWind(hurricane[], int);
    void lowestWind(hurricane[], int);
    void hurricaneCount(hurricane[], int);
    void StandardDeviation(hurricane[], float, int);

int main()
{
    int count = 0;                                                //lines 64-70 are the different variables needed to compute the calculations within
    float records = 0;                                            //the program.
    float totalHurricanes = 0;
    int totalTropicals = 0;
    int tropList = 0;
    float avgHurricaneWind = 0;
    float hurrTotalWind = 0;

    tropical_file.open("tropical.txt");                            //lines 72-74 open the txt files need for the program. Two input and one output files
    hurricane_file.open("hurricane.txt");
    output_file.open("list.txt");

    output_file << endl << "                                              STORM SUMMARY SHEET" << endl << endl;         //These two lines print the header
    header();                                                                                                           //Call to the function header.

    while (tropical_file.good())                                    //This checks to see if there is information still in tropical.txt and takes in information
    {                                                               //until there is not more data in the file. The information is being stored in the tropical array we created
        tropical_file >> tropicalArray[tropList];
        tropList++;
    }

    while (hurricane_file.good())                                   //This checks to see if there is still information in the hurricane.txt.
    {

        hurricane h1;                                               //Creates hurricane structure h1.

        hurricane_file.get(h1.name , 11);                           //lines 90-114 take in and calculate the information needed for the storm sheet summary
        hurricane_file >> h1.ID;
        hurricane_file >> h1.life;
        hurricane_file >> h1.date;

            for(int i = 0; i < 5; i++)                              //This for loop computes the average of the 5 wind speeds from the input file
            {
                h1.wind = 0;
                hurricane_file >> h1.wind;
                h1.totalWind = h1.totalWind + h1.wind;
            }
            h1.windAverage = h1.totalWind / 5;

            h1.level = storm_Level(h1.windAverage);

            for(int j = 0; j < 2; j++)                               //This for loop computes the average of the rain fall from the input file
            {
                h1.rain = 0;
                hurricane_file >> h1.rain;
                h1.totalRain = h1.totalRain + h1.rain;
            }
            h1.rainAverage = h1.totalRain / 2;
            h1.totalRain = 0;

        hurricane_file >> h1.tornadoe;

        if(h1.level > 0)                                            //This if will check to see if the storm is a hurricane or tropical storm and increment
        {                                                           //one or the other.
            totalHurricanes++;
        } else if(h1.level == 0)
        {
            totalTropicals++;
        }

        output_file << h1.name << "     \t";                        //lines 124-131 print the variables for a single hurricane to the output file.
        output_file << setw(10) << h1.ID << " ";
        output_file << setw(10) << h1.life << " ";
        output_file << setw(15) << h1.date << " ";
        output_file << setw(15) << h1.windAverage << " ";
        output_file << setw(15) << h1.rainAverage << " ";
        output_file << setw(15) << h1.tornadoe << " ";
        output_file << setw(15) << h1.level << " " << endl;

        hurrArray[count] = h1;                                      //This sets the hurricane being brought in to the correct position in the array for later use.
        count++;
        records++;

        hurrTotalWind = hurrTotalWind + h1.wind;

        hurricane_file.ignore(300, '\n');                           //This is to make sure you only pull in what is needed for each hurricane and not too much.

    }

    output_file << endl << "Total number of records = " << records << endl;                 //lines 143-145 print to the output file the information needed
    output_file << "Total number of hurricanes = " << totalHurricanes << endl;              //for the storm summary sheet
    output_file << "Total number of tropical storms = " << totalTropicals << endl << endl;


    sortLevel(hurrArray, count, 1);                                                         //lines 148-152 are all calls for the 5 levels of hurricanes.
    sortLevel(hurrArray, count, 2);                                                         //each call creates a new level for each of the 5 levels.
    sortLevel(hurrArray, count, 3);
    sortLevel(hurrArray, count, 4);
    sortLevel(hurrArray, count, 5);

    exceptionReport1(tropicalArray, hurrArray, tropList, records);                      //This calls the exception reports
    exceptionReport2(hurrArray, records);

    avgHurricaneWind = hurrTotalWind / (records);                               //These lines compute the wind average for all hurricanes entered into the list
    hurrWindAvg(avgHurricaneWind);

    highestWind(hurrArray, records);                                        //This calls two functions to compute the lowest and the highest average wind speeds
    lowestWind(hurrArray, records);

    StandardDeviation(hurrArray, avgHurricaneWind, records);                //This call calculates the standard deviation.

    hurricaneCount(hurrArray, records);                                 //This call calculates the number of hurricanes in each level.


    tropical_file.close();                              //lines 168-170 close the program files before the program terminates.
    hurricane_file.close();
    output_file.close();
}

void header()                                           //The header function just prints out the header for storm summary sheet
{
    output_file << "Name                  ID           Life          Date         Average           Average          Tornadoes         Storm" << endl;
    output_file << "                                  in days                   wind speed         rain fall          spawned          level" << endl << endl;
}

int storm_Level(int windAverage)                        //lines 179- 215: storm_Level computes the storm level of each hurricane sent to it and returns the storm level.
{
    int storm;

    if (windAverage < 75)
    {
        storm = 0;
    }

    if (windAverage >= 75 && windAverage < 95)
    {
        storm = 1;
    }

    if (windAverage >= 95 && windAverage < 110)
    {
        storm = 2;
    }

    if (windAverage >= 110 && windAverage < 130)
    {
        storm = 3;
    }

    if (windAverage >= 130 && windAverage < 155)
    {
        storm = 4;
    }

    if (windAverage >= 155)
    {
        storm = 5;
    }

    return storm;
}

void sortLevel(hurricane hurrArray[], int count, int num)                           //This is the function that computes and prints the different levels to the output file
{
    output_file << "                                          Hurricane Level " << num << endl << endl;
    output_file << "Name                  ID           Life          Date         Average           Average          Tornadoes" << endl;
    output_file << "                                  in days                   wind speed         rain fall          spawned" << endl << endl;

    int runs = count - 1;                                       //lines 222-231 are the variables needed to compute and print the variables needed for levels 1-5
    float hurrNum = 0;
    float totalLife = 0;
    float totalRain = 0;
    float totalTorn = 0;
    float totalWind = 0;
    float avgWind = 0;
    float avgTorn = 0;
    float avgRain =0;
    float avgLife = 0;

    for(int i = 0; i <= runs; runs--)                           //This for loop will run through the array of hurricanes and check to see if the storm level
    {                                                           // from the storm being looked at is the same as the num being brought in. num is the storm
        if (hurrArray[runs].level == num)                       //level being looked at in whichever pass of the function you are in.
        {
        output_file << hurrArray[runs].name << "     \t";                   //lines 237-243 will print out the variables needed for the hurricane level to the output file
        output_file << setw(10) << hurrArray[runs].ID << " ";
        output_file << setw(10) << hurrArray[runs].life << " ";
        output_file << setw(15) << hurrArray[runs].date << " ";
        output_file << setw(15) << hurrArray[runs].windAverage << " ";
        output_file << setw(15) << hurrArray[runs].rainAverage << " ";
        output_file << setw(15) << hurrArray[runs].tornadoe << " " << endl;

        totalLife = totalLife + hurrArray[runs].life;                     //lines 245-249 will compute the various calculations needed in the output file.
        totalRain = totalRain + hurrArray[runs].rainAverage;
        totalTorn = totalTorn + hurrArray[runs].tornadoe;
        totalWind = totalWind + hurrArray[runs].windAverage;
        hurrNum++;
        }
    }

    avgLife = totalLife / hurrNum;                              //lines 253-256 will compute the averages for the storm life, rainfall, tornadoes, and wind speed.
    avgRain = totalRain / hurrNum;
    avgTorn = totalTorn / hurrNum;
    avgWind = totalWind / hurrNum;

    output_file << endl << endl << "Total number of Level " << num << " hurricanes is " << setprecision (4) << hurrNum << "." << endl;              //lines 258-262 will print out the
    output_file << "Average life span in days of level " << num << " hurricanes is " << setprecision (4) << avgLife << "." << endl;                 //bottom portion of each hurricane level.
    output_file << "Average rain fall for Level " << num << " hurricanes is " << setprecision (4) << avgRain << "." << endl;
    output_file << "Average tornadoes spawned for level " << num << " hurricanes is " << setprecision (4) << avgTorn << "." << endl;
    output_file << "Average wind speed for level " << num << " hurricanes is " << setprecision (4) << avgWind << "." << endl << endl << endl;

}

void exceptionReport1(int tropicalArray[], hurricane hurrArray[], int tropList, int records)        //This function with print the exception report 1 to the output file
{
    output_file << "                        Exception Report 1 " << endl << endl;                                       //These lines print the header
    output_file << "The Following Tropical Storms were not listed in the Tropical Storm data list." << endl << endl;
    output_file << "Name                   ID" << endl << endl;

    for(int i = 0; i < tropList; i++)                                               //lines 272-284 are a nested for loop that will compare each ID number from
    {                                                                               //from the tropical list to the ID number of the hurricanes. If there is a match
        for(int j = 0; j < records; j++)                                            //the program will send the hurricane to the output file.
        {
            if (tropicalArray[i] == hurrArray[j].ID)
            {
                output_file << hurrArray[j].name << "     \t";
                output_file << setw(10) << hurrArray[j].ID << " " << endl;
            }
        }
    }
    output_file << endl;
}

void exceptionReport2(hurricane hurrArray[], int records)                       //This function will compute and send exception report 2 to the output file.
{
    output_file << "                        Exception Report 2 " << endl << endl;                                          //These print the header.
    output_file << "The Following Tropical Storms were not listed in the Tropical Storm data list." << endl << endl;
    output_file << "Name                   ID" << endl << endl;

    for(int i = 0; i < records; i++)                                             //lines 292-300 will check to see if the storm level in each hurricane is 0
    {                                                                           //if it does equal 0 that hurricane will be output to the output file in exception report 2
        if(hurrArray[i].level == 0)
        {
        output_file << hurrArray[i].name << "     \t";
        output_file << setw(10) << hurrArray[i].ID << " " << endl;
        }
    }
    output_file << endl;
}

void hurrWindAvg(float avgHurricanesWind)                                   //This function prints the average wind speed of all hurricanes to the summary statistics.
{
    output_file << "Summary Statistics" << endl << endl;
    output_file << "Wind average of all hurricanes \t" << avgHurricanesWind << endl;

}

void highestWind(hurricane hurrArray[], int records)            //lines 310-321 are the function that computes the highest wind average in the array by setting one
{                                                               // of the elements equal to the lowest variable and comparing them to that.
    int highest = hurrArray[records - 1].windAverage;

    for(int i = 0; i < records; i++)
    {
        if(hurrArray[i].windAverage > highest)
        {
            highest = hurrArray[i].windAverage;
        }
    }
    output_file << "Highest wind average    \t" << highest << endl;
}

void lowestWind(hurricane hurrArray[], int records)             //lines 326-339 will compute the lowest wind average in the array of hurricanes
{                                                               //and print that out in the summary statistics the same was it does for the highest.
    int place = records - 1;                                    //the only difference is that if the lowest is lower then 75, the lowest is set to 75.
    int lowest = hurrArray[place].windAverage;

    for(int i = 0; i <= records; i++)
    {
        if(hurrArray[i].windAverage < lowest)
        {
            lowest = hurrArray[i].windAverage;

        }if(hurrArray[i].windAverage <= 75)
        {
            lowest = 75;
        }
    }
    output_file << "Lowest wind average     \t" << lowest << endl;
}

void hurricaneCount(hurricane hurrArray[], int records)                         //lines 343-377 is the function that computes how many of each hurricane are
{                                                                               //in each level and outputs them to the output file.
    int level1 = 0;
    int level2 = 0;
    int level3 = 0;
    int level4 = 0;
    int level5 = 0;

    output_file << "Number of Hurricanes in each level" << endl << endl;

    for(int i = 0; i < records; i++)
    {
        if(hurrArray[i].level == 1)
        {
            level1++;
        }else if(hurrArray[i].level == 2)
        {
            level2++;
        }else if (hurrArray[i].level == 3)
        {
            level3++;
        }else if (hurrArray[i].level == 4)
        {
            level4++;
        }else if (hurrArray[i].level == 5)
        {
            level5++;
        }
    }
    output_file << "level   1   \t" << level1 << endl;
    output_file << "level   2   \t" << level2 << endl;
    output_file << "level   3   \t" << level3 << endl;
    output_file << "level   4   \t" << level4 << endl;
    output_file << "level   5   \t" << level5 << endl;
}

void StandardDeviation(hurricane hurrArray[], float avgWindSpeed, int records)        //This last function computes the standard deviation of the
{                                                                                     //average wind speeds for all the hurricanes and sends it to
    float speedAvg = 0;                                                               //the output file.
    float speedTotal = 0;
    float stdDev = 0;
    for(int i = 0; i < records; i++)
    {
        speedAvg = (hurrArray[i].windAverage - avgWindSpeed);
        speedTotal = speedTotal + (speedAvg * speedAvg);
    }
    stdDev = speedTotal / records;
    stdDev = sqrt(stdDev);
    output_file << "Standard deviation      \t" << stdDev << endl << endl;

}
