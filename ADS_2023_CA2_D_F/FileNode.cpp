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
string FileNode::display() const
{
	return "File: " + name + " " + to_string(fileLength) + "Bytes " + " " + fileType;
}
int FileNode::getFileLength() const
{
	return fileLength;
}
string FileNode::getFileType() const
{
	return fileType;
}