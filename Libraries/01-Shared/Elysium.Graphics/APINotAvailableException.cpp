#include "APINotAvailableException.hpp"

#ifndef ELYSIUM_CORE_TEMPLATE_FUNCTIONAL_MOVE
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core.Template/Move.hpp"
#endif

Elysium::Graphics::APINotAvailableException::APINotAvailableException()
	: Elysium::Core::Exception(u8"APINotAvailableException")
{ }

Elysium::Graphics::APINotAvailableException::APINotAvailableException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }

Elysium::Graphics::APINotAvailableException::APINotAvailableException(Elysium::Core::Utf8String&& Message)
	: Elysium::Core::Exception(Elysium::Core::Template::Functional::Move(Message))
{ }

Elysium::Graphics::APINotAvailableException::~APINotAvailableException()
{ }
