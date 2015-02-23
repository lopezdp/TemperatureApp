//
//  main.cpp
//  Ex.01-LopezDP.cpp
//
//  Created by David P. Lopez on 2/5/15.
//  Copyright (c) 2015 David P. Lopez. All rights reserved.
//

/* Sample Input File to USE for this program

4
12
Miami,59.6,60.5,64.0,67.6,72.0,75.2,76.5,76.5,75.7,72.2,67.5,62.2
Miami,76.5,77.7,80.7,83.8,87.2,89.5,90.9,90.6,89.0,85.4,81.2,77.5
Key West,65.2,65.7,68.8,72.1,75.9,78.7,79.6,79.2,78.5,75.7,71.9,67.3 
Key West,75.3,75.9,78.8,81.9,85.4,88.1,89.4 ,89.5,88.2,84.7,80.6,76.7 
Jacksonville,41.9,44.3,49.8,54.6,62.5,69.4,72.4,72.2,69.4,59.7,50.8,44.1
Jacksonville,64.2,67.3,73.4,78.6,84.3,88.7,90.8,89.4,86.1,79.1,72.5,65.8
Pensacola,42.7,45.4,51.7,57.6,65.8,72.1,74.5,74.2,70.4,59.6,51.1,44.7
Pensacola,61.2,64.4,70.2,76.2,83.4,89.0,90.7,90.1,87.0,79.3,70.3,63.4






*/


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct TemperatureInfo
{
    char scale; // degrees 'F' or 'C'
    double low;
    double high;
    string monthName;
};


struct CityTempInfo
{
    string cityName;
    TemperatureInfo *tempInfo;
};


//prototypes
void getCityMonthInfo(ifstream&, int *, int *);

void getMonthTempData(ifstream&, CityTempInfo *, int*, int*);

int programMenu(CityTempInfo *, int *, int * );

char scaleMenu(CityTempInfo *, int *, int *);

int reportMenu(CityTempInfo *, int *, int *);


double lowConvertC(CityTempInfo *, int *, int *);
double highConvertC(CityTempInfo *, int *, int *);
double warmMonth(CityTempInfo *, int *, int *, int *);
double coldMonth(CityTempInfo *, int *, int *, int *);
void displayInfo(CityTempInfo *, int *, int *, int *, char *, int *);





int main() {
    
    ifstream inFile;
    
    // insert code here...
    inFile.open("inFile.txt");
    
    if(!inFile)
    {
        cout << "ERROR!!! Cannot read file.";
    }
    else
    {
        
        int numCity;
        int numMonths;
        int citySelection;
        int reportChoice;
        char scaleChoice;
    
        CityTempInfo *ptrCurrentCity;//pointer to current city
    
        //get number of cities & number of months from file...
        getCityMonthInfo(inFile, &numCity, &numMonths);
    
        //dynamically allocate arrays
        ptrCurrentCity = new CityTempInfo[numCity];
    
        // safe programming practice
        if (!ptrCurrentCity /*|| !ptrTempInfo*/)
        {
            cout << "Unable to successfully allocate required memory...";
            cout << "Exiting...";
            system ("PAUSE");   // Windows only
            exit(0);
        }
    
        //test getCityMonthInfo function
        cout << numCity << endl;
        cout << numMonths << endl;
    
        //get month names and populate array ptrCurrentCity with cityName & high/low data
        getMonthTempData(inFile, ptrCurrentCity, &numCity, &numMonths);
        
        citySelection = programMenu(ptrCurrentCity, &numCity, &numMonths);
        
        scaleChoice = scaleMenu(ptrCurrentCity, &numCity, &numMonths);
        reportChoice = reportMenu(ptrCurrentCity, &numCity, &numMonths);
        
        displayInfo(ptrCurrentCity, &numCity, &numMonths, &citySelection, &scaleChoice, &reportChoice);
        
        
        // deallocate memory
    

        }
    
    // deallocate memory
    //delete ptrCurrentCity;
    //ptrCurrentCity = nullptr;
    
    
    inFile.close();
    return 0;
    
}

void getCityMonthInfo(ifstream &inputFile, int *numOfCities, int *numOfMonths)
{
    string numCitiesString;
    string numMonthsString;
    
    //reads number of cities
    getline(inputFile, numCitiesString, '\n');
    *numOfCities = atoi(numCitiesString.c_str());
        
    //reads number of months
    getline(inputFile, numMonthsString, '\n');
    *numOfMonths = atoi(numMonthsString.c_str());
}

