// ADS_2023_CA2_D_F.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Tree.h"
#include <string>
#include "FolderNode.h"
#include "NodeType.h"
#include "FileNode.h"
#include "TreeIterator.h"
using namespace std;
template<class T>
void displayTree(TreeIterator<T> iter, string indent);

int main()
{
	FolderNode* test = new FolderNode("File");
   // cout << test.getType() << endl;
    FileNode* fileTest = new FileNode("test", 12, ".exe");
   // cout << fileTest.getType() << endl;
    Tree<XmlNode*> root(test);
    TreeIterator<XmlNode*> iter(&root);
    iter.appendChild(fileTest);
   // cout << iter.item()->getType() << endl;
	iter.root();
	displayTree(iter, "");
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
