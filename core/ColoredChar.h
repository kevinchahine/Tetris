#pragma once

#include <iostream>
#include <iocolor/iocolor.h>

class ColoredChar
{
public:
	ColoredChar() = default;
	ColoredChar(char character, uint8_t color) :
		m_character(character),
		m_color(color) {}
	ColoredChar(char character, char fgColor, uint8_t bgColor) :
		m_character(character),
		m_color(iocolor::calcColor(fgColor, bgColor)) {}
	ColoredChar(const ColoredChar &) = default;
	ColoredChar(ColoredChar &&) noexcept = default;
	virtual ~ColoredChar() noexcept = default;
	ColoredChar & operator=(const ColoredChar &) = default;
	ColoredChar & operator=(ColoredChar &&) noexcept = default;

	char & character() { return m_character; }
	const char & character() const { return m_character; }

	uint8_t & color() { return m_color; }
	const uint8_t & color() const { return m_color; }

	friend std::ostream & operator<<(std::ostream & os, const ColoredChar & cc) {
		os << iocolor::setcolor(cc.color())
			<< cc.character();

		return os;
	}

private:

	char m_character = char();
	uint8_t m_color = iocolor::WHITE;	// fg: white, bg: black
};
