// trees_impl.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "TreeNode.h"

int main()
{
	// create a tree
	TreeNode<std::string>* root = new TreeNode<std::string>("root");
	TreeNode<std::string>* node1 = new TreeNode<std::string>("node1");
	TreeNode<std::string>* node2 = new TreeNode<std::string>("node2");
	TreeNode<std::string>* node3 = new TreeNode<std::string>("node3");
	TreeNode<std::string>* leaf1_1 = new TreeNode<std::string>("leaf1_1");
	TreeNode<std::string>* leaf1_2 = new TreeNode<std::string>("leaf1_2");
	TreeNode<std::string>* leaf1_3 = new TreeNode<std::string>("leaf1_3");
	TreeNode<std::string>* leaf2_1 = new TreeNode<std::string>("leaf2_1");
	TreeNode<std::string>* leaf2_2 = new TreeNode<std::string>("leaf2_2");
	TreeNode<std::string>* leaf3_1 = new TreeNode<std::string>("leaf3_1");

	// set a tree structure
	root->addChild(node1);
	root->addChild(node2);
	root->addChild(node3);

	node1->addChild(leaf1_1);
	node1->addChild(leaf1_2);
	node1->addChild(leaf1_3);

	node2->addChild(leaf2_1);
	node2->addChild(leaf2_2);

	node3->addChild(leaf3_1);

	// print out debug
	std::cout << "Simple Tree Implemented With C++" << std::endl;
	std::cout << std::string(2, '\n');
	std::cout << root->printDebug() << std::endl;

	// program termination
	while (true)
	{
		std::string q;
		std::cout << std::string(2, '\n');
		std::cout << "Please, type 'q' and press 'Enter' to exit" << std::endl;
		std::cin >> q;
		if (q == "q")
		{
			return 0;
		}
	}    
}

