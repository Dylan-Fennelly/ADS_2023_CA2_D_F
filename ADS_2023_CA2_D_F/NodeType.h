#pragma once
enum class NodeType/*This enum allows an xml node to be either a folder or a file
					 this means that a node can be stored as a base xml node and if 
					 more node specific functions are needed the node can be cast to it
					 actual type*/
{
	FOLDER,
	FILE
};