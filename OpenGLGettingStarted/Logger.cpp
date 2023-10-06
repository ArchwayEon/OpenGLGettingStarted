#include "Logger.h"

void Logger::Log(const std::string& message)
{
	m_log.push_back(message);
}
