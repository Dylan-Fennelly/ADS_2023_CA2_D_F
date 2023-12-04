#pragma once
#include "XmlNode.h"
class FolderNode :public XmlNode
{
public:
	FolderNode(const string& name);
	NodeType getType() const override;
};

