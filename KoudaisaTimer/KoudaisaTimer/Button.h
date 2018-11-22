#pragma once
# include <Siv3D.hpp>

class Button
{
	Point m_pos;
	Size m_size;
	String m_name;

	bool m_isEnabled;

public:

	Button():m_isEnabled(true){ }
	Button(const Point& _pos,const Size& _size) :m_pos(_pos),m_size(_size), m_isEnabled(true) {}
	Button(const Rect& _rect,const String& _name) :m_pos(_rect.pos), m_size(_rect.size),m_name(_name) , m_isEnabled(true) {}

	void setName(const String& _name)
	{
		m_name = _name;
	}

	void setEnabled(bool _enabled)
	{
		m_isEnabled = _enabled;
	}

	Rect getColider()const
	{
		return Rect(m_pos, m_size);
	}

	bool mouseOver()const
	{
		return getColider().mouseOver && !getColider().leftClicked && m_isEnabled;
	}

	bool leftClicked()const
	{
		return getColider().leftClicked&& m_isEnabled;
	}

	bool isEnabled()const
	{
		return m_isEnabled;
	}


	void draw()const
	{
		getColider().draw();
		FontAsset(L"Button")(m_name).drawAt(getColider().center,Palette::Black);

		if (!m_isEnabled)
		{
			getColider().draw(Color(Palette::Black,200));
			return;
		}

		if (leftClicked())
		{
			drawPushed();
		}

		else if (mouseOver())
		{
			getColider().draw(Color(Palette::Gray, 100));
		}

	}

	void drawPushed()const
	{
		getColider().draw(Color(Palette::Gray, 230));
	}
};