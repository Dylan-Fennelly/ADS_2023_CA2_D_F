#include "TreeManager.h"
#include <stack>
#include "FileNode.h"
#include <vector>
#include <queue>
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
		try
		{
			string xml = this->xmlFileLoader->loadFile(path);
			this->xmlTree = this->xmlParser->parseXml(xml);
		}
		catch (exception e)
		{
			cout << e.what() << endl;
			return false;
		}
        
        
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
void TreeManager::displayFolderContents(string folderName)
{
	if (xmlTree == nullptr || folderName == "")
	{
		cout << "Tree is empty or folder name is empty." << endl;
		return;
	}

	// Use findFileOrFolder to locate the specified folder
	string folderPath = findFileOrFolder(folderName);

	if (folderPath == "File or folder not found.")
	{
		cout << "Folder not found." << endl;
		return;
	}

	// Use calculateMemoryUsageLocalToFile to get the total memory usage of the folder
	int folderSize = calculateMemoryUsageLocalToFile(folderPath);

	cout << "Contents of folder '" << folderName << "':" << endl;

	// Start BFS from the root
	queue<TreeIterator<XmlNode*>> bfsQueue;
	TreeIterator<XmlNode*> rootIterator(xmlTree);
	bfsQueue.push(rootIterator);

	while (!bfsQueue.empty())
	{
		// Get the front node from the queue
		TreeIterator<XmlNode*> currentIterator = bfsQueue.front();
		bfsQueue.pop();

		// Check if the current node's name matches the specified folder name
		if (currentIterator.node->data->getName() == folderName)
		{
			// Iterate through children and print file nodes
			DListIterator<Tree<XmlNode*>*> childIter = (*currentIterator.node->children).getIterator();
			while (childIter.isValid())
			{
				FileNode* fileNode = dynamic_cast<FileNode*>(childIter.item()->data);

				if (fileNode != nullptr)
				{
					// Display the file information
					cout << fileNode->display() << endl;

					// Optionally, you can accumulate the file size to display the total size later
					// folderSize += fileNode->getFileLength();
				}

				// Enqueue children for further exploration
				bfsQueue.push(TreeIterator<XmlNode*>(childIter.item()));
				childIter.advance();
			}

			// Print the total size of the folder
			cout << "Total size: " << folderSize << " Bytes" << endl;

			// Return as we have processed the folder
			return;
		}

		// Enqueue children for further exploration
		DListIterator<Tree<XmlNode*>*> childIter = (*currentIterator.node->children).getIterator();
		while (childIter.isValid())
		{
			bfsQueue.push(TreeIterator<XmlNode*>(childIter.item()));
			childIter.advance();
		}
	}

	// If the specified folder is not found, display an appropriate message
	cout << "Folder not found." << endl;
}
void TreeManager::pruneTree()
{
	if (xmlTree == nullptr)
	{
		cout<<"Tree is empty"<<endl;
		return;
	}
	pruneTreeRecursive(xmlTree);
}

void TreeManager::pruneTreeRecursive(Tree<XmlNode*>* currentNode)
{
	if (currentNode == nullptr)
	{
		return;
	}

	DListIterator<Tree<XmlNode*>*> childIter = (*currentNode->children).getIterator();
	while (childIter.isValid())
	{
		pruneTreeRecursive(childIter.item());

		// Remove empty folders
		if (childIter.item()->data->getType() == NodeType::FOLDER && childIter.item()->children->head == nullptr)
		{
			delete childIter.item();
			childIter = currentNode->children->remove(childIter);
		}
		else
		{
			childIter.advance();
		}
	}
}





