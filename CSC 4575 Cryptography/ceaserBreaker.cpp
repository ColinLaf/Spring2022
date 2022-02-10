#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <iomanip>

using namespace std;

string shiftCipher(int, string);
string formatOutput(string);

class character
{
    public:
        int key;
        double frequency;
        double correlation;
};

int spaces = 0;
int spaceLocation[16] = {0};

int main()
{
    string ciphertext = "IT STY XYZRGQJ TAJW XTRJYMNSL GJMNSI DTZ";
    string temp= "";
    char alphabet[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    double engFreq[26] = {0.080, 0.015, 0.030, 0.040, 0.130, 0.020, 0.015, 0.060, 0.065, 0.005, 0.005, 0.035, 0.030, 0.070, 0.080, 0.020, 0.002, 0.065, 0.060, 0.090, 0.030, 0.010, 0.015, 0.005, 0.020, 0.002};
    character objArray[26], tempArray[5];

    for(int i = 0; i < 26; i++)
    {
        objArray[i].key = alphabet[i];
        objArray[i].frequency = 0.0;
        objArray[i].correlation = 0.0;
    }


    cout << "\nThis is the Ceaser Cipher Program" << endl;
    cout << "The ciphertext is IT STY XYZRGQJ TAJW XTRJYMNSL GJMNSI DTZ" << endl;
    

    int numUnique, letters, max = 0;
    char c;

    //Removes the spaces between each of the words in the ciphertext
    for(int i = 0; i < ciphertext.length(); i++)
    {
        c = ciphertext[i];
        if(!isspace(c))
        {
            temp += c;
            letters++;
        }
        else
        {
            spaceLocation[spaces] = letters;
            spaces++;
            letters = 0;
        }
    }
    ciphertext = temp;

    //Gets the character frequency for each letter of the cipher
    for(int i = 0; i < 26; i++)
    {
        for(int j = 0; j < ciphertext.length(); j++)
        {
            if(alphabet[i] == ciphertext[j])
            {
                objArray[i].frequency += 0.1;
            }
        }
        //Gets the number of unique characters in the cipher
        if(objArray[i].frequency > 0)
        {
            numUnique++;
        }
    }
    
    //Calculates the Correlation of Frequency for the cipher
    for(int i = 0; i < 26; i++)
    {
        for(int j = 0; j < 26; j++)
        {
                objArray[i].correlation += (objArray[j].frequency * engFreq[(26 + j-i) % 26]);   
        }
    }

    for(int i = 0; i < 5; i++)
    {
        for(int j = 0; j < 26; j++)
        {
            if(objArray[j].correlation > objArray[max].correlation)
            {
                max = j;
            }
        }
        tempArray[i].key = objArray[max].key;
        tempArray[i].correlation = objArray[max].correlation;
        tempArray[i].frequency = objArray[max].frequency;
        objArray[max].correlation = 0.0;
        max = 0;
    }

    int d = 0;
    cout << "\nMost Probable Keys:" << endl << endl;
    for(int i = 0; i < 5; i++)
    {

        cout << "i = " << static_cast<char>(tempArray[i].key) << "   " << setprecision(4) << fixed << tempArray[i].correlation << endl;
        cout << "---Possible plaintext: ";
        d = tempArray[i].key % 65;
        cout << shiftCipher(d, ciphertext) << endl;
        //cout << setprecision(1) << fixed << tempArray[i].frequency << " ";
    }
}

string shiftCipher(int shift, string ciphertext)
{
    int letter = 0;
    int len = ciphertext.length();
    string tempStr = "";
    for(int i = 0; i < len; i++)
    {
        letter = static_cast<int>(ciphertext[i]);
        letter -= shift;

        if(letter < 65)
        {
            tempStr += static_cast<char>(letter+26);
        }
        else
        {
            tempStr += static_cast<char>(letter);
        }
    }
    return formatOutput(tempStr);
}

string formatOutput(string str)
{
    int start, sp = 0;
    int len = str.length();
    string tempStr = "";
    
    for(int i = 0; i < spaces; i++)
    {   
        sp = spaceLocation[i];
        tempStr += str.substr(start, sp) + " ";
        //cout << spaceLocation[i] << " ";
        start += spaceLocation[i];
    }
    tempStr += str.substr(start);
    return tempStr;
}

