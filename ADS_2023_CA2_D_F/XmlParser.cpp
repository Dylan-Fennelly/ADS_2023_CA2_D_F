#include "XmlParser.h"
#include <sstream>
#include <stack>
bool XmlParser::validateXML( string& xmlContent) {
    istringstream xmlStream(xmlContent);
    stack<string> tagStack;

    std::string line;
    while (getline(xmlStream, line)) 
    {
        size_t pos = line.find('<');
        while (pos != string::npos)
        {
            size_t endPos = line.find('>', pos);
            if (endPos != string::npos)
            {
               string token = line.substr(pos, endPos - pos + 1);
                if (token[1] == '/') 
                { // Closing tag
                    string closingTag = token.substr(2, token.size() - 3);
                    if (tagStack.empty() || tagStack.top() != closingTag) 
                    {
                        return false; // Mismatched closing tag
                    }
                    tagStack.pop();
                }
                else
                { // Opening tag
                    tagStack.push(token.substr(1, endPos - pos - 1));
                }
                pos = endPos + 1;
            }
            else
            {
                break;
            }
            pos = line.find('<', pos);
        }
    }

    return tagStack.empty(); // Stack should be empty if all tags are properly closed
}


