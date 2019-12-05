#include "CSVReader.h"

vector<vector<string> > CSVReader::getData(){

	ifstream file (fileName);

	vector<vector<string> > ret;

	string line = "";
	// Iterate through each line and split the content using delimeter
	while (getline(file, line))
	{
		vector<string> vec;
		size_t pos = 0;
        string token;
        while ((pos = line.find(delimeter)) != string::npos) {
            token = line.substr(0, pos);
            vec.push_back(token);
            line.erase(0, pos + 1);
            }
           vec.push_back(line);
		ret.push_back(vec);
	}
	// Close the File
	file.close();

	return ret;
}
