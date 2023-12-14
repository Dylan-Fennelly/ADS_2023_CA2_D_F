#pragma once
#include "Tree.h"
#include "XmlNode.h"
#include "XmlParser.h"
#include "XmlFileLoader.h"
#include"TreeIterator.h"
class TreeManager
{
public:
    TreeManager(XmlParser* , XmlFileLoader* );
    Tree<XmlNode*>* xmlTree = nullptr;
    bool loadTreeFromXML(string path);
    void displayTree();
    int countItemsinTree();

    int calculateMemoryUsage(string path);

    void calculateMemoryUsageRecursive(TreeIterator<XmlNode*> treeIterator, int& total);

private:
    
    XmlParser* xmlParser;
    XmlFileLoader* xmlFileLoader;
    void displayTreeRecursive(TreeIterator<XmlNode*> treeIterator, string indent);   
};


