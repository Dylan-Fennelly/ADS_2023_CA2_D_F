#pragma once
#include "Tree.h"
#include "XmlNode.h"
#include "TreeIterator.h"
class XmlParser
{
public :
	Tree<XmlNode*>* parseXml( string& xml);

	bool validateXML(string& xml);
	private:

};

