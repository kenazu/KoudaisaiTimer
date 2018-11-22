#pragma once
# include "SceneBase.h"
# include "Timer.h"
# include "Clock.h"

class TimerScene :public MyApp::Scene
{
	Array<Timer> m_timers;
	Clock m_clock;

	int m_timerIdx = 0;


public:

	void load(const String& _path)
	{
		const Size SIZE(3, 2);
		TextReader reader(_path);

		String line;

		while (reader.readLine(line))
		{
			const auto datas = line.split(L':');

			if (datas.size() != 2)
			{
				Println(L"loadError -> sizeError:",line);
				continue;
			}

			const auto noData = ParseOpt<int>(datas[0]);

			if (!noData.has_value())
			{
				Println(L"loadError -> noDataError:", noData);
				continue;
			}

			const int no = noData.value() - 1;

			if (!InRange(no, 0, SIZE.x*SIZE.y - 1))
			{
				Println(L"loadError -> noError:", no);
				continue;
			}

			const Point pos = Point(320 * (no%SIZE.x), 270 * (no / SIZE.x));

			m_timers.push_back(Timer(pos, Size(320, 270), datas[1]));
		}
	}

	void init()override
	{
		load(L"test.data");

		/*
		m_timers.push_back(Timer(Point(0, 0), Size(320, 270), L"PC3"));
		m_timers.push_back(Timer(Point(320, 0), Size(320, 270), L"PC4"));
		m_timers.push_back(Timer(Point(0, 270), Size(320, 270), L"PC1"));
		m_timers.push_back(Timer(Point(320, 270), Size(320, 270), L"PC2"));
		m_timers.push_back(Timer(Point(640, 270), Size(320, 270), L"VR"));
		*/

		m_clock = Clock(Point(640, 0), Size(320, 270), L"ŽžŒv");

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
			m_timers[m_timerIdx].callStartBt();
		}

		else if (Input::KeyBackspace.clicked || Input::KeyShift.clicked)
		{
			m_timers[m_timerIdx].callResetBt();
		}


	}
	void draw()const override
	{
		for (const auto& t : m_timers)
		{
			t.draw();
		}

		m_clock.draw();

		if (!InRange(m_timerIdx, 0, 4))
		{
			return;
		}

		m_timers[m_timerIdx].getColider().drawFrame(3, 0, Palette::Yellow);
	}
};