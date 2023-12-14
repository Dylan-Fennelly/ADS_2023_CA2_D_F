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
#include "FilePath.h"
#include<thread>
#include<chrono>

using namespace std;

void displayMenu();
void loadXml(TreeManager& treeManager);
void loadXmlOptions();
//If you want the menu to go fast ctrl F and replace all this_thread::sleep_for(std::chrono::milliseconds(150));
//with this_thread:://sleep_for(std::chrono::milliseconds(200));
int main()
{
    XmlParser* xmlParser = new XmlParser();
    XmlFileLoader* xmlFileLoader = new XmlFileLoader();
    TreeManager treeManager(xmlParser, xmlFileLoader);

    int choice;
    string filename;
    string folderName;
    bool deep;

    while (true)
    {
        displayMenu();
        this_thread::sleep_for(std::chrono::milliseconds(150));
        cout << "Enter your choice: ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid choice." << endl;
            this_thread::sleep_for(std::chrono::milliseconds(150));
            continue;
        }

        switch (choice)
        {
        case 1:
            loadXml(treeManager);
            break;
        case 2:
            treeManager.displayTree();
            break;
        case 3:
            this_thread::sleep_for(std::chrono::milliseconds(150));
            cout << "Number of items in the tree: " << treeManager.countItemsinTree() << endl;
            this_thread::sleep_for(std::chrono::milliseconds(150));
            cout << "\n";
            break;
        case 4:
            this_thread::sleep_for(std::chrono::milliseconds(150));
            cout << "Enter the name of the file or folder: ";
            cin >> filename;
            this_thread::sleep_for(std::chrono::milliseconds(150));
            cout << treeManager.findFileOrFolder(filename) << endl;
            cout << "\n";
            break;
        case 5:
            this_thread::sleep_for(std::chrono::milliseconds(150));
            cout << "Enter the name of folder: ";
            this_thread::sleep_for(std::chrono::milliseconds(150));
            cin >> folderName;
            this_thread::sleep_for(std::chrono::milliseconds(150));
            cout << "Enter 1 for deep search or 0 for local search: ";
            this_thread::sleep_for(std::chrono::milliseconds(150));
            cin >> deep;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a valid choice." << endl;
                cout << "\n";
                break;
            }
            this_thread::sleep_for(std::chrono::milliseconds(150));
            cout << "Memory usage: " << treeManager.calculateMemoryUsage(folderName, deep) << endl;
            cout << "\n";
            break;
        case 6:
            cout << "Enter the name of the folder: ";
            cin >> folderName;
            treeManager.displayFolderContents(folderName);
            break;
        case 7:
            treeManager.pruneTree();
            break;
        case 8:
            exit(0);
        default:
            cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
            break;
        }
    }

    return 0;
}

void loadXml(TreeManager& treeManager)
{
    loadXmlOptions();
    int choice;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "Enter your choice: ";
    cin >> choice;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter a valid choice." << endl;
        return;
    }

    switch (choice)
    {
    case 1:
        treeManager.loadTreeFromXML(FilePath::VS_SAMPLE_SIMPLE);
        break;
    case 2:
        treeManager.loadTreeFromXML(FilePath::VS_SAMPLE);
        break;
    case 3:
        treeManager.loadTreeFromXML(FilePath::UNITY_SAMPLE);
        break;
    default:
        cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
        break;
    }
}

void displayMenu()
{
    cout << "------------------------" << endl;
    cout << "        Main Menu       " << endl;
    cout << "------------------------" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "1. Load Tree from XML" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "2. Display Tree" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "3. Count Items in Tree" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "4. Find File or Folder" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "5. Calculate Memory Usage" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "6. Display Folder Contents" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "7. Prune Tree" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "8. Exit" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "------------------------" << endl;
}

void loadXmlOptions()
{
    cout << "------------------------" << endl;
    cout << "      Load XML Menu     " << endl;
    cout << "------------------------" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "1. Load Simple VS Example" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "2. Load VS Example" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "3. Load Unity Example" << endl;
    this_thread::sleep_for(std::chrono::milliseconds(150));
    cout << "------------------------" << endl;
}
