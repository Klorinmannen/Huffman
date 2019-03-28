#pragma once
#include<string>


class LeafNode
{
private:

	char mSymbol;
	unsigned int mFrequency;
	std::string mBinaryCode;

public:
	LeafNode() { mSymbol = '\0'; mFrequency = 0; mBinaryCode = ""; }
	virtual ~LeafNode(){}

	void SetSymbol(const char & _symbol) { mSymbol = _symbol; }
	void SetFrequency(const unsigned int & _frequency) { mFrequency = _frequency; }
	void SetBinaryCode(const std::string & _code) { mBinaryCode = _code; }

	char GetSymbol() const { return mSymbol; }
	unsigned int GetFrequency() const { return mFrequency; }
	std::string GetBindaryCode() const { return mBinaryCode; }
/*
	bool operator<(const LeafNode & node) 
	{
		return node.GetFrequency() < mFrequency;
	}
*/

};
