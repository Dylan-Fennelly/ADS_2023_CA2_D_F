#pragma once
#include <string>
#include "NodeType.h"
using namespace std;
class XmlNode /*This is an abstrct class to hold an xml element 
				For this project there will only be two types: file and folder
				but the addition of other node for other documents that use
				the xml structure could be added (follows open closed principle*/
{
public :
	string name; //String for the name of the xml element

	XmlNode(string & name) : name(name) {} // Constructor for the xml node

	virtual ~XmlNode() = default; // Virtual destructor for the xml node
	virtual NodeType getType() const = 0; /*Pure Virtual function to get the type of the node
											(This forces the class to be treated as abstrct*/
};