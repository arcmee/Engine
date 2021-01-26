#pragma once

namespace Utility
{
	class noncopyable
	{
	public:
		noncopyable() {};
	private:
		noncopyable(const noncopyable&);
		noncopyable& operator=(noncopyable&);
	};
}

using namespace Utility;