#include "ContentLoadException.hpp"

#ifndef ELYSIUM_CORE_OBJECT
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Object.hpp"
#endif

Elysium::Graphics::Content::ContentLoadException::ContentLoadException()
	: Elysium::Core::Exception(u8"SystemException")
{ }
Elysium::Graphics::Content::ContentLoadException::ContentLoadException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Graphics::Content::ContentLoadException::ContentLoadException(Elysium::Core::String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Object::Move(Message))
{ }
Elysium::Graphics::Content::ContentLoadException::~ContentLoadException()
{ }
