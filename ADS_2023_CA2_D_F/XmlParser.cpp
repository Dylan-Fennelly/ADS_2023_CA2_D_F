#include "XmlParser.h"
#include <sstream>
#include <stack>
#include "TreeIterator.h"
#include "FolderNode.h"
#include "FileNode.h"

bool XmlParser::validateXML(string& xmlContent) {
    istringstream xmlStream(xmlContent);
    stack<string> tagStack;

    string line;
    while (getline(xmlStream, line)) 
    {
        size_t pos = line.find('<');
        while (pos != string::npos) 
        {
            size_t endPos = line.find('>', pos);
            if (endPos != string::npos) 
            {
                string token = line.substr(pos, endPos - pos + 1);
                if (token[1] == '/')// Closing tag 
                { 
                    string closingTag = token.substr(2, token.size() - 3);
                    if (tagStack.empty() || tagStack.top() != closingTag)// Mismatched closing tag
                    {
                        return false; 
                    }
                    tagStack.pop();
                }
                else 
                { // Opening tag
                    tagStack.push(token.substr(1, endPos - pos - 1));
                }
                pos = endPos + 1;
            }
            else 
            {
                break;
            }
            pos = line.find('<', pos);
        }
    }

    return tagStack.empty(); // Stack should be empty if all tags are properly closed
}
//This function will parse an xml string and return a tree of xml nodes
//The node are either of type FileNode or FolderNode
//The folder node is represented by the <dir> tag and has a name 
//Which can be found by parseing the name attribute on the next line
//We do not construct the folder node until we have found the name
//The file node is represented by the <file> tag and has a name
//it also has length which can be found by parsing the length attribute
//but the length attribute has the letter b at the end so we have to take care 
//when parseing the length to remove the b
//The file also has type which can be found by parsing the type attribute
//The attribute are always on one line in the form <name>value</name>
//When parsing when we hit a folder node we must drop down to that level 
//and when we hit a file node we must add it to the current folder
//but it is important to bear in mind that the tree iterator 
//append the node to the child so we must use childfoward after adding the node
//to the folder
//we append to the child for all nodes
//we also
//Below is an example of the xml string that will be passed to this function
/*<dir>
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
	
	<dir>
	  <name>.vs</name>
		<dir>
		  <name>ADS_Single_LinkedList_Exercises</name>
			<dir>
			  <name>v17</name>
				
			</dir>
		</dir>
		
	</dir>
	<dir>
	  <name>Debug</name>
		<file>
		  <name>SinglyLinkedList.pdb</name>
		  <length>978944 b</length>
		  <type>pdb</type>
		</file>
		<file>
		  <name>TestSinglyLinkedList.exp</name>
		  <length>41528 b</length>
		  <type>exp</type>
		</file>
		<file>
		  <name>TestSinglyLinkedList.pdb</name>
		  <length>1945600 b</length>
		  <type>pdb</type>
		</file>
	</dir>	
</dir>

*/

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





