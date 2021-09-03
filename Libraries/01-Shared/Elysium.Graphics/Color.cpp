#include "Color.hpp"

#ifndef ELYSIUM_CORE_INTEGER
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/Integer.hpp"
#endif

#ifndef ELYSIUM_CORE_OVERFLOWEXCEPTION
#include "../../../../Elysium-Core/Libraries/01-Shared/Elysium.Core/OverflowException.hpp"
#endif

#ifndef _TYPE_TRAITS_
#include <type_traits>
#endif

#ifndef _LIMITS_
#include <limits>
#endif

Elysium::Graphics::Color::Color(float Red, float Green, float Blue)noexcept
	: Elysium::Graphics::Color::Color(Red, Green, Blue, 1.0f)
{ }
Elysium::Graphics::Color::Color(float Red, float Green, float Blue, float Alpha)noexcept
	: Elysium::Graphics::Color::Color((Elysium::Core::uint8_t)(Red * 255.0f), (Elysium::Core::uint8_t)(Green * 255.0f), (Elysium::Core::uint8_t)(Blue * 255.0f), (Elysium::Core::uint8_t)(Alpha * 255.0f))
{ }
Elysium::Graphics::Color::Color(Elysium::Core::uint32_t Red, Elysium::Core::uint32_t Green, Elysium::Core::uint32_t Blue, Elysium::Core::uint32_t Alpha) noexcept
	: Elysium::Graphics::Color::Color((Elysium::Core::uint8_t)Red, (Elysium::Core::uint8_t)Green, (Elysium::Core::uint8_t)Blue, (Elysium::Core::uint8_t)Alpha)
{ }
Elysium::Graphics::Color::Color(Elysium::Core::uint8_t Red, Elysium::Core::uint8_t Green, Elysium::Core::uint8_t Blue, Elysium::Core::uint8_t Alpha) noexcept
	: _PackedValue(((Red | Green << 8) | Blue << 16) | Alpha << 24)
{ }
Elysium::Graphics::Color::Color(const Color & Source) noexcept
	: _PackedValue(Source._PackedValue)
{ }
Elysium::Graphics::Color::Color(Color&& Right) noexcept
{
	*this = std::move(Right);
}
Elysium::Graphics::Color::~Color() noexcept
{ }

Elysium::Graphics::Color& Elysium::Graphics::Color::operator=(const Color & Source) noexcept
{
	if (this != &Source)
	{
		_PackedValue = Source._PackedValue;
	}
	return *this;
}

Elysium::Graphics::Color& Elysium::Graphics::Color::operator=(Color&& Right) noexcept
{
	if (this != &Right)
	{
		_PackedValue = std::move(Right._PackedValue);

		Right._PackedValue = 0;
	}
	return *this;
}

const bool Elysium::Graphics::Color::operator==(const Color& Right) const
{
	return _PackedValue == Right._PackedValue;
}

const bool Elysium::Graphics::Color::operator!=(const Color& Right) const
{
	return _PackedValue != Right._PackedValue;
}

Elysium::Graphics::Color& Elysium::Graphics::Color::operator*=(const Color& Other)
{
	Elysium::Core::UInt32 LeftValue = _PackedValue;
	Elysium::Core::UInt32 RightValue = Other._PackedValue;

	_PackedValue = static_cast<Elysium::Core::uint32_t>(LeftValue * RightValue);

	return *this;
}

Elysium::Graphics::Color Elysium::Graphics::Color::operator*(const Color& Other)
{
	return this->operator*(Other);
}

const Elysium::Core::uint32_t& Elysium::Graphics::Color::GetPackedValue() const noexcept
{
	return _PackedValue;
}

const Elysium::Core::uint8_t Elysium::Graphics::Color::GetRed() const noexcept
{
	return ((Elysium::Core::uint8_t*)&_PackedValue)[0];
}