void getMonthTempData(ifstream &inFile, CityTempInfo *cityNames, int *numOfCities, int *numMonths)
{
    string tempCity;
    string temp;
    string tempLow;
    string tempHigh;

    //reads month names from file and passes string values to CityTempInfo struct variable cityName
    for(int j = 0; j < *numOfCities; j++)
    {
        //reads 1st City name at low temps
        getline(inFile, tempCity, ','); //gets 1st instance of cityName
        cityNames[j].cityName = tempCity;
        
        //dynamially creates an array of temp info for each cityName structure
        cityNames[j].tempInfo = new TemperatureInfo[*numMonths];
        
        cout << "low temps: " << endl;
        
        for(int i = 0; i < *numMonths; i++)
        {
            getline(inFile, tempLow, ','); //gets string of temp data one by one for lows
            cityNames[j].tempInfo[i].low = atof(tempLow.c_str()); //converts temps to int
            
            cout << cityNames[j].cityName << " " << cityNames[j].tempInfo[i].low << endl;
        }
        
        cout << "high temps: " << endl;
        for(int i = 0; i < *numMonths-1; i++)
        {
            getline(inFile, tempHigh, ','); //gets string of temp data one by one for highs
            cityNames[j].tempInfo[i].high = atof(tempHigh.c_str());
            
            cout << cityNames[j].cityName << " " << cityNames[j].tempInfo[i].high << endl;
        }
        getline(inFile, temp, '\n');
        cityNames[j].tempInfo[*numMonths-1].high = atof(temp.c_str());//reads the 12th month of high temp data for each city called
        
        cout << cityNames[j].cityName << " " << cityNames[j].tempInfo[*numMonths-1].high << endl;
    }
tempCity = "";
temp = "";
}

int programMenu(CityTempInfo *cityNames, int *numOfCities, int *numOfMonths)
{
    int menuSelection;
    bool t = true;
    
    //prompt user for menu selection input
    
    cout << endl;
    cout << endl;
    cout << "All data above this line is a test to show file was read correctly. Program runs below" << endl;
    cout << endl;
    cout << endl;
    cout << "Welcome to the COP 2335 Temperature Wizard Program." << endl;
    cout << "Please select one of the following cities: " << endl;
    cout << endl;
    cout << endl;
    
    while(t)
    {
        //loops through number of cities to print out menu choices
        for(int i = 0; i < *numOfCities; i++)
        {
            cout << i + 1 << ". " << cityNames[i].cityName << endl;
        }
        
        cout << *numOfCities + 1 << ". EXIT ---> Terminate Program." << endl;
        cout << endl;
        
        cout << "Your Menu Selection is: " << endl;
        
        // read user input for menu selection
        cin >> menuSelection;
        
        //user input validation & error checking
        if(menuSelection < 1 || menuSelection > 5)
        {
            cout << "Please enter a value between 1 & 5!!!" << endl;
            cout<< endl;
        }
    
        else if(menuSelection >= 1 && menuSelection < 5)
            scaleMenu(cityNames, numOfCities, numOfMonths);
        
        else if(menuSelection == 5 || menuSelection < 1 || menuSelection > 5)
        {
            exit(0);
        }else
            t = false;
        
    }
    
    return menuSelection;
    
}

//returns a char used for the C or F selection made by user
char scaleMenu(CityTempInfo *cityNames, int *numOfCities, int *numOfMonths)
{
    int menuSelection;
    bool t = true;
    
    //prompt user for scale selection input
    cout << "Please choose to view your data in Celcius or Farenheit: " << endl;
    cout << "1. Degrees Farenheit" << endl;
    cout << "2. Degrees Celcius" << endl;
    cout << "3. EXIT ---> Return to Previous Menu" << endl;
    
    while(t)
    {
        cin >> menuSelection;
        
        //user input validation & error checking
        if(menuSelection < 1 || menuSelection > 3)
        {
            cout << "Please enter a value between 1 & 3!!!" << endl;
            cout<< endl;
        }
        else if(menuSelection >= 1 && menuSelection < 3)
        {
            reportMenu(cityNames, numOfCities, numOfMonths);
        }
        else
            t = false;
        
        if(menuSelection == 1) // returns farenheit scale
            return 'F';
        if(menuSelection == 2) // returns Celcius Scale
            return 'C';
        if(menuSelection == 3) // selection to escape to previous menu
            programMenu(cityNames, numOfCities, numOfMonths);
        
        else
            cout << "Please enter a value between 1 & 3" << endl;
        
        
        for(int j = 0; j < *numOfCities; j++)
        {
            for(int i = 0; i < *numOfMonths; i++)
            {
                if(menuSelection == 1)
                    cityNames[j].tempInfo[i].scale = 'F';
                
                if(menuSelection == 2)
                    cityNames[j].tempInfo[i].scale = 'C';
            }
        }
    }
    return false;
}

