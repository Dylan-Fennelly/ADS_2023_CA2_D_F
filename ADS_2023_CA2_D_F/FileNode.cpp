#include "FileNode.h"
FileNode::FileNode(const string& name, int fileLength, const string& fileType)
	:XmlNode(name)
{
	this->fileLength = fileLength;
	this->fileType = fileType;
}
NodeType FileNode :: getType() const
{
	return NodeType::FILE;
}