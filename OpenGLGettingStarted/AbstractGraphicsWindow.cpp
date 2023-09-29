#include "AbstractGraphicsWindow.h"

AbstractGraphicsWindow::AbstractGraphicsWindow(const string& title, int width, int height) :
	m_title(title), m_width(width), m_height(height), backgroundColor({0.0f, 0.0f, 0.0f, 1.0f})
{
}

AbstractGraphicsWindow::~AbstractGraphicsWindow()
{
}
