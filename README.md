# ADS_2023_CA2_D_F
This project is for Ca2 of my Algoritms and Data Structures Module.
## Description of Assignment
This assignment was for the purpose of learning how to use the Tree and TreeIterator classes.  
The assignment was to create a tree from an .xml file that has a very particular format:

### The format of the .xml file is as follows:<BR>
```xml
<dir>
  <name>ADS_Single_LinkedList_Exercises</name>
	<dir>
	  <name>.git</name>
		<file>
		  <name>config</name>
		  <length>353 b</length>
		  <type>config</type>
		</file>
		<file>
		  <name>description</name>
		  <length>73 b</length>
		  <type>description</type>
		</file>
		<file>
		  <name>HEAD</name>
		  <length>23 b</length>
		  <type>HEAD</type>
		</file>
	</dir>
</dir>
```
We were then given a certain liberty of how to load the XML onto the Tree. 
I chose to use an Object-Oriented Approach and created a Base Class called xmlNode.
This class has 2 derived classes called xmlFile and xmlFolder. The xmlFile class has 3 attributes:

* name
* length 
* type
* 
The xmlFolder class has 1 attribute:
* name

I used a generic tree class that was provided to us by our lecturer.  
I then used the TreeIterator class for iterating through the tree.
### I used the following code to load the xml file onto the tree:
```c++
Tree<XmlNode*>* XmlParser::parseXml(string& xml)
{
   
    Tree<XmlNode*>* tree = nullptr;
    TreeIterator<XmlNode*> treeIterator = nullptr; // Initialize with nullptr

    istringstream xmlStream(xml);
    string line;

    while (getline(xmlStream, line))
    {
        size_t posOpeningStart = line.find_first_of('<');
        size_t posOpeningEnd = line.find_first_of('>');
        size_t posClosingStart = line.find_last_of('<');
        size_t posClosingEnd = line.find_last_of('>');

        string openingTag = line.substr(posOpeningStart + 1, posOpeningEnd - posOpeningStart - 1);

        if (openingTag == "dir")
        {
            getline(xmlStream, line);
            size_t posNameStart = line.find_first_of('>');
            size_t posNameEnd = line.find_last_of('<');
            string name = line.substr(posNameStart + 1, posNameEnd - posNameStart - 1);
            FolderNode* folderNode = new FolderNode(name);

            if (tree == nullptr)
            {
                tree = new Tree<XmlNode*>(folderNode);
                treeIterator = TreeIterator<XmlNode*>(tree);
                continue;
            }
            else
            {
                treeIterator.appendChild(folderNode);
                treeIterator.childEnd();
                treeIterator.down(); // Move down after appending the child
            }
        }
        else if (openingTag == "file")
        {
            // Read file information
            getline(xmlStream, line);
            size_t posNameStart = line.find_first_of('>');
            size_t posNameEnd = line.find_last_of('<');
            string name = line.substr(posNameStart + 1, posNameEnd - posNameStart - 1);

            getline(xmlStream, line);
            size_t posLengthStart = line.find_first_of('>');
            size_t posLengthEnd = line.find_last_of('<');
            int length = stoi(line.substr(posLengthStart + 1, posLengthEnd - posLengthStart - 2));

            getline(xmlStream, line);
            size_t posTypeStart = line.find_first_of('>');
            size_t posTypeEnd = line.find_last_of('<');
            string type = line.substr(posTypeStart + 1, posTypeEnd - posTypeStart - 1);

            FileNode* fileNode = new FileNode(name, length, type);

            // Append fileNode to the current folder
            treeIterator.appendChild(fileNode);
        }
        else if (openingTag == "/dir")
        {
            // Move up after encountering "/dir"
            treeIterator.up();
        }
    }

    return tree;
}
```
I also created a TreeManager class that holds the tree and alsos the user to interact with the tree, with such interactions
being printing the tree pruning the tree of any folders that are empty and also searching for a file by name.
Using this I was able to create a menu driven program that allows the user to interact with the tree.
### The TreeManager class(.h) is as follows:
```c++
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
```
>## Reflections:
>>I found this assignment to be very interesting and I learned a lot about trees and how to use them. I also learned a lot about
using depth first search and breadth first search. 
I did find the intial loading of the xml file onto the tree to be quite difficult and I had to do a lot of research to figure out
how to do it. I also found the pruning of the tree to be quite difficult and it took many attempts to ger it in working order.
I feel that i grew a new understanding of unit testing and how to use it, I found that with the complexity of this assignment
having stable tests to instantly check if my code was working was very helpful.
I wasnt able to implement SFML in time for the deadline, but I do plan on implementing it in the future.
## References
https://cplusplus.com/  
https://www.geeksforgeeks.org/





