#pragma once

#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")


class TextClass
{
private:
	IDWriteFactory*		g_pDWriteFactory;
	IDWriteTextFormat*	g_pTextFormat;
	WCHAR*				fontName;
	FLOAT				fontSize;
public:
	TextClass();
	TextClass(TextClass&);
	~TextClass();

	bool Initialize();
	IDWriteTextFormat* GetTextFormat();
	void Shutdown();
};

