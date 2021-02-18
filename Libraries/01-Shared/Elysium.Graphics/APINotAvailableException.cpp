#include "APINotAvailableException.hpp"

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

Elysium::Graphics::APINotAvailableException::APINotAvailableException()
	: Elysium::Core::Exception(u8"APINotAvailableException")
{ }
Elysium::Graphics::APINotAvailableException::APINotAvailableException(const char8_t* Message)
	: Elysium::Core::Exception(Message)
{ }
Elysium::Graphics::APINotAvailableException::APINotAvailableException(Elysium::Core::String&& Message)
	: Elysium::Core::Exception(std::move(Message))
{ }
Elysium::Graphics::APINotAvailableException::~APINotAvailableException()
{ }
