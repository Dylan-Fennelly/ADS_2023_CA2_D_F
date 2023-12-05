#include "FolderNode.h"
FolderNode::FolderNode(const string& name) :XmlNode(name)
{

}
NodeType FolderNode::getType() const
{
	return NodeType::FOLDER;
}
string FolderNode::display() const
{
	return "Folder: " + name;
	
}