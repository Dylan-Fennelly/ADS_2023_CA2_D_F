#pragma once
#include "XmlNode.h"
class FileNode : public XmlNode
{
public:
	FileNode(const string& name, int length, const string& fileType);
	NodeType getType() const override;
	int getFileLength() const;
	string getFileType() const;
	void setName(const string& name) override;
	void setFileLength(int length);
	void setFileType(const string& fileType);
	string display() const override;
	int fileLength;
	string fileType;
};

