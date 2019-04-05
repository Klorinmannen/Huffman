#pragma once
#include<string>
#include<fstream>

class FileReader
{
private:
	std::string mText;

public:
	FileReader() {}
	~FileReader()
	{
		mText.clear();
	}

	void ReadFile(const std::string & _path)
	{
		std::string temp = "";
		std::fstream inStream;

		inStream.open(_path, std::ios::in);
		while (std::getline(inStream, temp))
			mText += temp;

		inStream.close();

		return;
	}

	void InsertString(const std::string & _text) { mText = _text; return; } //For debugging

	std::string GetText() const { return mText; }
	
	void Clear() { mText.clear(); return; }
	void Init() { mText = ""; return; }
};