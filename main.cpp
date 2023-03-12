#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

#define MAX_LINES 20

using namespace std;


string generateRandomID() {
    const string CHARACTERS = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    const int ID_LENGTH = 4;
    string id;

    // Seed the random number generator with the current time
    srand(time(0));

    // Generate a random character for each position in the ID string
    for (int i = 0; i < ID_LENGTH; i++) {
        int index = rand() % CHARACTERS.length();
        id += CHARACTERS[index];
    }

    return id;
}


int main()
{

    ifstream myFile;
    string array[MAX_LINES];

    cout << "Contents of arrivingAnimals.txt ..." << endl;
    myFile.open("arrivingAnimals.txt");

    if (myFile.fail())
    {
        cout << "Failed to open file." << endl;
        return 1;
    }

    int lines = 0;
    while (!myFile.eof())
    {
        getline(myFile, array[lines]);
        lines++;

        if (lines == MAX_LINES)
        {
            cout << "Max lines reached" << endl;
            break;
        }
    }

    myFile.close();

    vector<vector<string>> newArray;

    for (const auto &str : array)
    {
        vector<string> innerVector;

        // Split the string by spaces
        size_t pos = 0;
        string token;
        string tempStr = str; // make a copy of the string
        while ((pos = tempStr.find(' ')) != string::npos)
        {
            token = tempStr.substr(0, pos);
            tempStr.erase(0, pos + 1); // modify the copy
            innerVector.push_back(token);
        }
        innerVector.push_back(tempStr); // add the final token

        // Split the inner vector by commas
        vector<string> subVector;
        for (const auto &token : innerVector)
        {
            if (token.find(',') != string::npos)
            {
                vector<string> newVector;
                size_t subPos = 0;
                string subToken;
                string subTempStr = token; // make a copy of the string
                while ((subPos = subTempStr.find(',')) != string::npos)
                {
                    subToken = subTempStr.substr(0, subPos);
                    subTempStr.erase(0, subPos + 1); // modify the copy
                    newVector.push_back(subToken);
                }
                newVector.push_back(subTempStr); // add the final token
                subVector.insert(subVector.end(), newVector.begin(), newVector.end());
            }
            else
            {
                subVector.push_back(token);
            }
        }

        newArray.push_back(subVector);
    }

    // Print the 2D array
    for (const auto &innerVector : newArray)
    {
        for (const auto &str : innerVector)
        {
            cout << str << " ";
        }
        cout << endl;
    }

    // Access an element of the 2D array
    cout << newArray[4][0] << endl;

    // for (size_t i = 0; i < newArray.size(); i++) {
    // for (size_t j = 0; j < newArray[i].size(); j++) {
    //     cout << newArray[i][j] << " ";
    // }
    // cout << endl;
    //}

    // Open the output file stream
    ofstream outfile("output.txt");

    // Check if the file was opened successfully
    if (!outfile.is_open())
    {
        cout << "Error opening output file!" << endl;
        return 1;
    }

    // Write the array elements to the output file
    
    for (size_t i = 0; i < newArray.size(); i++)
    {
        for (size_t j = 0; j < newArray[i].size(); j++)
        {
            outfile << newArray[i][j] << " ";
        }
        outfile << endl;
    }

    // Close the output file stream
    outfile.close();

    return 0;
}
