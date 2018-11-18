#pragma once
# include "SceneBase.h"
# include "Timer.h"

class TimerScene :public MyApp::Scene
{
	Array<Timer> m_timers;

	int m_timerIdx = -1;

public:

	bool load(const String& _path)
	{

	}

	void init()override
	{
		m_timers.push_back(Timer(Point(0, 0), Size(320, 270), L"PC3"));
		m_timers.push_back(Timer(Point(320, 0), Size(320, 270), L"PC4"));
		m_timers.push_back(Timer(Point(0, 270), Size(320, 270), L"PC1"));
		m_timers.push_back(Timer(Point(320, 270), Size(320, 270), L"PC2"));
		m_timers.push_back(Timer(Point(640, 270), Size(320, 270), L"VR"));
	}

	void updateIdx()
	{
		if (Input::Key1.clicked)
		{
			m_timerIdx = 0;
		}
		else if (Input::Key2.clicked)
		{
			m_timerIdx = 1;
		}
		else if (Input::Key3.clicked)
		{
			m_timerIdx = 2;
		}
		else if (Input::Key4.clicked)
		{
			m_timerIdx = 3;
		}
		else if (Input::Key5.clicked)
		{
			m_timerIdx = 4;
		}
		else if (Input::KeyTab.clicked)
		{
			m_timerIdx += 1;
			m_timerIdx %= 5;
		}
	}

	void update()
	{
		for (auto&& t : m_timers)
		{
			t.update();
		}

		updateIdx();

		if (!InRange(m_timerIdx, 0, 4))
		{
			return;
		}

		if (Input::KeyEnter.clicked || Input::KeySpace.clicked)
		{
			m_timers[m_timerIdx].startBtFunc();
		}

		else if (Input::KeyBackspace.clicked)
		{
			m_timers[m_timerIdx].resetBtFunc();
		}


	}
	void draw()const override
	{
		for (const auto& t : m_timers)
		{
			t.draw();
		}

		if (!InRange(m_timerIdx, 0, 4))
		{
			return;
		}

		m_timers[m_timerIdx].getColider().drawFrame(3, 0, Palette::Yellow);
	}
};