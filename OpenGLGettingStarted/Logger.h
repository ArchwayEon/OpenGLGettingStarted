#pragma once
#include <vector>
#include <string>
class Logger
{
protected:
	std::vector<std::string> m_log;

public:
	void Log(const std::string& message);

	const std::vector<std::string> GetLog() { return m_log; }
};

