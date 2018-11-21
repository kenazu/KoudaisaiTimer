#pragma once
# include <Siv3D.hpp>
# include "Button.h"


class Clock
{
	Point m_pos;
	Size m_size;

	String m_name;

public:
	Clock() {}
	Clock(const Point& _pos, const Size& _size, const String& _name) :m_pos(_pos), m_size(_size), m_name(_name)
	{

	}

	Point getCenter()const
	{
		return m_pos.movedBy(m_size / 2);
	}

	Point getClockCenter()const
	{
		return m_pos.movedBy(m_size / 2).movedBy(0,-30);
	}

	void update()
	{

	}

	void draw()const
	{
		Circle(getClockCenter(), 8).draw();

		for (auto i : step(12))
		{
			Circle(getClockCenter() + Circular(70, Radians(i * 30)), i % 3 ? 5 : 7).draw();
		}

		const DateTime time = DateTime::Now();

		// éûêj
		const double hourRadian = (time.hour*60.0 + time.minute) / 720.0 * TwoPi;
		Line(getClockCenter(), getClockCenter() + Circular(40, hourRadian)).draw(5);

		// ï™êj
		const double minuteRadian = time.minute / 60.0 * TwoPi;
		Line(getClockCenter(), getClockCenter() + Circular(50, minuteRadian)).draw(3);

		// ïbêj
		const double secondRadian = time.second / 60.0 * TwoPi;
		Line(getClockCenter(), getClockCenter() + Circular(60, secondRadian)).draw(2);

		FontAsset(L"Timer")(time.format(L"HH:mm")).drawAt(getClockCenter().movedBy(0, m_size.y / 2 - 10));
	}
};