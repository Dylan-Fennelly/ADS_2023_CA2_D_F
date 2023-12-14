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

int TreeManager::calculateMemoryUsage(string path,bool deep)
{
	switch (deep)
	{
		case true:
			return calculateMemoryUsageDeep(path);
			break;
		case false:
			return calculateMemoryUsageLocalToFile(path);
			break;
	}

}

int TreeManager::calculateMemoryUsageLocalToFile(string path)
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
int TreeManager::calculateMemoryUsageDeep(string path)
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

	int totalMemoryUsage = 0;  // Total memory usage for all files in folders below the specified folder

	// Check if there is only one argument, and it matches the root
	if (pathVector.size() == 1 && pathVector[0] == xmlTree->data->getName())
	{
		cout << "Calculating total memory usage for the entire tree:" << endl;
		calculateTotalMemoryUsage(xmlTree, totalMemoryUsage);
		cout << "Total memory usage: " << totalMemoryUsage << endl;
		return totalMemoryUsage;
	}

	while (!queue.empty())
	{
		Tree<XmlNode*>* currentNode = queue.front();
		queue.pop();

		cout << "Current Node: " << currentNode->data->getName() << endl;

		// Check if the current node matches the current path element
		if (pathVector.empty() || currentNode->data->getName() == pathVector.front())
		{
			// Remove the front element of the path vector
			if (!pathVector.empty())
			{
				pathVector.erase(pathVector.begin());
			}

			// If this is the last level of the path, start calculating memory
			if (pathVector.empty())
			{
				// Iterate through children and add their memory usage to the total
				DListIterator<Tree<XmlNode*>*> childIter = (*currentNode->children).getIterator();
				while (childIter.isValid())
				{
					FileNode* fileNode = dynamic_cast<FileNode*>(childIter.item()->data);

					if (fileNode != nullptr)
					{
						cout << "File: " << fileNode->getName() << " " << fileNode->getFileLength() << "Bytes  " << fileNode->getType() << endl;
						totalMemoryUsage += fileNode->getFileLength();
					}

					// Enqueue children for further exploration
					queue.push(childIter.item());
					childIter.advance();
				}

				// Return the total memory usage for the folder
				cout << "Total memory usage: " << totalMemoryUsage << endl;
				return totalMemoryUsage;
			}
			else
			{
				// Enqueue children for further exploration
				DListIterator<Tree<XmlNode*>*> childIter = (*currentNode->children).getIterator();
				while (childIter.isValid())
				{
					queue.push(childIter.item());
					childIter.advance();
				}
			}
		}
		else
		{
			// Enqueue children for further exploration
			DListIterator<Tree<XmlNode*>*> childIter = (*currentNode->children).getIterator();
			while (childIter.isValid())
			{
				queue.push(childIter.item());
				childIter.advance();
			}
		}
	}

	// If the path was not found, return -1
	cout << "Path not found" << endl;
	return -1;
}

void TreeManager::calculateTotalMemoryUsage(Tree<XmlNode*>* subtree, int& totalMemoryUsage)
{
	// Recursively calculate total memory usage for the entire subtree
	DListIterator<Tree<XmlNode*>*> childIter = (*subtree->children).getIterator();
	while (childIter.isValid())
	{
		FileNode* fileNode = dynamic_cast<FileNode*>(childIter.item()->data);

		if (fileNode != nullptr)
		{
			totalMemoryUsage += fileNode->getFileLength();
		}

		// Recursive call for child subtree
		calculateTotalMemoryUsage(childIter.item(), totalMemoryUsage);
		childIter.advance();
	}
}
//string TreeManager::findFileOrFolder(string filename)
//{
//	if (xmlTree == nullptr || filename == "")
//	{
//		return "Tree is empty or filename is empty.";
//	}
//
//	// Create a stack for DFS traversal
//	stack<TreeIterator<XmlNode*>> dfsStack;
//
//	// Start DFS from the root
//	TreeIterator<XmlNode*> rootIterator(xmlTree);
//	dfsStack.push(rootIterator);
//
//	while (!dfsStack.empty())
//	{
//		// Get the top node from the stack
//		TreeIterator<XmlNode*> currentIterator = dfsStack.top();
//		dfsStack.pop();
//
//		// Check if the current node's data matches the specified filename
//		if (currentIterator.node->data->getName() == filename)
//		{
//			// Generate the path by backtracking through the stack
//			string path = "";
//			while (!dfsStack.empty())
//			{
//				path = "/" + currentIterator.node->data->getName() + path;
//				currentIterator = dfsStack.top();
//				dfsStack.pop();
//			}
//
//			// Add the root node's name to the path
//			path = currentIterator.node->data->getName() + path;
//
//			return path;
//		}
//
//		// Push children onto the stack for further exploration
//		if (currentIterator.childValid())
//		{
//			dfsStack.push(currentIterator);
//			dfsStack.push(TreeIterator<XmlNode*>(currentIterator.childIter.currentNode->data));
//		}
//	}
//
//	return "File or folder not found.";
//}
string TreeManager::findFileOrFolderRecursive(TreeIterator<XmlNode*> iterator, string partialFilename)
{
	// Base case: check if the current node is the file or folder we are looking for
	if (xmlTree == nullptr|| partialFilename.empty())
	{
		return "Tree is empty or filename is empty.";
	}


	// Check if the current node's name contains the specified partialFilename
	if (iterator.node->data->getName().find(partialFilename) != string::npos) {
		// If found, generate the path
		return iterator.node->data->getName();
	}

	// Recursively search in the children
	DListIterator<Tree<XmlNode*>*> childIter = (*iterator.node->children).getIterator();
	while (childIter.isValid()) {
		string childPath = findFileOrFolderRecursive(TreeIterator<XmlNode*>(childIter.item()), partialFilename);
		if (childPath != "File or folder not found.") {
			// Concatenate the current node's name and return the path
			return iterator.node->data->getName() + "/" + childPath;
		}
		childIter.advance();
	}

	// If not found in the current node's children, return "File or folder not found."
	return "File or folder not found.";
}

// Wrapper function to start the recursive search from the root
string TreeManager::findFileOrFolder(string partialFilename)
{
	TreeIterator<XmlNode*> rootIterator(xmlTree);
	return findFileOrFolderRecursive(rootIterator, partialFilename);
}

