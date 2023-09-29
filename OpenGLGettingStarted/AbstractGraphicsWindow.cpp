#include "AbstractGraphicsWindow.h"

AbstractGraphicsWindow::AbstractGraphicsWindow(string title, int width, int height) :
	m_title(title), m_width(width), m_height(height), backgroundColor({0.0f, 0.0f, 0.0f})
{
}

AbstractGraphicsWindow::~AbstractGraphicsWindow()
{
}
