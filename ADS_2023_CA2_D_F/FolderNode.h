#pragma once
#include "XmlNode.h"
class FolderNode :public XmlNode
{
public:
	FolderNode(const string& name);
	NodeType getType() const override;
	string getName() const ;
	string display () const override;
};

