#pragma once
#include"LeafNode.h"
#include<memory>

class InternalNode : public LeafNode
{
private:
	std::shared_ptr<LeafNode> mLeftChild;
	std::shared_ptr<LeafNode> mRightChild;
	
public:
	InternalNode() { mLeftChild = nullptr; mRightChild = nullptr; }
	virtual ~InternalNode(){}

	void SetLeftChild(const std::shared_ptr<LeafNode> & _node) { mLeftChild = _node; }
	void SetRightChild(const std::shared_ptr<LeafNode> & _node) { mRightChild = _node; }

	std::shared_ptr<LeafNode> GetLeftChild() { return mLeftChild; }
	std::shared_ptr<LeafNode> GetRightChild() { return mRightChild; }
};