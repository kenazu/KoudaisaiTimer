#pragma once
#include<Siv3d.hpp>

class DrawArea
{
protected:
	Point m_pos;
	Size m_size;
	String m_name;

public:

	DrawArea() {}

	DrawArea(const Point& _pos, const Size& _size):m_pos(_pos),m_size(_size)
	{

	}

	DrawArea(const Point& _pos, const Size& _size,const String& _name) :m_pos(_pos), m_size(_size),m_name(_name)
	{

	}

	Rect getColider()const
	{
		return Rect(m_pos, m_size);
	}

	Point getCenter()const
	{
		return m_pos.movedBy(m_size / 2);
	}

	virtual void update() = 0;
	virtual void draw()const = 0;


};