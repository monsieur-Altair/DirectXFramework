#include "TextClass.h"

TextClass::TextClass()
{
	g_pDWriteFactory = NULL;
	g_pTextFormat = NULL;
	fontName = L"MyMidPro";
	fontSize = 20;
}

TextClass::TextClass(TextClass&)
{
}

TextClass::~TextClass()
{

}

bool TextClass::Initialize()
{
	HRESULT result = S_OK;
	
	result = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(g_pDWriteFactory), reinterpret_cast<IUnknown**>(&g_pDWriteFactory));
	if (FAILED(result))
		return false;

	result = g_pDWriteFactory->CreateTextFormat(
		fontName,
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		fontSize,
		L"", //locale
		&g_pTextFormat
	);

	if (FAILED(result))
		return false;

	g_pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
	g_pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);

	return true;
}

IDWriteTextFormat* TextClass::GetTextFormat()
{
	return g_pTextFormat;
}

void TextClass::Shutdown()
{
	if (g_pDWriteFactory)
	{
		g_pDWriteFactory->Release();
		g_pDWriteFactory = NULL;
	}
	if (g_pTextFormat)
	{
		g_pTextFormat->Release();
		g_pTextFormat = NULL;
	}
	//if (fontName)
	//{
	//	delete[] fontName;
	//	fontName = NULL;
	//}
}
