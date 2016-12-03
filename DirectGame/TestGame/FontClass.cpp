#include "stdafx.h"
#include "FontClass.h"


FontClass::FontClass()
{

}

FontClass::~FontClass()
{

}

void FontClass::Initialize(ID3D11Device *device, IDXGISwapChain *swapChain)
{
	//HWND hwnd = DXUTGetHWND();


	HRESULT hr = S_OK;

	// Create a Direct2D factory.
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_d2dFactory);

	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(m_dWriteFactory),
		reinterpret_cast<IUnknown **>(&m_dWriteFactory)
	);

	IDXGIDevice * pDXGIDevice;
	hr = device->QueryInterface(__uuidof(IDXGIDevice), (void **)&pDXGIDevice);

	/*
	// Create a Direct2D render target.
	hr = m_d2dFactory->CreateHwndRenderTarget(
	D2D1::RenderTargetProperties(),
	D2D1::HwndRenderTargetProperties(hwnd, size),
	&m_pRenderTarget
	);
	*/

	// Obtain the Direct2D device for 2-D rendering.
	hr = m_d2dFactory->CreateDevice(pDXGIDevice, &m_d2dDevice);

	// Get Direct2D device's corresponding device context object.
	hr = m_d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &m_d2dDeviceContext);



	// Now we set up the Direct2D render target bitmap linked to the swapchain. 
	// Whenever we render to this bitmap, it is directly rendered to the 
	// swap chain associated with the window.
	float dpiX;
	float dpiY;
	m_d2dFactory->GetDesktopDpi(&dpiX, &dpiY);
	D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
		D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
		dpiX,
		dpiY
	);

	// Direct2D needs the dxgi version of the backbuffer surface pointer.
	IDXGISurface* dxgiBackBuffer;


	swapChain->GetBuffer(0, __uuidof(IDXGISurface), (LPVOID*)&dxgiBackBuffer);
	// Get a D2D surface from the DXGI back buffer to use as the D2D render target.

	m_d2dDeviceContext->CreateBitmapFromDxgiSurface(
		dxgiBackBuffer,
		&bitmapProperties,
		&m_d2dTargetBitmap
	);

	// Now we can set the Direct2D render target.
	m_d2dDeviceContext->SetTarget(m_d2dTargetBitmap);


	// Create D2D/DWrite objects for rendering text.
	{

		m_dWriteFactory->CreateTextFormat(
			L"Verdana",
			NULL,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			20,
			L"en-us",
			&m_textFormat
		);
		(m_textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING));
		(m_textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR));
	}


}

void FontClass::Draw(std::vector<std::shared_ptr<FontNode> > & node)
{
	ID2D1SolidColorBrush* pBlackBrush;
	(
		m_d2dDeviceContext->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White),
			&pBlackBrush
		)
		);
	m_d2dDeviceContext->SetTarget(m_d2dTargetBitmap);
	m_d2dDeviceContext->BeginDraw();
	m_d2dDeviceContext->SetTransform(D2D1::Matrix3x2F::Identity());

	for each (auto var in node)
	{
		const WCHAR* infoW = var->GetText();
		D2D1_RECT_F textRect = D2D1::RectF(var->GetPosX()*ScreenWith, var->GetPosY()*ScreenHeight, var->GetSizeX()*ScreenWith, var->GetSizeY()*ScreenHeight);
		m_d2dDeviceContext->DrawText(
			infoW,
			sizeof(infoW),
			m_textFormat,
			&textRect,
			pBlackBrush
		);
		delete infoW;
	}


	m_d2dDeviceContext->EndDraw();

}
