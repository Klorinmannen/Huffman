#pragma once
#include<string>
#include<fstream>

class FileReader
{
private:
	std::string mText;

public:
	FileReader()
	{

	}
	~FileReader()
	{

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

	std::string GetText() const
	{
		return mText;
	}
	
	void Reset()
	{
		mText.clear();
	}
};