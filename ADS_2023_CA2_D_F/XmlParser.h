#pragma once
#include "Tree.h"
#include "XmlNode.h"
class XmlParser
{
public :
	Tree<XmlNode*> parseXml(string& xml);
	bool validateXML(string& xml);
};

