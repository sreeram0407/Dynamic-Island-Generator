/*
Author: Sreeram Kondapalli
Date: 11/05/2022
Description: The aim of this project is to understand dynamic array
allocation by creating dynamic arrays and performing algorithms on them.
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <string.h>
#include "termcolor.hpp"
using namespace std;

int** makeParticleMap(int width, int height,  int windowX, int windowY, int radius, int numParticles, int maxLife);
void polishedParticleMap(int width, int height, int** map, int waterline);
int findMax(int** map, int width, int height);
int* movement(int windowX, int windowY);
bool moveExists(int** map, int width, int height, int windowX, int windowY);
void normalizeMap(int** map, int width, int height, int maxVal);
double frand();

//forward declaring all the functions
int main(int argc, char** argv)
{
    int seed;
    if(argc == 3 && (strcmp(argv[1], "-s") == 0) && (atoi(argv[2]) != 0)){
        seed = atoi(argv[2]);
        srand(seed);
    }
    else
        srand(time(0));
    int width;
    int height;
    int windowX;
    int windowY;
    int radius;
    int numParticles;
    int maxLife;
    int waterline;

    //asking for user input
    cout <<"Welcome to Sreeram Kondapalli’s CSE240 island generator! \n";
    cout << "Enter grid width: ";
    cin >> width;
    cout << "Enter grid height: ";
    cin >> height;
    cout << "Enter drop-zone x-coordinate (0 - <width>): ";
    cin >> windowX;
    cout << "Enter drop-zone y-coordinate (0 - <height>): ";
    cin >> windowY;
    cout << "Enter drop-zone radius (minimum 2): ";
    cin >> radius;
    cout << "Enter number of particles to drop: ";
    cin >> numParticles;
    cout << "Enter max life of particles: ";
    cin >> maxLife;
    cout << "Enter value for waterline (40-200): ";
    cin >> waterline;

    int** map = makeParticleMap(width, height, windowX, windowY, radius,numParticles, maxLife);
    cout << endl << endl;
    polishedParticleMap(width, height, map, waterline);


}

int** makeParticleMap(int width, int height,  int windowX, int windowY, int radius,
                      int numParticles, int maxLife)
{
   //variable declaration
    int** map;
    int* newPoints;
    int x = 0;
    int y = 0;
    double r = 0.0;

    map = new int*[height];
    for(int y = 0; y < height; y++)
    {
        map[y] = new int[width];
    }

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            map[y][x] = 0;
        }
    }

    //creating the grid
    int max = maxLife;
    while(numParticles != 0)
    {
        //drop zone
        r = radius * sqrt(frand());
        double theta = frand() * 2 * M_PI;
        x = (int)(windowX + r * cos(theta));
        y = (int)(windowY + r * sin(theta));

        map[y][x] = map[y][x] + 1;

        while(maxLife != 0)
        {
            newPoints = movement(x, y);
            if(moveExists(map, width, height, newPoints[0], newPoints[1]) == true)
            {
                int directionX = newPoints[0];
                int directionY = newPoints[1];

                x = directionX;
                y = directionY;
                map[y][x] = map[y][x] + 1;
            }
            maxLife--;
        }
        maxLife = max;
        numParticles--;
    }


    //printing the grid
    cout << "Raw Island:" << endl;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            cout << setw(3) << map[i][j] ;
        }
        cout << endl;
    }

    findMax(map, width, height);

    ofstream outFile;
    outFile.open("Island.txt");

    for(int i = 0 ; i < height; ++i)
    {
        for(int j = 0; j < width; ++j)
        {
            outFile << map[i][j] << " ";
        }
        outFile << "\n";
    }

    outFile << endl;
    outFile.close();

    return map;
}

int* movement(int x, int y)
{
    int choice = (rand() % 159) + 1;
    int* newPoints = new int[2];
    int newPointX;
    int newPointY;

    if(choice >= 0 && choice <= 20)
    {
        newPointX = x - 1;
        newPointY = y - 1;
        newPoints[0] = newPointX;
        newPoints[1] = newPointY;
    }


    if(choice >= 21 && choice <= 40)
    {
        newPointX = x;
        newPointY = y - 1;
        newPoints[0] = newPointX;
        newPoints[1] = newPointY;
    }

    if(choice >= 41 && choice <= 60)
    {
        newPointX = x + 1;
        newPointY = y - 1;
        newPoints[0] = newPointX;
        newPoints[1] = newPointY;
    }

    if(choice >= 61 && choice <= 80)
    {
        newPointX = x - 1;
        newPointY = y;
        newPoints[0] = newPointX;
        newPoints[1] = newPointY;
    }

    if(choice >= 81 && choice <= 100)
    {
        newPointX = x + 1;
        newPointY = y;
        newPoints[0] = newPointX;
        newPoints[1] = newPointY;
    }

    if(choice >= 101 && choice <= 120)
    {
        newPointX = x - 1;
        newPointY = y + 1;
        newPoints[0] = newPointX;
        newPoints[1] = newPointY;
    }

    if(choice >= 121 && choice <= 140)
    {
        newPointX = x;
        newPointY = y + 1;
        newPoints[0] = newPointX;
        newPoints[1] = newPointY;
    }

    if(choice >= 141 && choice <= 160)
    {
        newPointX = x + 1;
        newPointY = y + 1;
        newPoints[0] = newPointX;
        newPoints[1] = newPointY;
    }

    return newPoints;
}
//move exists check if move is available
bool moveExists(int** map, int width, int height, int windowX, int windowY)
{
    if(windowX >= 0 && windowX < width && windowY >= 0 && windowY < height)
        return true;
    return false;
}
//find max finds the max
int findMax(int** map, int width, int height)
{
    int maxVal = 0;
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(map[y][x] > maxVal)
            {
                maxVal = map[y][x];
            }
        }
    }

    return maxVal;
}

void normalizeMap(int** map, int width, int height, int maxVal)
{
    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            map[y][x] = (map[y][x] / (float) maxVal) * 255;
        }
    }

}

void polishedParticleMap(int width, int height, int** map, int waterline)
{
    int** normalisedMap;
    normalisedMap = new int*[height];

    char** charMap;
    charMap = new char*[height];
    int maxVal = findMax(map, width, height);

    for(int i = 0; i < height; i++)
    {
        normalisedMap[i] = new int [width];
        charMap[i] = new char [width];
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            normalisedMap[i][j] = map[i][j];
        }
    }
    normalizeMap(normalisedMap, width, height, maxVal);
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(normalisedMap[i][j] < 0.5 * waterline)
            {
                charMap[i][j] = '#';
            }
            if(normalisedMap[i][j] > 0.5 * waterline)
            {
                charMap[i][j] = '~';
            }
            if(normalisedMap[i][j] < 0.5 * waterline)
            {
                charMap[i][j] = '#';
            }
            else if(normalisedMap[i][j] > waterline && normalisedMap[i][j] < (waterline + 0.15 * (255 - waterline)))
            {
                charMap[i][j] = '.';
            }
            else if(normalisedMap[i][j] > waterline && normalisedMap[i][j] >= (waterline + 0.15 * (255 - waterline)) && normalisedMap[i][j] < (waterline + 0.4 * (255 - waterline)))
            {
                charMap[i][j] = '-';
            }
            else if(normalisedMap[i][j] > waterline && normalisedMap[i][j] >= (waterline + 0.40 * (255 - waterline)) && normalisedMap[i][j] < (waterline + 0.80 * (255- waterline)))
            {
                charMap[i][j] = '*';
            }
            else if(normalisedMap[i][j] > waterline && normalisedMap[i][j] >= (waterline + 0.80 * (255 - waterline)))
            {
                charMap[i][j] = '^';
            }
        }
    }

    ofstream outFile;
    outFile.open("Island.txt");

    cout << "Normalized:" << endl;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            cout << setw(3) << normalisedMap[i][j] ;
            outFile << normalisedMap[i][j] << " ";
        }
        cout << endl;
        outFile << endl;
    }
    cout << endl;
    cout << "Final:" << endl;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(charMap[i][j] == '#'){
                cout << termcolor::blue << charMap[i][j];
                outFile << charMap[i][j];
            }
            else if(charMap[i][j] == '~'){
                cout << termcolor::cyan << charMap[i][j];
                outFile << charMap[i][j];
            }
            else if(charMap[i][j] == '.'){
                cout << termcolor::bright_yellow << charMap[i][j];
                outFile << charMap[i][j];
            }
            else if(charMap[i][j] == '-'){
                cout << termcolor::green << charMap[i][j];
                outFile << charMap[i][j];
            }
            else if(charMap[i][j] == '*'){
                cout << termcolor::bright_green << charMap[i][j];
                outFile << charMap[i][j];
            }
            else if(charMap[i][j] == '^'){
                cout << termcolor::bright_grey << charMap[i][j];
                outFile << charMap[i][j];
            }
        }
        cout << endl;
    }

    outFile.close();
}

double frand()
{
    return (double)rand() / ((double)RAND_MAX+1);
}