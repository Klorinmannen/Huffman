#include "HuffmanTree.h"

void HuffmanTree::readFromFile()
{
	std::string temp = "";
	std::fstream inStream;

	inStream.open(mPath, std::ios::in);
	while (std::getline(inStream, temp))
		mText += temp;
		
	inStream.close();

	return;
}

void HuffmanTree::writeToFile(const std::string & _fileName)
{

	std::fstream outStream;
	outStream.open(_fileName, std::ios::out);
	outStream << mBinaryCode;
	outStream.close();

	return;
}

void HuffmanTree::buildBinaryCode()
{
	mBinaryCode.clear();
	
	for (auto text = mText.begin(); text != mText.end(); ++text)
		mBinaryCode += mSymbolsMap.find(*text)->second;
	
	return;
}

void HuffmanTree::manageBinaryCode(const int & _arg)
{
	switch (_arg)
	{
	case 0:
		mBinaryCode += "0";

		break;
	case 1:
		mBinaryCode += "1";

		break;
	case -1:
		if (mBinaryCode.size() > 0)
			mBinaryCode.pop_back();

		break;
	}

	return;
}

void HuffmanTree::computeFrequency()
{
	//For each time a character in the text appears, +1 frequency.
	//For each character check if theres a frequency and if there is, store char with its frequency
	for (auto text = mText.begin(); text != mText.end(); ++text)
	{
		if (mCharsnFreq[static_cast<int>(*text)].first == '\0')
			mCharsnFreq[static_cast<int>(*text)].first = *text;

		mCharsnFreq[static_cast<int>(*text)].second += 1;
	}

	//Clean up empty spaces
	for (auto obj = mCharsnFreq.begin(); obj != mCharsnFreq.end();)
	{
		if (obj->first == '\0')
			obj = mCharsnFreq.erase(obj);
		else
			obj++;
	}

	return;
}

void HuffmanTree::buildTree()
{
	std::shared_ptr<LeafNode> pLeafOne = nullptr;
	std::shared_ptr<LeafNode> pLeafTwo = nullptr;
	std::shared_ptr<InternalNode> pInternalPtr = nullptr;

	for (unsigned int i = 0; i < mCharsnFreq.size(); i++)
	{
		pLeafOne = std::make_shared<LeafNode>();
		pLeafOne->SetWeigth(mCharsnFreq[i].second);
		pLeafOne->SetSymbol(mCharsnFreq[i].first);
		mNodes.push_back(pLeafOne);
	}

	std::sort(mNodes.begin(), mNodes.end(), Compare());

	while (mNodes.size() > 1)
	{
		pLeafOne = mNodes.back();
		mNodes.pop_back();
		if (mNodes.size() > 0)
		{
			pLeafTwo = mNodes.back();
			mNodes.pop_back();

			pInternalPtr = std::make_shared<InternalNode>();
			pInternalPtr->SetWeigth(pLeafOne->GetWeight() + pLeafTwo->GetWeight());
			pInternalPtr->SetLeftChild(pLeafOne);
			pInternalPtr->SetRightChild(pLeafTwo);

			mNodes.push_back(pInternalPtr);
		}
		else
		{
			pInternalPtr = std::make_shared<InternalNode>();
			pInternalPtr->SetWeigth(pLeafOne->GetWeight());
			pInternalPtr->SetLeftChild(pLeafOne);
		}

		std::sort(mNodes.begin(), mNodes.end(), Compare());
	}

	mRoot = std::dynamic_pointer_cast<InternalNode>(mNodes.front());
	mNodes.pop_front();
 
	pLeafOne.reset();
	pLeafTwo.reset();
	pInternalPtr.reset();

	return;
}

void HuffmanTree::traverseTree(const std::shared_ptr<LeafNode>& _node, const int & _arg)
{
	std::shared_ptr<InternalNode> temp = nullptr;
	temp = std::dynamic_pointer_cast<InternalNode>(_node);

	switch (_arg)
	{

	case FLAGS::CREATE_BINARY_CODE:
		if (temp)
		{
			manageBinaryCode(0);
			traverseTree(temp->GetLeftChild(), FLAGS::CREATE_BINARY_CODE);
			manageBinaryCode(1);
			traverseTree(temp->GetRightChild(), FLAGS::CREATE_BINARY_CODE);

		}
		else
		{
			_node->SetBinaryCode(mBinaryCode);
			mSymbolsMap[_node->GetSymbol()] = mBinaryCode;
		}

		manageBinaryCode(-1);

		break;
	case FLAGS::PRINT:
		if (temp)
		{
			traverseTree(temp->GetLeftChild(), FLAGS::PRINT);
			traverseTree(temp->GetRightChild(), FLAGS::PRINT);
		}
		else
		{
			std::cout <<
				"Binary code: " <<
				_node->GetSymbol() <<
				" " <<
				_node->GetWeight() <<
				". " <<
				_node->GetBindaryCode() <<
				std::endl;
		}

		break;
	}


	return;
}

void HuffmanTree::init()
{
	mCharsnFreq.resize(ASCII_SIZE);
	for (auto obj = mCharsnFreq.begin(); obj != mCharsnFreq.end(); ++obj)
		*obj = std::make_pair('\0', 0);

}

void HuffmanTree::reset()
{
	mText.clear();
	mPath.clear();
	mBinaryCode.clear();
	mRoot.reset();
	mCharsnFreq.clear();
	mSymbolsMap.clear();
	mNodes.clear();

	return;
}

void HuffmanTree::printCompression()
{
	std::cout << "Bits uncompressed: " << mText.size() * 8 << ". Bits compressed: " << mCharsnFreq.size() * 8 << ". " << std::endl;
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
	if (mRoot)
		reset();

	mText = _text;
	computeFrequency();
	buildTree();
	traverseTree(mRoot, FLAGS::CREATE_BINARY_CODE);

	return true;
}

bool HuffmanTree::MainFromTextFile(const std::string & _path)
{
	if (_path.empty())
		return false;
	if (mRoot)
		reset();

	mPath = _path;
	readFromFile();
	computeFrequency();
	buildTree();
	traverseTree(mRoot, FLAGS::CREATE_BINARY_CODE);
	buildBinaryCode();

#ifdef _DEBUG
	printCompression();
	PrintTree();
#endif

	return true;
}

bool HuffmanTree::WriteBinaryCodeToFile(const std::string & _fileName)
{
	if (mBinaryCode.empty() || _fileName.empty())
		return false;

	writeToFile(_fileName);
	return true;
}

bool HuffmanTree::PrintTree()
{
	if (!mRoot)
		return false;
	
	traverseTree(mRoot, FLAGS::PRINT);
	return true;
}

bool HuffmanTree::ResetTree()
{
	reset();
	return true;
}

std::string HuffmanTree::GetBinaryCode() const
{
	return mBinaryCode;
}
