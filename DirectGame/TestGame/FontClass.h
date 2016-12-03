#pragma once

#include <d3d11.h>
#include <d2d1_2.h>
#include <dwrite.h>

#include "SpriteNode.h"
#include <vector>


class FontClass
{
public:
	FontClass();
	~FontClass();
	void Initialize(ID3D11Device *device, IDXGISwapChain *swapChain);
	void Draw(std::vector<std::shared_ptr<FontNode> > & node);
private:
	ID2D1Factory2* m_d2dFactory;
	//ID2D1HwndRenderTarget* m_pRenderTarget;
	ID2D1Device1* m_d2dDevice;
	ID2D1DeviceContext* m_d2dDeviceContext;
	ID2D1Bitmap1* m_d2dTargetBitmap;
	//ID2D1Factory1* m_d2dFactory;
	IDWriteFactory* m_dWriteFactory;
	IDWriteTextFormat* m_textFormat;
};
