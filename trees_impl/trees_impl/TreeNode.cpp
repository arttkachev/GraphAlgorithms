#include "stdafx.h"
#include "TreeNode.h"

template<typename T>
TreeNode<T>::TreeNode(T nodeData)
{
	this->setData(nodeData);
}

template<typename T>
TreeNode<T>::~TreeNode()
{	
}

template<typename T>
void TreeNode<T>::setData(T dataToSet)
{
	data = dataToSet;
}

template<typename T>
void TreeNode<T>::setParent(TreeNode<T>* parentToSet)
{
	parent = parentToSet;
}

template<typename T>
void TreeNode<T>::addChild(TreeNode<T>* childToAdd)
{
	this->children.push_back(childToAdd);
	childToAdd->setParent(this);
}

template<typename T>
std::string TreeNode<T>::printDebug()
{
	std::string debugString;	
	debugString.append(this->getData());	
	if (this->children.size() > 0)
	{
		debugString += "(";
		for (size_t i = 0; i < this->children.size(); i++)
		{
			debugString += this->children[i]->printDebug();			
			if (i < this->children.size() - 1)
			{
				debugString += ", ";
			}
		}			
		debugString += ")";		
	}	
	return debugString;
}

