#include "HuffmanTree.h"

void HuffmanTree::computeFrequency()
{
	//For each time a character in the text appears, +1 frequency.
	for (auto text = mText.begin(); text != mText.end(); ++text)
	{
		mCalcFrequency[static_cast<int>(*text)] += 1;
	}

	//For each character check if theres a frequency and if there is, store sign + freq in parallel.
	for (unsigned int i = 0; i < mCalcFrequency.size(); i++)
	{
		if (mCalcFrequency[i] != 0)
		{
			mCharacters.push_back(static_cast<char>(i));
			mFrequency.push_back(mCalcFrequency[i]);
		}
	}
}

void HuffmanTree::buildTree()
{
	std::shared_ptr<LeafNode> pLeafOne = nullptr;
	std::shared_ptr<LeafNode> pLeafTwo = nullptr;
	std::shared_ptr<InternalNode> pInternalPtr = nullptr;

	for (unsigned int i = 0; i < mCharacters.size(); i++)
	{
		pLeafOne = std::make_unique<LeafNode>();
		pLeafOne->SetFrequency(mFrequency[i]);
		pLeafOne->SetSymbol(mCharacters[i]);
		mNodes.push(pLeafOne);
	}

	//std::sort(mNodes.begin(), mNodes.end(), Compare());

	while (mNodes.size() > 1)
	{
		pLeafOne = mNodes.top();
		mNodes.pop();
		if (mNodes.size() > 0)
		{
			pLeafTwo = mNodes.top();
			mNodes.pop();

			pInternalPtr = std::make_shared<InternalNode>();
			pInternalPtr->SetFrequency(pLeafOne->GetFrequency() + pLeafTwo->GetFrequency());
			pInternalPtr->SetLeftChild(pLeafOne);
			pInternalPtr->SetRightChild(pLeafTwo);

			mNodes.push(pInternalPtr);
		}
		else
		{
			pInternalPtr = std::make_shared<InternalNode>();
			pInternalPtr->SetFrequency(pLeafOne->GetFrequency());
			pInternalPtr->SetLeftChild(pLeafOne);
		}

		//std::sort(mNodes.begin(), mNodes.end(), Compare());
	}

	mRoot = mNodes.top();
	mNodes.pop();
 
	pLeafOne.reset();
	pLeafTwo.reset();
	pInternalPtr.reset();
}

void HuffmanTree::buildBinaryCode(const std::shared_ptr<LeafNode> & _node)
{
	std::shared_ptr<InternalNode> temp = nullptr; 
	temp = std::dynamic_pointer_cast<InternalNode>(_node);
	
	if (temp != nullptr)
	{
		mBinaryCode += "0";
		buildBinaryCode(temp->GetLeftChild());
		mBinaryCode += "1";
		buildBinaryCode(temp->GetRightChild());

		return;
	}
	if (_node != nullptr)
	{
		_node->SetBinaryCode(mBinaryCode);
		if (mBinaryCode.size() > 0)
			mBinaryCode.pop_back();
	}

}

void HuffmanTree::init()
{
	for (unsigned int i = 0; i < ASCII_SIZE; i++)
	{
		mCalcFrequency.push_back(0);
	}
}	

HuffmanTree::HuffmanTree()
{
	ASCII_SIZE = 256;
	init();
}

HuffmanTree::HuffmanTree(unsigned int _ascii_size)
{
	ASCII_SIZE = _ascii_size;
	init();
}

HuffmanTree::~HuffmanTree()
{
}

bool HuffmanTree::MainFromString(const std::string & _text)
{
	if (_text.empty())
		return false;

	mText = _text;
	computeFrequency();
	buildTree();
	buildBinaryCode(mRoot);

	return true;
}

bool HuffmanTree::MainFromTextFile(const std::string & _path)
{
	if (_path.empty())
		return false;

	mPath = _path;


	return true;
}

bool HuffmanTree::PrintTree()
{
	return false;
}

bool HuffmanTree::DeleteTree()
{
	return false;
}
