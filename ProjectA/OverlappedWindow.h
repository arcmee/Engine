#pragma once
#include"noncopyable.h"
#include <memory>

namespace PlatformRig
{
	class InputTranslator;

	class IWindowHandler
	{
	public:
		virtual void OnResize(unsigned newWidth, unsigned newHeight) = 0;
		virtual ~IWindowHandler();
	};



	class OverlappedWindow : noncopyable
	{
	public:
		const void* GetUnderlyingHandle() const;
		
		OverlappedWindow();
		~OverlappedWindow();

		class Pimpl;
	protected:
		std::unique_ptr<Pimpl> _pimpl;

	};
}

