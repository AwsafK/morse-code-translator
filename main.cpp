/******************************************************************************
A modular program that reads text from a file, and then writes that text to another file in morse code.
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool loadMorseArray(string[], ifstream&);
void genMorse(string&, const string, const string[]);

int main()
{
    string inputFileName, outputFileName;
    int lineCounter = 0;
    ifstream morseLoaderFile("morseLetters.txt");    
    cout << "Enter the name of the input File: ";
    cin >> inputFileName;
    
    ifstream inputFile(inputFileName);
    if(inputFile.fail())  //If input file fails to open
    {
        cout << "Error, unable to open file " << inputFileName << ".\n";
    }
    else
    {
        cout << "Enter the name of the ouput File: ";
        cin >> outputFileName;
        
        ofstream outputFile(outputFileName);
        if(outputFile.fail())  //If output file fails to open
        {
            cout << "Error, unable to open the output file " << outputFileName << ".\n";
        }
        
        string letterHolderArr[26];
        bool successCheck = false;
        successCheck = loadMorseArray(letterHolderArr, morseLoaderFile);
        
        string lineToConvert;
        if(successCheck == true)
        {
            while(getline(inputFile, lineToConvert))
            {   
                lineCounter++;
                string generatedMorseOut;
                genMorse(generatedMorseOut, lineToConvert, letterHolderArr);
                
                if(lineCounter > 0)
                {
                    outputFile << generatedMorseOut << endl;
                }
            }
            outputFile.close();
        }
        if(successCheck == false)  //If there is an error loading the morse code
        {
            cout << "Error loading the Morse Code\n";
        }

        if(lineCounter > 0)  //This prints if the file isn't empty
        {
            cout << "Translation complete. " << lineCounter << " lines translated.\n";
        }

        if(lineCounter == 0)  //if the file is empty
        {
            cout << "The file was empty.\n";
        }
    
    }
    
    inputFile.close();

    morseLoaderFile.close();    
    return 0;
}
//This function puts the morse code into the string array

bool loadMorseArray(string letterHolder[26], ifstream &inputFileLinker)
    {
        string morseLoader;
        bool success = false;
        char characterCode;
        while(inputFileLinker >> characterCode)
        {
            if(characterCode >= 'A' && characterCode <= 'Z')
            {
                inputFileLinker.ignore(1, '\t');  //Ignoring the tab 
                inputFileLinker >> morseLoader;
                
                //Making sure the code is being saved to the correct index
                
                letterHolder[characterCode % 'A'] = morseLoader;
                success = true;
            }
        }

        return success;
    }
//This function converts the letters to morse code
    
void genMorse(string &generatedMorseOut, const string lineToConvert, const string letterHolderArr[])
{
    int arrayIndex = 0;
    int i = 0;
    for(char charToMorse : lineToConvert)
    {
        charToMorse = lineToConvert[i];
        arrayIndex = charToMorse % 'A';
        if(arrayIndex >= 0 && arrayIndex <= 26)
        {
            generatedMorseOut += letterHolderArr[arrayIndex] + " ";
            i++;
        }
        if(charToMorse == ' ')   //If it reads a space
        {   
            generatedMorseOut += " ";
            i++;
        }
        if(charToMorse == '.')  //If it reads a period
        {
            generatedMorseOut += ".";
            i++;
        }
        
    }
    
    
    
    
    
    
    return;
}


