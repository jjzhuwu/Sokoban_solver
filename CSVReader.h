#ifndef CSVREADER_H_INCLUDED
#define CSVREADER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <vector>
#include <iterator>
#include <string>
using namespace std;


// from : https://thispointer.com/how-to-read-data-from-a-csv-file-in-c/
class CSVReader
{
	string fileName;
	string delimeter;

public:
	CSVReader(std::string filename, std::string delm = ","){
	    fileName = filename;
	    delimeter = delm;
    }

	// Function to fetch data from a CSV File
	std::vector<std::vector<std::string> > getData();
};

#endif // CSVREADER_H_INCLUDED
