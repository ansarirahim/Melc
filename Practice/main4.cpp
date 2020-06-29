typedef unsigned char BYTE;
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <assert.h>
using std::cout;
using std::endl;
using std::ifstream;
using std::string;
using std::getline;
using std::vector;


//
// *** DATA STRUCTURES ***
//

// Each line data is stored in this structure
struct LineData
{
    // Store bytes read in current line
    vector< BYTE > Data;
};

// Prefer STL vector to raw C arrays.
//
//typedef struct _INTEL_HEX_RECORD
//{
//    BYTE Length;
//    WORD Address;
//    BYTE Type;
//    BYTE Data[MAX_INTEL_HEX_RECORD_LENGTH];
//} INTEL_HEX_RECORD, *PINTEL_HEX_RECORD;


//
// *** FUNCTION IMPLEMENTATIONS ***
//

// Given a character storing a nibble in hex, 
// converts it to its corresponding value
BYTE CharToHex(char ch)
{
    // Convert to upper case
    ch = toupper(ch);

    // Parse nibble
    if (ch >= '0' && ch <= '9')
    {
        return (ch - '0');
    }
    else if (ch >= 'A' && ch <= 'F')
    {
        return (ch - 'A' + 10);
    }
    else
    {
        // Bad input character 
        assert(false);
        return 0; // to suppress warning C4715
    }
}

// Given a pointer to two characters containing a byte representation in hex,
// returns the corresponding byte value.
BYTE ParseByte(const char * str)
{
    char highNibbleChar = str[0];
    char lowNibbleChar = str[1];

    BYTE highNibble = CharToHex(highNibbleChar);
    BYTE lowNibble = CharToHex(lowNibbleChar);

    return (lowNibble + (highNibble << 4));
}


// Given a line containing hex data, parses it
// and stores data in a vector of BYTEs.
void ParseLine(const string & line, vector<BYTE> & data)
{
    // Clear vector content
    data.clear();

    // Pointer to line characters
    const char * ptr = line.c_str();

    // Skip starting ":"
    assert(*ptr == ':');
    ptr++;

    // String length.
    // Process characters two-by-two; exclude starting ":" (so: length-1)
    int byteCount = (line.length() - 1) / 2;

    // Reserve storage in array
    data.reserve(byteCount);

    // Process each couple of hex chars in the string
    for (int i = 0; i < byteCount; i++)
    {
        // Parse couples of hex characters and convert them to bytes
        BYTE currByte = ParseByte(ptr);

        // Add byte to array
        data.push_back(currByte);

        // Go to next characters
        ptr += 2;
    }
printf("\n");
for(int i=0;i<byteCount;i++)
printf(" %.2X",data.at(i));
   
}


//
// *** MAIN PROGRAM ***
//
int main()
{
    // Try opening input text file
    ifstream inFile("0010603_FLASH.HEX");//InputFile.txt");
    
    // Check for open failure
    if (! inFile)
    {
        cout << "Can't open file." << endl;
        exit(1);
    }

    // Line read from file
    string line;

    // Store data read from file, line by line
    vector< LineData > fileData;

    // Read file line by line, and process it
    while (getline(inFile, line))
    {

        LineData currLineData;
        ParseLine(line, currLineData.Data);
        fileData.push_back(currLineData);
    }

    // File closed by ifstream destructor

    // Put a break point on return statement and inspect
    // the load data in 'fileData' variable using STL visualizers.

    // All right
    return 0;
}

