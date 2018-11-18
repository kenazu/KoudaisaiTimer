#pragma once
# include <Siv3D.hpp>
# include "Button.h"

class Timer
{
	Stopwatch m_timer;
	Button m_startBt;
	Button m_resetBt;

	Point m_pos;
	Size m_size;

	String m_name;

	static const int DEADLINE_S = 10 * 60;

public:

	Timer() {}
	Timer(const Point& _pos,const Size& _size,const String& _name):m_pos(_pos),m_size(_size),m_name(_name)
	{
		m_startBt = Button(Rect(100, 30).setCenter(m_size.x / 4, 220).movedBy(_pos), L"スタート");
		m_resetBt = Button(Rect(100, 30).setCenter(m_size.x / 4 * 3, 220).movedBy(_pos), L"リセット");
	}

	void start() { m_timer.start(); }

	void pause() { m_timer.pause(); }

	void restart() { m_timer.restart(); }

	void reset() { m_timer.reset(); }

	Rect getColider()const
	{
		return Rect(m_pos, m_size);
	}

	Point getCenter()const
	{
		return getColider().center;
	}

	String getTime()const
	{
		const String min = Pad(m_timer.min() % 60, { 2,L'0' });
		const String sec = Pad(m_timer.s() % 60, { 2,L'0' });

		return Format(min, L":", sec);
	}

	bool isTimeOver()const
	{
		return m_timer.s() > DEADLINE_S;
	}

	void startBtFunc()
	{
		if (m_timer.isPaused() || !m_timer.isActive())
		{
			start();
			m_startBt.setName(L"ポーズ");

		}

		else if (m_timer.isActive())
		{
			pause();
			m_startBt.setName(L"スタート");
		}
	}

	void resetBtFunc()
	{
		reset();
		m_startBt.setName(L"スタート");
	}

	void update()
	{
		if (m_startBt.leftClicked())
		{
			startBtFunc();
		}

		if (m_resetBt.leftClicked())
		{
			resetBtFunc();
		}
	}

	void draw()const
	{
		if (isTimeOver())
		{
			getColider().draw(Color(Palette::Red, 200));
		}

		getColider().drawFrame(1, 0, Palette::White);

		const Rect nameRect = Rect(m_pos, m_size.x, 50).drawFrame(1, 0, Palette::White);
		FontAsset(L"TimerName")(m_name).drawAt(nameRect.center);

		const Rect timeRect = Rect(150, 70).setCenter(getCenter()).drawFrame(1, 0, Palette::White);
		FontAsset(L"Timer")(getTime()).drawAt(timeRect.center);


		

		m_startBt.draw();
		m_resetBt.draw();
	}

};
