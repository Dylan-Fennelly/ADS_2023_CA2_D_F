#pragma once

#include <iostream>
enum class NodeType/*This enum allows an xml node to be either a folder or a file
					 this means that a node can be stored as a base xml node and if 
					 more node specific functions are needed the node can be cast to it
					 actual type*/
{
	FOLDER,
	FILE
};
inline std::ostream& operator<<(std::ostream& os, const NodeType& type) {
    switch (type) {
    case NodeType::FOLDER:
        os << "FOLDER";
        break;
    case NodeType::FILE:
        os << "FILE";
        break;
    }
    return os;
}