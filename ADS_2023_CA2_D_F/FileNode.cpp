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
	return "File: " + name + " " + to_string(fileLength) + "Bytes " + " FileType: " + fileType;
}
int FileNode::getFileLength() const
{
	return fileLength;
}
string FileNode::getFileType() const
{
	return fileType;
}

void FileNode::setName(const string& name)
{
	this->name = name;
}

void FileNode::setFileLength(int length)
{
	this->fileLength = length;
}

void FileNode::setFileType(const string& fileType)
{
this->fileType = fileType;
}
