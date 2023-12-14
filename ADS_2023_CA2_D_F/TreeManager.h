#pragma once

#include "Tree.h"
#include "XmlNode.h"
#include "XmlParser.h"
#include "XmlFileLoader.h"
#include "TreeIterator.h"

class TreeManager {
public:
    TreeManager(XmlParser*, XmlFileLoader*);
    bool loadTreeFromXML(string path);
    void displayTree();
    int countItemsinTree();
    string findFileOrFolder(string filename);
    int calculateMemoryUsage(string path, bool deep);
    void displayFolderContents(string folderName);
    void pruneTree();

private:
    int calculateMemoryUsageLocalToFile(string path);
    int calculateMemoryUsageDeep(string path);
    void calculateTotalMemoryUsage(Tree<XmlNode*>* subtree, int& totalMemoryUsage);
    void displayTreeRecursive(TreeIterator<XmlNode*> treeIterator, string indent);
    void pruneTreeRecursive(Tree<XmlNode*>* currentNode);
    string findFileOrFolderRecursive(TreeIterator<XmlNode*> iterator, string filename);

    XmlParser* xmlParser;
    XmlFileLoader* xmlFileLoader;
    Tree<XmlNode*>* xmlTree = nullptr;
};