int reportMenu(CityTempInfo *cityNames, int *numOfCities, int *numOfMonths)
{
    int menuSelection;
    bool t = true;
    
    cout << "What do you want to do?" << endl;
    cout << "1. View low and high temperatures" << endl;
    cout << "2. View the warmest month" << endl;
    cout << "3. View the coldest month" << endl;
    cout << "4. EXIT ---> Return to Previous Menu" << endl;
    
    while(t)
    {
        cin >> menuSelection;
        
        //user input validation & error checking
        if(menuSelection < 1 || menuSelection > 4)
        {
            cout << "Please enter a value between 1 & 4!!!" << endl;
            cout<< endl;
        }
        else if(menuSelection >= 1 && menuSelection < 4)
        {
            //reportMenu(cityNames, numOfCities, numOfMonths); go to next task etc reports
        }
        else if(menuSelection == 4)
        {
            scaleMenu(cityNames, numOfCities, numOfMonths);
        }
        else
            t = false;
    }

    return menuSelection;
}


double lowConvertC(CityTempInfo *cityNames, int *numOfCities, int *numOfMonths)
{
    return ((5.0/9.0) * (cityNames[*numOfCities].tempInfo[*numOfMonths].low  - 32.0));
}

double highConvertC(CityTempInfo *cityNames, int *numOfCities, int *numOfMonths)
{
    return ((5.0/9.0) * (cityNames[*numOfCities].tempInfo[*numOfMonths].high  - 32.0));
}


double warmMonth(CityTempInfo *cityNames, int *numOfCities, int *numOfMonths, int *cityChoice)
{
    double warmMonth = cityNames[*cityChoice - 1].tempInfo[0].high;
    
    for (int i = 0; i < *numOfMonths; i++)
    {
        if (cityNames[*cityChoice - 1].tempInfo[i].high >= warmMonth)
            warmMonth = cityNames[*cityChoice - 1].tempInfo[i].high;
    }
    return warmMonth;
}

double coldMonth(CityTempInfo *cityNames, int *numOfCities, int *numOfMonths, int *cityChoice)
{
    double coldMonth = cityNames[*cityChoice - 1].tempInfo[0].low;
    
    for (int i = 0; i < *numOfMonths; i++)
    {
        if (cityNames[*cityChoice - 1].tempInfo[i].low <= coldMonth)
            coldMonth = cityNames[*cityChoice - 1].tempInfo[i].low;
    }
    
    return coldMonth;
}



void displayInfo(CityTempInfo *cityNames, int *numOfCities, int *numOfMonths, int *cityChoice, char *scale, int *report)
{
    for (int i = 0; i < *numOfCities; i++)
        for (int j = 0; j < *numOfMonths; j++)
            cityNames[i].tempInfo[j].scale = *scale;
    
    // Converting Fahrenheit to Celsius
    if (*scale == 'C')
    {
        for (int i = 0; i < *numOfCities; i++)
        {
            for (int j = 0; j < *numOfMonths; j++)
            {
                cityNames[i].tempInfo[j].low  = lowConvertC(cityNames, numOfCities, numOfMonths);
                cityNames[i].tempInfo[j].high = highConvertC(cityNames, numOfCities, numOfMonths);
            }
        }
    }
    
    // Low and high temps
    if (*report == 1)
    {
        cout << cityNames[*cityChoice - 1].cityName << endl;
        cout << setw(5) << "Month" << setw(5) << "Low" << setw(11) << "High" << endl << setw(2.5);
        
        for (int i = 0; i < *numOfMonths; i++)
        {
            cout << cityNames[*cityChoice - 1].tempInfo[i].monthName.substr(0, 3) << setw(8);
            
            cout << fixed << setprecision(1) << cityNames[*cityChoice - 1].tempInfo[i].low << " "
            << cityNames[*cityChoice - 1].tempInfo[i].scale << setw(8);
            
            cout << fixed << setprecision(1) << cityNames[*cityChoice - 1].tempInfo[i].high << " "
            << cityNames[*cityChoice - 1].tempInfo[i].scale<< setw(2.5);
            cout << endl;
        }
    }
    
    // Warmest month
    else if (*report == 2)
    {
        double warmTemp = warmMonth(cityNames, numOfCities, numOfMonths, cityChoice);
        
        cout << "Warmest month for " << cityNames[*cityChoice - 1].cityName
        <<  " was " << fixed << setprecision(1) << warmTemp << " degrees " << scale << endl;
    }
    
    // Coldest month
    else if (*report == 3)
    {
        double coldTemp = coldMonth(cityNames, numOfCities, numOfMonths, cityChoice);
        
        cout << "Coldest month for " << cityNames[*cityChoice - 1].cityName
        <<  " was " << fixed << setprecision(1) << coldTemp << " degrees " << scale << endl;
    }
    
    else
    {
        cerr << "Exiting..." << endl;
        exit(1);
    }
}

























