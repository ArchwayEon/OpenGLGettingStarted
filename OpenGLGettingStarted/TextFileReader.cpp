#include "TextFileReader.h"
#include <sstream>
#include <fstream>

TextFileReader::TextFileReader() : 
	m_filePath(""), m_data("")
{
}

TextFileReader::~TextFileReader()
{
}

bool TextFileReader::Read()
{
    std::stringstream ss;
    std::ifstream fin;
    fin.open(m_filePath.c_str());
    if (fin.fail()) {
        ss << "Could not open: " << m_filePath << std::endl;
        getline(ss, m_error);
        return false;
    }

    m_data = "";
    std::string line;
    while (!fin.eof()) {
        getline(fin, line);
        Trim(line);
        if (line != "") { // Skip blank lines
            m_data += line + "\n";
        }
    }
    fin.close();
    return true;
}

void TextFileReader::Trim(std::string& str)
{
    const std::string delimiters = " \f\n\r\t\v";
    str.erase(str.find_last_not_of(delimiters) + 1);
    str.erase(0, str.find_first_not_of(delimiters));
}
