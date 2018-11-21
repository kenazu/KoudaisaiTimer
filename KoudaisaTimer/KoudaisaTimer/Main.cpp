
# include <Siv3D.hpp>
# include "TimerScene.h"

void Main()
{
	Window::SetTitle(L"NITMic工大祭タイマー");

	Window::Resize(960,540);

	FontAsset::Register(L"Button",10);
	FontAsset::Register(L"Timer", 20);		
	FontAsset::Register(L"TimerName", 20);
	FontAsset::Register(L"Clock", 20);
	FontAsset::Register(L"ClockName", 20);


	MyApp manager;
	manager.add<Empty>(L"Empty");
	manager.add<TimerScene>(L"TimerScene");

	while (System::Update())
	{
		manager.updateAndDraw();
	}
}
