#include "XmlNode.h"

XmlNode::XmlNode(const string& name)
{

	this->name = name;
}

string XmlNode::getName()
{
	return this->name;
}

