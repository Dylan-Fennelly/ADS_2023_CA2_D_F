#include "XmlFileLoader.h"
#include <fstream>
#include <sstream>

string XmlFileLoader::loadFile(string filePath)
{
    ifstream file(filePath);
    ostringstream fileContentStream;

    if (file.is_open()) 
    {
        string line;
        while (getline(file, line)) 
        {
            fileContentStream << line << '\n';  // Preserve line breaks
        }
        file.close();
    }
    else 
    {
        throw std::exception("Error Opening File");
    }

    return fileContentStream.str();
}
