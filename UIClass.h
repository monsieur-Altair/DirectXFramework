#pragma once

#include "TextClass.h"
#include "Constants.h"
#include <d2d1.h>
#pragma comment(lib, "d2d1.lib")


class UIClass
{
private:
	ID2D1Factory* g_pD2DFactory;
	ID2D1RenderTarget* g_pRenderTarget;
	ID2D1SolidColorBrush* g_pWhiteBrush;
	ID2D1SolidColorBrush* g_pRedBrush;
	TextClass* g_pText;
public:
	UIClass();
	UIClass(const UIClass&);
	~UIClass();

	bool Intialize(IDXGISwapChain*);
	void Draw();
	void Shutdown();
};

