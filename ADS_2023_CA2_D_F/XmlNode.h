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
	XmlNode(const string& name); // Constructor for the xml node

	virtual ~XmlNode() = default; // Virtual destructor for the xml node
	virtual NodeType getType() const = 0; /*Virtual function to get the type of the node*/
	virtual string display() const = 0; /*Virtual function to display the node*/
	
	string name; //String for the name of the xml element

	virtual void setName(const string& name) = 0; //Function to set the name of the xml element
};