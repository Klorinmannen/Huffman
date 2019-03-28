#pragma once
#include<queue>
#include<vector>
#include<iostream>
#include<fstream>
#include"InternalNode.h"

class HuffmanTree
{
private:
	class Compare
	{
	public:
		bool operator()(const std::shared_ptr<LeafNode> & lhs, const std::shared_ptr<LeafNode> & rhs) const
		{
			return lhs->GetFrequency() < rhs->GetFrequency();
		}
	};

	std::priority_queue<
		std::shared_ptr<LeafNode>, 
		std::vector<std::shared_ptr<LeafNode>>, 
		Compare> mNodes;
	
	//std::deque<std::shared_ptr<LeafNode>> mNodes;
	std::shared_ptr<LeafNode> mRoot;
	std::vector<unsigned int> mCalcFrequency;
	std::vector<std::shared_ptr<LeafNode>> s;

	//**** runs in parallel - maybe use a touple?
	std::vector<char> mCharacters;
	std::vector<unsigned int> mFrequency;
	//****

	std::string mBinaryCode;
	std::string mText;
	std::string mPath;
	unsigned int ASCII_SIZE;


	void computeFrequency();
	void buildTree();
	void buildBinaryCode(const std::shared_ptr<LeafNode> & _node);

	void init();
public:
	HuffmanTree();
	HuffmanTree(unsigned int _ascii_size);
	~HuffmanTree();

	bool MainFromString(const std::string & _text);
	bool MainFromTextFile(const std::string & _path);
	bool PrintTree();
	bool DeleteTree();

};