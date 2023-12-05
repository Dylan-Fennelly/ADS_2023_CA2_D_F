#pragma once
#include "XmlNode.h"
class FileNode : public XmlNode
{
public:
	int fileLength;
	string fileType;
	FileNode(const string& name, int length, const string& fileType);
	NodeType getType() const override;
	string display() const override;
};

