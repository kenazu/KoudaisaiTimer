#pragma once
# include <Siv3D.hpp>
# include "Button.h"

class Timer
{
	Stopwatch m_timer;
	Button m_startBt;
	Button m_resetBt;
	static const int DEADLINE_S = 10 * 60;


protected:
	Point m_pos;
	Size m_size;

	String m_name;

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

private:

	bool isCalledStartBt = false;
	bool isCalledResetBt = false;

	void startBtFunc()
	{
		if (!m_startBt.isEnabled())
		{
			return;
		}

		if (m_timer.isPaused() || !m_timer.isActive())
		{
			start();
			m_startBt.setName(L"ポーズ");
			m_resetBt.setEnabled(false);

		}

		else if (m_timer.isActive())
		{
			pause();
			m_startBt.setName(L"スタート");
			m_resetBt.setEnabled(true);

		}
	}

	void resetBtFunc()
	{
		if (!m_resetBt.isEnabled())
		{
			return;
		}

		reset();
		m_startBt.setName(L"スタート");
	}

public:

	void callStartBt()
	{
		startBtFunc();
		isCalledStartBt = true;
	}

	void callResetBt()
	{
		resetBtFunc();
		isCalledResetBt = true;
	}

	void update()
	{
		isCalledStartBt = false;
		isCalledResetBt = false;

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

		const Rect timeRect = Rect(150, 70).setCenter(getCenter()).drawFrame(1, 0, (!m_timer.isPaused() && m_timer.isActive()) ? Palette::Red : Palette::White);
		FontAsset(L"Timer")(getTime()).drawAt(timeRect.center);


		FontAsset(L"TimerText")(L"Space").drawAt(m_startBt.getColider().center.movedBy(0, 30));
		FontAsset(L"TimerText")(L"Shift").drawAt(m_resetBt.getColider().center.movedBy(0, 30));

		m_startBt.draw();
		m_resetBt.draw();

		if (isCalledStartBt && m_startBt.isEnabled())
		{
			m_startBt.drawPushed();
		}

		if (isCalledResetBt && m_resetBt.isEnabled())
		{
			m_resetBt.drawPushed();
		}
	}

};
