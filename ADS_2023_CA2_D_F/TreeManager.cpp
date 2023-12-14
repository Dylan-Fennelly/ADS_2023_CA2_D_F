#include "TreeManager.h"

TreeManager::TreeManager(XmlParser* parser, XmlFileLoader* xmlFileLoader)
{
	this->xmlParser = parser;
	this->xmlFileLoader = xmlFileLoader;
}

bool TreeManager::loadTreeFromXML(string path)
{
    if (this->xmlParser == nullptr)
    {
        return false;
    }
    else
    {
        //Load the xml file using the xmlFileLoader
        //then parse using the parser and return the tree
        string xml = this->xmlFileLoader->loadFile(path);
        this->xmlTree = this->xmlParser->parseXml(xml);
    }
    return true;
}
void TreeManager::displayTree()
{
	TreeIterator<XmlNode*> iter(this->xmlTree);
	displayTreeRecursive(iter, "");
}
void TreeManager::displayTreeRecursive(TreeIterator<XmlNode*> treeIterator, string indent)
{

	cout << indent << treeIterator.node->data->display();
	if (treeIterator.childValid())
	{
		cout << "(" << endl;

		while (treeIterator.childValid())
		{
			TreeIterator<XmlNode*> iter2(treeIterator.childIter.currentNode->data);
			displayTreeRecursive(iter2, "\t" + indent);
			treeIterator.childForth();
		}
		cout << indent << ")";
	}
	cout << endl;
}

