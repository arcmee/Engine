#pragma once
#include <memory>


class InputTranslator
{
public:
	InputTranslator();
	~InputTranslator();

private:
	class Pimpl;
	//std::unique_ptr<Pimpl> _pimpl;

	//unsigned		GetMouseButtonState() const;

	//void			Publish(const RenderOverlays::DebuggingDisplay::InputSnapshot& snapShot);

};

