#include "FolderNode.h"
FolderNode::FolderNode(const string& name) :XmlNode(name)
{

}
NodeType FolderNode::getType() const
{
	return NodeType::FOLDER;
}