#include "FolderNode.h"
FolderNode::FolderNode(const string& name) :XmlNode(name)
{

}
NodeType FolderNode::getType() const
{
	return NodeType::FOLDER;
}
string FolderNode :: getName() const
{
	return name;
}
string FolderNode::display() const
{
	return "Folder: " + name;
	
}

void FolderNode::setName(const string& name)
{
	this-> name = name;
}
