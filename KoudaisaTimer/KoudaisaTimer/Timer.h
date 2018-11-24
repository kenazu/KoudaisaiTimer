#pragma once
# include <Siv3D.hpp>
# include "Button.h"
# include "DrawArea.h"

class Timer :public DrawArea
{
	Stopwatch m_timer;
	Button m_startBt;
	Button m_resetBt;
	static const int DEADLINE_S = 10 * 60;

	int m_initMin;
	int m_initSec;
public:

	Timer() {}

	Timer(const Point& _pos, const Size& _size, const String& _name,int _initMin=0,int _initSec = 0) :
		DrawArea(_pos, _size, _name),m_initMin(_initMin),m_initSec(_initSec)
	{
		m_startBt = Button(Rect(100, 30).setCenter(m_size.x / 4, 220).movedBy(_pos), L"スタート");
		m_resetBt = Button(Rect(100, 30).setCenter(m_size.x / 4 * 3, 220).movedBy(_pos), L"リセット");
	}

	void setInitMin(int _initMin)
	{
		m_initMin = _initMin;
	}

	void setInitSec(int _initSec)
	{
		m_initSec = _initSec;
	}


	void start() { m_timer.start(); }

	void pause() { m_timer.pause(); }

	void restart() { m_timer.restart(); }

	void reset() { m_timer.reset(); }

	String getTime()const
	{
		const int sec = m_timer.s() + m_initSec + m_initMin * 60;

		const String minStr = Pad(sec / 60, { 2,L'0' });
		const String secStr = Pad(sec % 60, { 2,L'0' });

		return Format(minStr, L":", secStr);
	}

	bool isTimeOver()const
	{
		return m_timer.s() + m_initSec + m_initMin * 60 > DEADLINE_S;
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
		m_initMin = 0;
		m_initSec = 0;


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

	void update()override
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

	void draw()const override
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
