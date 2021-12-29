#include "ContentLoadException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_MOVE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#endif

Elysium::Graphics::Content::ContentLoadException::ContentLoadException()
	: Elysium::Core::Exception(u8"SystemException")
{ }

Elysium::Graphics::Content::ContentLoadException::ContentLoadException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }

Elysium::Graphics::Content::ContentLoadException::ContentLoadException(Elysium::Core::Utf8String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Graphics::Content::ContentLoadException::~ContentLoadException()
{ }
