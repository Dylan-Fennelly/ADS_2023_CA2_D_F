// ADS_2023_CA2_D_F.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tree.h"
#include <string>
#include "FolderNode.h"
#include "NodeType.h"
#include "FileNode.h"
#include "TreeIterator.h"
#include "XmlFileLoader.h"
#include "XmlParser.h"
#include "TreeManager.h"
using namespace std;
template<class T>
void displayTree(TreeIterator<T> iter, string indent);

int main()
{
	FolderNode* test = new FolderNode("Root");
   // cout << test.getType() << endl;
    FileNode* fileTest = new FileNode("test", 12, ".exe");
   // cout << fileTest.getType() << endl;
    Tree<XmlNode*> root(test);
    TreeIterator<XmlNode*> iter(&root);
    iter.appendChild(fileTest);
   // cout << iter.item()->getType() << endl;
	FileNode* filetest2 = new FileNode("Test 2", 20, ".bat");
	iter.appendChild(filetest2);
	FolderNode* folder2 = new FolderNode("utils");
	iter.appendChild(folder2);
	iter.childForth();
	iter.childForth();
	iter.down();
	FileNode* filetest3 = new FileNode("test 3", 100, ".exe");
	iter.appendChild(filetest3);
	iter.root();
	displayTree(iter, "");
	
	XmlParser parser;


	XmlFileLoader loader;
	string filename = "E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml";
	string xml = loader.loadFile(filename);
	
	cout << xml << endl;
	cout <<boolalpha<< parser.validateXML(xml) << endl;
	Tree<XmlNode*>* tree = parser.parseXml(xml);
	if (tree != nullptr)
	{
		cout << "Parsed XML Tree:" << endl;
		TreeIterator<XmlNode*> iter2(tree);  // Pass the actual tree pointer
		//displayTree(iter2, "");
	}
	else
	{
		cout << "XML is invalid" << endl;
	}
	XmlParser* parser2 = new XmlParser();
	XmlFileLoader* loader2 = new XmlFileLoader();

	TreeManager* manager = new TreeManager(parser2,loader2);
	manager->loadTreeFromXML("E:\\Projects\\C++\\ADS_2023_CA2_D_F\\XmlFiles\\vs_sample_simple.xml");

	cout << "Break";
	TreeIterator<XmlNode*> iter3(manager->xmlTree);// Pass the actual tree pointer
//displayTree(iter3, "");
	manager->displayTree();
	cout<<manager->countItemsinTree();
}
template<class T>
void displayTree(TreeIterator<T> iter, string indent)
{
	cout << indent << iter.node->data->display();
	if (iter.childValid())
	{
		cout << "(" <<endl;
	
	while (iter.childValid())
	{
		TreeIterator<T> iter2(iter.childIter.currentNode->data);
		displayTree(iter2, "\t" + indent);
		iter.childForth();
	}
	cout <<indent<< ")" ;
	}
	cout << endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
