#pragma once
#include <vector>
#include <string> 

// class template that represents a node in the tree
template<typename T>
class TreeNode
{
public:
	TreeNode(T nodeData);
	~TreeNode();

	// public interface to communicate with this class
	void setData(T dataToSet);
	void setParent(TreeNode<T>* parentToSet);
	void addChild(TreeNode<T>* childToAdd);
	std::string printDebug();

	inline T getData() const
	{
		return data;
	}

	inline TreeNode<T>* getParent() const
	{
		return parent;
	}

	inline std::vector<TreeNode<T>*> getChildren() const
	{
		return children;
	}	

private:
	// it stores some data about a node
	T data;
	// root node
	TreeNode<T>* parent = nullptr;
	// AdjacencyList of children. Vector is being used as a data structure
	std::vector<TreeNode<T>*> children;
};

#include "TreeNode.cpp"

