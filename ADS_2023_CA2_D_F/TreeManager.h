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
    string findFileOrFolder(string filename);
    string findFileOrFolderRecursive(TreeIterator<XmlNode*> iterator, string filename);
    int calculateMemoryUsage(string path, bool deep);


private:
    int calculateMemoryUsageLocalToFile(string path);
    int calculateMemoryUsageDeep(string path);

    void calculateTotalMemoryUsage(Tree<XmlNode*>* subtree, int& totalMemoryUsage);


    
    XmlParser* xmlParser;
    XmlFileLoader* xmlFileLoader;
    void displayTreeRecursive(TreeIterator<XmlNode*> treeIterator, string indent);   
};


