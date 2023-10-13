#pragma once
#include <string>
class TextFileReader
{
protected:
	std::string m_filePath;
	std::string m_data;
	std::string m_error;

public:
	TextFileReader();
	~TextFileReader();
	void SetFilePath(const std::string& filePath) { m_filePath = filePath; }
	const std::string& GetData() const { return m_data; }
	const std::string& GetError() const { return m_error; }
	bool Read();
protected:
	void Trim(std::string& str);
};

