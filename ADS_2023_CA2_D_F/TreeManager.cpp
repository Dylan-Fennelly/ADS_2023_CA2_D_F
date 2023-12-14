#include "TreeManager.h"
#include <stack>
#include "FileNode.h"
#include <vector>
#include <queue>
/*#pragma once
#include "Tree.h"

template <class T>
class TreeIterator
{
public:
	Tree<T> *node;
	DListIterator<Tree<T>*> childIter;

	TreeIterator(Tree<T>* root);
	void resetIterator();
	void root();
	void up();
	void down();
	void childBack();
	void childForth();
	void childStart();
	void childEnd();
	void appendChild(T item);
	void prependChild(T item);
	void insertChildBefore(T item);
	void insertChildAfter(T item);
	void removeChild();
	bool childValid();
	T childItem();
	T item();
};
template <class T>
TreeIterator<T>::TreeIterator(Tree<T>* root)
{
	node = root;
	resetIterator();
}

template <class T>
void TreeIterator<T>::resetIterator()
{
	if (node != nullptr)
	{
		childIter = node->children->getIterator();
	}
	else
	{
		childIter = nullptr;
	}
}

template <class T>
void TreeIterator<T>::root()
{
	if (node->parent != nullptr)
	{
		node = node->parent;
		root();
	}
	resetIterator();
}

template <class T>
void TreeIterator<T>::up()
{
	if (node->parent != nullptr)
	{
		node = node->parent;

	}
	resetIterator();
}

template <class T>
void TreeIterator<T>::down()
{
	if (childIter.isValid())
	{
		node = childIter.item();

	}
	resetIterator();
}

template <class T>
void TreeIterator<T>::childBack()
{
	if (childIter.isValid())
	{
		childIter.previous();
	}
}

template <class T>
void TreeIterator<T>::childForth()
{
	if (childIter.isValid())
	{
		childIter.advance();
	}
}

template <class T>
void TreeIterator<T>::childStart()
{
	if (childIter.isValid())
	{
		childIter.start();
	}
}

template <class T>
void TreeIterator<T>::childEnd()
{
	if (childIter.isValid())
	{
		childIter.end();
	}
}

template <class T>
void TreeIterator<T>::appendChild(T item)
{
	Tree<T>* temp = new Tree<T>(item);
	temp->parent = node;
	node->children->append(temp);
	resetIterator();
}

template <class T>
void TreeIterator<T>::prependChild(T item)
{
	Tree<T>* temp = new Tree<T>(item);
	temp->parent = node;
	node->children->prepend(temp);
	resetIterator();
}

template <class T>
void TreeIterator<T>::insertChildBefore(T item)
{
	Tree<T> *temp = new Tree<T>(item);
	temp->parent = node;
	node->children->insert(childIter, temp);

}

template <class T>
void TreeIterator<T>::insertChildAfter(T item)
{

	Tree<T> *temp = new Tree<T>(item);
	temp->parent = node;
	childIter.advance();
	node->children->insert(childIter, temp);
	childIter.previous();
	childIter.previous();

}

template <class T>
void TreeIterator<T>::removeChild()
{
	childIter = node->children->remove(childIter);

}

template <class T>
bool TreeIterator<T>::childValid()
{
	return childIter.isValid();
}

template <class T>
T TreeIterator<T>::childItem()
{
	return childIter->node->data;
}

template <class T>
T TreeIterator<T>::item()
{
	return node->data;
}*/
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
	if(this->xmlTree == nullptr)
	{
		cout << "Tree is empty" << endl;
		return;
	}
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

int TreeManager::countItemsinTree()
{
	if(this->xmlTree == nullptr)
	{
		return 0;
	}
	return this->xmlTree->count();
}
/*Determine the Amount of Memory Used by a Given Folder Using a Breadth-First Algorithm:

Implementation:
Implement a function (e.g., calculateMemoryUsage) that takes a folder path as a parameter.
Traverse the folder's tree using a breadth-first algorithm.
Sum the memory usage of all items within the folder (files and subfolders).*/
//A folder path is the order the folder decend in the tree
//eg ADS_Single_LinkedList_Exercises/git
//We need to take this string and split it, using the / as a delimiter
//then we do a breath first search on the tree
//if we dont find the specified file we return -1
//if we do find it we then do the children of the folder and add up the memory usage
//which is the getfileLength() on the file nodes
//We need to to check the type of the xml node and if is NodeType::FILE
//We use dynamic cast to access the function as the base class doesnt have access to the derived class functions
//We then add the memory usage to the total
//We then return the total
//Example of breath first search
/*void printBFS(Tree<string> tree)
{
	queue<Tree<string>> queue;
	queue.push(tree);
	while (!queue.empty())
	{
		DListIterator<Tree<string>*> iter = queue.front().children->getIterator();
		while (iter.isValid())
		{
			queue.push(*iter.item());
			iter.advance();
		}
		cout << queue.front().data << ", ";
		queue.pop();

	}


}*/
int TreeManager::calculateMemoryUsage(string path)
{
	if (xmlTree == nullptr || path == "")
	{
		return -1;
	}

	size_t pos = 0;
	string token;
	vector<string> pathVector;
	while ((pos = path.find("/")) != string::npos)
	{
		token = path.substr(0, pos);
		pathVector.push_back(token);
		path.erase(0, pos + 1);
	}
	pathVector.push_back(path);

	queue<Tree<XmlNode*>*> queue;
	queue.push(xmlTree);

	while (!queue.empty())
	{
		Tree<XmlNode*>* currentNode = queue.front();
		queue.pop();

		if (currentNode->data->getName() == pathVector.front())
		{
			pathVector.erase(pathVector.begin());

			if (pathVector.empty())
			{
				int totalMemoryUsage = 0;
				DListIterator<Tree<XmlNode*>*> childIter = (*currentNode->children).getIterator();

				while (childIter.isValid())
				{
					FileNode* fileNode = dynamic_cast<FileNode*>(childIter.item()->data);

					if (fileNode != nullptr)
					{
						totalMemoryUsage += fileNode->getFileLength();
					}

					queue.push(childIter.item());
					childIter.advance();
				}

				return totalMemoryUsage;
			}
			else
			{
				DListIterator<Tree<XmlNode*>*> childIter = (*currentNode->children).getIterator();
				while (childIter.isValid())
				{
					queue.push(childIter.item());
					childIter.advance();
				}
			}
		}
	}

	return -1;
}












 
