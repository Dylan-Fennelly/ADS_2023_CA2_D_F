#pragma once
#include "Tree.h"
#include "XmlNode.h"
#include "XmlParser.h"
class TreeManager
{
public:
	bool loadTreeFromXML();

private:
	Tree<XmlNode*> xmlTree;
	XmlParser xmlParser;
};