const Elysium::Core::uint8_t Elysium::Graphics::Color::GetGreen() const noexcept
{
	return ((Elysium::Core::uint8_t*)&_PackedValue)[1];
}

const Elysium::Core::uint8_t Elysium::Graphics::Color::GetBlue() const noexcept
{
	return ((Elysium::Core::uint8_t*)&_PackedValue)[2];
}

const Elysium::Core::uint8_t Elysium::Graphics::Color::GetAlpha() const noexcept
{
	return ((Elysium::Core::uint8_t*)&_PackedValue)[3];
}

const Elysium::Graphics::Color Elysium::Graphics::Color::AliceBlue = Color(240u, 248u, 255u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::AntiqueWhite = Color(250u, 235u, 215u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Aqua = Color(0u, 255u, 255u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Aquamarine = Color(127u, 255u, 212u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Azure = Color(240u, 255u, 255u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Beige = Color(2405, 2405, 220u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Bisque = Color(255u, 228u, 196u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Black = Color(0u, 0u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::BlanchedAlmond = Color(255u, 235u, 205u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Blue = Color(0u, 0u, 255u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::BlueViolet = Color(138u, 43u, 226u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Brown = Color(165u, 42u, 42u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::BurlyWood = Color(222u, 184u, 135u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::CadetBlue = Color(95u, 158u, 160u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Chartreuse = Color(127u, 255u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Chocolate = Color(210u, 105u, 30u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Coral = Color(255u, 127u, 80u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::CornflowerBlue = Color(100u, 149u, 237u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Cornsilk = Color(255u, 248u, 220u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Crimson = Color(220u, 20u, 60u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Cyan = Color(0u, 255u, 255u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkBlue = Color(0u, 0u, 139u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkCyan = Color(0u, 139u, 139u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkGoldenrod = Color(184u, 134u, 11u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkGray = Color(169u, 169u, 169u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkGreen = Color(0u, 100u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkKhaki = Color(189u, 183u, 107u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkMagenta = Color(139u, 0u, 139u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkOliveGreen = Color(85u, 107u, 47u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkOrange = Color(255u, 140u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkOrchid = Color(153u, 50u, 204u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkRed = Color(139u, 0u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkSalmon = Color(233u, 150u, 122u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkSeaGreen = Color(143u, 188u, 139u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkSlateBlue = Color(72u, 61u, 139u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkSlateGray = Color(47u, 79u, 79u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkTurquoise = Color(0u, 206u, 209u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DarkViolet = Color(148u, 0u, 211u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DeepPink = Color(255u, 20u, 147u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DeepSkyBlue = Color(0u, 191u, 255u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DimGray = Color(105u, 105u, 105u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::DodgerBlue = Color(30u, 144u, 255u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Firebrick = Color(178u, 34u, 34u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::FloralWhite = Color(255u, 250u, 240u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::ForestGreen = Color(34u, 139u, 34u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Fuchsia = Color(255u, 0u, 255u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Gainsboro = Color(220u, 220u, 220u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::GhostWhite = Color(248u, 248u, 255u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Gold = Color(218, 215u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Goldenrod = Color(218u, 165u, 32u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Gray = Color(128u, 128u, 128u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Green = Color(0u, 128u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::GreenYellow = Color(173u, 255u, 47u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Honeydew = Color(240u, 255u, 240u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::HotPink = Color(255u, 105u, 180u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::IndianRed = Color(205u, 92u, 92u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Indigo = Color(75u, 0u, 130u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Ivory = Color(255u, 255u, 240u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Khaki = Color(240u, 230u, 140u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Lavender = Color(230u, 230u, 250u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LavenderBlush = Color(255u, 240u, 245u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LawnGreen = Color(124u, 252u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LemonChiffon = Color(255u, 250u, 205u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightBlue = Color(173u, 216u, 230u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightCoral = Color(240u, 128u, 128u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightCyan = Color(224u, 255u, 255u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightGoldenrodYellow = Color(250u, 250u, 210u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightGray = Color(211u, 211u, 211u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightGreen = Color(144u, 238u, 144u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightPink = Color(255u, 182u, 193u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightSalmon = Color(255u, 160u, 122u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightSeaGreen = Color(32u, 178u, 170u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightSkyBlue = Color(135u, 206u, 250u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightSlateGray = Color(119u, 136u, 153u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightSteelBlue = Color(176u, 196u, 222u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LightYellow = Color(255u, 255u, 224u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Lime = Color(0u, 255u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::LimeGreen = Color(50u, 205u, 50u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Linen = Color(250u, 240u, 230u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Magenta = Color(255u, 0u, 255u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Maroon = Color(128u, 0u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::MediumAquamarine = Color(102u, 205u, 170u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::MediumBlue = Color(0u, 0u, 205u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::MediumOrchid = Color(186u, 85u, 211u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::MediumPurple = Color(147u, 112u, 219u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::MediumSeaGreen = Color(60u, 179u, 113u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::MediumSlateBlue = Color(123u, 104u, 238u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::MediumSpringGreen = Color(0u, 250u, 154u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::MediumTurquoise = Color(72u, 209u, 204u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::MediumVioletRed = Color(199u, 21u, 133u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::MidnightBlue = Color(25u, 25u, 112u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::MintCream = Color(245u, 255u, 250u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::MistyRose = Color(255u, 228u, 225u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Moccasin = Color(255u, 228u, 181u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::NavajoWhite = Color(255u, 222u, 173u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Navy = Color(0u, 0u, 128u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::OldLace = Color(253u, 245u, 230u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Olive = Color(128u, 128u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::OliveDrab = Color(107u, 142u, 35u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Orange = Color(255u, 165u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::OrangeRed = Color(255u, 69u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Orchid = Color(218u, 112u, 214u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::PaleGoldenrod = Color(238u, 232u, 170u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::PaleGreen = Color(152u, 251u, 152u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::PaleTurquoise = Color(175u, 238u, 238u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::PaleVioletRed = Color(219u, 112u, 147u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::PapayaWhip = Color(255u, 239u, 213u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::PeachPuff = Color(255u, 218u, 185u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Peru = Color(205u, 133u, 63u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Pink = Color(255u, 192u, 203u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Plum = Color(221u, 160u, 221u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::PowderBlue = Color(176u, 224u, 230u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Purple = Color(128u, 0u, 128u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Red = Color(255u, 0u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::RosyBrown = Color(188u, 143u, 143u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::RoyalBlue = Color(65u, 105u, 225u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::SaddleBrown = Color(139u, 69u, 19u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Salmon = Color(250u, 128u, 114u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::SandyBrown = Color(244u, 164u, 96u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::SeaGreen = Color(46u, 139u, 87u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::SeaShell = Color(255u, 245u, 238u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Sienna = Color(160u, 82u, 45u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Silver = Color(192u, 192u, 192u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::SkyBlue = Color(135u, 206u, 235u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::SlateBlue = Color(106u, 90u, 205u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::SlateGray = Color(112u, 128u, 144u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Snow = Color(255u, 250u, 250u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::SpringGreen = Color(0u, 255u, 127u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::SteelBlue = Color(70u, 130u, 180u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Tan = Color(210u, 180u, 140u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Teal = Color(0u, 128u, 128u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Thistle = Color(216u, 191u, 216u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Tomato = Color(255u, 99u, 71u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Transparent = Color(0u, 0u, 0u, 0u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Turquoise = Color(64u, 224u, 208u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Violet = Color(238u, 130u, 238u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Wheat = Color(245u, 222u, 179u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::White = Color(255u, 255u, 255u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::WhiteSmoke = Color(245u, 245u, 245u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::Yellow = Color(255u, 255u, 0u, 255u);
const Elysium::Graphics::Color Elysium::Graphics::Color::YellowGreen = Color(154u, 205u, 50u, 255u);
