#include "UIClass.h"

UIClass::UIClass()
{
	g_pD2DFactory = NULL;
	g_pRenderTarget = NULL;
	g_pWhiteBrush = NULL;
	g_pRedBrush = NULL;
    g_pText = NULL;
}

UIClass::UIClass(const UIClass&)
{
}

UIClass::~UIClass()
{
}

bool UIClass::Intialize(IDXGISwapChain* g_pSwapChain)
{
	HRESULT result = S_OK;
	result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_pD2DFactory);
	if (FAILED(result))
		return false;
    IDXGISurface* pBackBuffer2 = NULL;

    result = g_pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer2));
    if (FAILED(result))
        return false;

    FLOAT dpiX, dpiY;
    g_pD2DFactory->GetDesktopDpi(&dpiX, &dpiY);
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
        dpiX,
        dpiY);

    result = g_pD2DFactory->CreateDxgiSurfaceRenderTarget(pBackBuffer2, &props, &g_pRenderTarget);
    if (FAILED(result))
        return false;

    g_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::White), &g_pWhiteBrush);
    g_pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red), &g_pRedBrush);
    


    g_pText = new TextClass;
    bool res = g_pText->Initialize();
    if (!res)
        return false;

	return true;
}

void UIClass::Draw()
{
    UINT size = NULL;
    const D2D1_POINT_2F p = { (LENGTH_WINDOW - 300) / 2 , (WIDTH_WINDOW - 160) / 2 - 20 };
    

    g_pRenderTarget->BeginDraw();
    for (int i = 1; i < 7; i++) 
    {
        g_pRenderTarget->DrawRectangle( D2D1::RectF(10*i, 10*i, LENGTH_WINDOW - 300 - 10*i, WIDTH_WINDOW - 160 - 10*i),g_pWhiteBrush);//160 bot, 300 length
        g_pRenderTarget->DrawLine(      D2D1::Point2F(60+10*i, 60+10*i),                   D2D1::Point2F(60+10*i, WIDTH_WINDOW-160-60-10 * i),      g_pRedBrush);
        g_pRenderTarget->DrawLine(      D2D1::Point2F(LENGTH_WINDOW-300-60-10*i, 60+10*i), D2D1::Point2F(LENGTH_WINDOW-300-60-10*i, WIDTH_WINDOW - 160 - 60 - 10 * i),g_pRedBrush);
    }

    g_pRenderTarget->DrawEllipse(D2D1::Ellipse(p, 50.0f, 50.0f),g_pRedBrush);

    int i = 80, j=150;
    static const WCHAR sc_Text[] = L"Melnikov Maksim";
    size = ARRAYSIZE(sc_Text) - 1;
    g_pRenderTarget->DrawText(
        sc_Text, size, 
        g_pText->GetTextFormat(), 
        D2D1::RectF((LENGTH_WINDOW-300)/2 - i, 70, (LENGTH_WINDOW - 300) / 2 + i, 250),
        g_pRedBrush, 
        D2D1_DRAW_TEXT_OPTIONS_NONE, 
        DWRITE_MEASURING_MODE_NATURAL);


    static const WCHAR sc_Text1[] = L"924401 DirectX framework 2021";
    size = ARRAYSIZE(sc_Text1) - 1;
    g_pRenderTarget->DrawText(
        sc_Text1, 
        size, 
        g_pText->GetTextFormat(), 
        D2D1::RectF((LENGTH_WINDOW - 300) / 2 - j, WIDTH_WINDOW - 160 - 90, (LENGTH_WINDOW - 300) / 2 + j, WIDTH_WINDOW),
        g_pWhiteBrush, 
        D2D1_DRAW_TEXT_OPTIONS_NONE, 
        DWRITE_MEASURING_MODE_NATURAL);


    g_pRenderTarget->EndDraw();
}

void UIClass::Shutdown()
{
    if(g_pD2DFactory)
    {
        g_pD2DFactory->Release();
        g_pD2DFactory = NULL;
    }

    if (g_pRenderTarget)
    {
        g_pRenderTarget->Release();
        g_pRenderTarget = NULL;
    }
    if (g_pRedBrush)
    {
        g_pRedBrush->Release();
        g_pRedBrush = NULL;
    }    
    if (g_pWhiteBrush)
    {
        g_pWhiteBrush->Release();
        g_pWhiteBrush = NULL;
    }
    if (g_pText)
    {
        delete g_pText;
        g_pText = NULL;
    }
}
