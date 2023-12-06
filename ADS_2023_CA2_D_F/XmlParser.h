#pragma once
#include "Tree.h"
#include "XmlNode.h"
class XmlParser
{
public :
	Tree<XmlNode*> parseXml();
private:
	bool validateXML();
};

