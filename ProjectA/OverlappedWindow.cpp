#include "OverlappedWindow.h"
#include "Defines.h"

#include <windows.h>
#include <vector>


namespace PlatformRig
{

	class CurrentModule
	{
	public:
		CurrentModule();
		~CurrentModule();

		unsigned __int64		HashId();
		::HINSTANCE				Handle();
		::HINSTANCE				HInstance();

		static CurrentModule&	GetInstance();

	protected:
		unsigned __int64		_moduleHash;
	};

	inline unsigned __int64 CurrentModule::HashId() 	{ return _moduleHash; }
	inline ::HMODULE		CurrentModule::Handle()		{ return ::GetModuleHandle(0); }
	inline ::HINSTANCE		CurrentModule::HInstance()	{ return (::HINSTANCE)(::GetModuleHandle(0)); }

	CurrentModule::CurrentModule()
	{
		unsigned short buffer[MaxPath];
		auto filenameLength = ::GetModuleFileNameW(Handle(), (LPWSTR)buffer, dimof(buffer));
		//_moduleHash = Utility::Hash64(buffer, &buffer[filenameLength]);
	}

	CurrentModule::~CurrentModule() {}

	CurrentModule& CurrentModule::GetInstance()
	{
		static CurrentModule result;
		return result;
	}

	class OverlappedWindow::Pimpl 
	{
	public:
		HWND		_hwnd;
		bool		_activated;
		std::shared_ptr<InputTranslator> _inputTranslator;
		std::vector<std::shared_ptr<IWindowHandler>> _windowHandlers;

		Pimpl() : _hwnd(HWND(INVALID_HANDLE_VALUE)), _activated(false) {}

	};

	LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		switch (msg) {
		case WM_CLOSE:
			PostQuitMessage(0);
			break;

		case WM_ERASEBKGND:
			return 0;       // (suppress these)

		case WM_ACTIVATE:
		case WM_MOUSEMOVE:
		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_LBUTTONDBLCLK:
		case WM_RBUTTONDBLCLK:
		case WM_MBUTTONDBLCLK:
		case WM_MOUSEWHEEL:
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:
		case WM_SIZE:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		{
			auto pimpl = (OverlappedWindow::Pimpl*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
			if (!pimpl || pimpl->_hwnd != hwnd) break;

			//auto* inputTrans = pimpl->_inputTranslator.get();
			//if (!pimpl->_activated) { inputTrans = nullptr; }

			switch (msg) {
			case WM_ACTIVATE:
				pimpl->_activated = wparam != WA_INACTIVE;
				break;

			case WM_MOUSEMOVE:
			{
				//if (pimpl->_activated) {
				//	signed x = ((int)(short)LOWORD(lparam)), y = ((int)(short)HIWORD(lparam));
				//	if (inputTrans) inputTrans->OnMouseMove(x, y);
				//}
			}
			break;

			//case WM_LBUTTONDOWN:    if (inputTrans) { inputTrans->OnMouseButtonChange(0, true); }    break;
			//case WM_RBUTTONDOWN:    if (inputTrans) { inputTrans->OnMouseButtonChange(1, true); }    break;
			//case WM_MBUTTONDOWN:    if (inputTrans) { inputTrans->OnMouseButtonChange(2, true); }    break;

			//case WM_LBUTTONUP:      if (inputTrans) { inputTrans->OnMouseButtonChange(0, false); }   break;
			//case WM_RBUTTONUP:      if (inputTrans) { inputTrans->OnMouseButtonChange(1, false); }   break;
			//case WM_MBUTTONUP:      if (inputTrans) { inputTrans->OnMouseButtonChange(2, false); }   break;

			//case WM_LBUTTONDBLCLK:  if (inputTrans) { inputTrans->OnMouseButtonDblClk(0); }   break;
			//case WM_RBUTTONDBLCLK:  if (inputTrans) { inputTrans->OnMouseButtonDblClk(1); }   break;
			//case WM_MBUTTONDBLCLK:  if (inputTrans) { inputTrans->OnMouseButtonDblClk(2); }   break;

			//case WM_MOUSEWHEEL:     if (inputTrans) { inputTrans->OnMouseWheel(GET_WHEEL_DELTA_WPARAM(wparam)); }    break;

			//case WM_SYSKEYDOWN:
			//case WM_SYSKEYUP:
			//case WM_KEYDOWN:
			//case WM_KEYUP:
			//	if (inputTrans) { inputTrans->OnKeyChange((unsigned)wparam, (msg == WM_KEYDOWN) || (msg == WM_SYSKEYDOWN)); }
			//	if (msg == WM_SYSKEYUP || msg == WM_SYSKEYDOWN) return true;        // (suppress default windows behaviour for these system keys)
			//	break;

			//case WM_CHAR:
			//	if (inputTrans) { inputTrans->OnChar((ucs2)wparam); }
			//	break;

			case WM_SIZE:
				for (auto i = pimpl->_windowHandlers.begin(); i != pimpl->_windowHandlers.end(); ++i) {
					signed x = ((int)(short)LOWORD(lparam)), y = ((int)(short)HIWORD(lparam));
					(*i)->OnResize(x, y);
				}
				return msg == WM_SIZING;
			}
		}
		break;
		}

		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	OverlappedWindow::OverlappedWindow()
	{

	}


	OverlappedWindow::~OverlappedWindow()
	{
	}

}
 