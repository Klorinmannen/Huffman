#pragma once
#include<string>


class LeafNode
{
private:

	char mSymbol;
	unsigned int mWeight;
	std::string mBinaryCode;

public:
	LeafNode() { mSymbol = '\0'; mWeight = 0; mBinaryCode = ""; }
	virtual ~LeafNode(){}

	void SetSymbol(const char & _symbol) { mSymbol = _symbol; }
	void SetWeigth(const unsigned int & _frequency) { mWeight = _frequency; }
	void SetBinaryCode(const std::string & _code) { mBinaryCode = _code; }

	char GetSymbol() const { return mSymbol; }
	unsigned int GetWeight() const { return mWeight; }
	std::string GetBindaryCode() const { return mBinaryCode; }
/*
	bool operator<(const LeafNode & node) 
	{
		return node.GetWeight() < mWeight;
	}
*/

};
