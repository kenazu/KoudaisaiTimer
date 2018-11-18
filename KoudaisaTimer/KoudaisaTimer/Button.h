#pragma once
# include <Siv3D.hpp>

class Button
{
	Point m_pos;
	Size m_size;
	String m_name;

public:

	Button(){ }
	Button(const Point& _pos,const Size& _size) :m_pos(_pos),m_size(_size){}
	Button(const Rect& _rect,const String& _name) :m_pos(_rect.pos), m_size(_rect.size),m_name(_name) {}

	void setName(const String& _name)
	{
		m_name = _name;
	}

	Rect getColider()const
	{
		return Rect(m_pos, m_size);
	}

	bool mouseOver()const
	{
		return getColider().mouseOver && !getColider().leftClicked;
	}

	bool leftClicked()const
	{
		return getColider().leftClicked;
	}


	void draw()const
	{
		getColider().draw();
		FontAsset(L"Button")(m_name).drawAt(getColider().center,Palette::Black);

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