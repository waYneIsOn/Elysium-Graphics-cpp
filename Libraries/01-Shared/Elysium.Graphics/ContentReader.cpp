#include "ContentReader.hpp"

#ifndef ELYSIUM_GRAPHICS_CONTENT_CONTENTLOADEXCEPTION
#include "ContentLoadException.hpp"
#endif

#ifndef ELYSIUM_GRAPHICS_CONTENT_CONTENTMANAGER
#include "ContentManager.hpp"
#endif

Elysium::Graphics::Content::ContentReader::~ContentReader() noexcept
{ }

Elysium::Graphics::Content::ContentReader Elysium::Graphics::Content::ContentReader::Create(const ContentManager& Manager, Elysium::Core::IO::Stream& Input, const Elysium::Core::String& AssetName)
{
    // file header
    // +--------+----------------------+--------------------------------
    // | Type   |   Description        | Example/Value
    // +--------+----------------------+--------------------------------
    // | Byte   | Format identifier    | E (69)
    // +--------+----------------------+--------------------------------
    // | Byte   | Format identifier    | G (71)
    // +--------+----------------------+--------------------------------
    // | Byte   | Format identifier    | E (69)
    // +--------+----------------------+--------------------------------
    // | UInt16 | Format version       | ...
    // +--------+----------------------+--------------------------------
    // | UInt32 | Content length       | ...
    // +--------+----------------------+--------------------------------
    // | ...    | ...                  | ...
    // +--------+----------------------+--------------------------------
	Elysium::Core::IO::BinaryReader Reader = Elysium::Core::IO::BinaryReader(Input, Elysium::Core::Text::Encoding::UTF8(), false);

	const Elysium::Core::byte Magic1 = Reader.ReadByte();
	const Elysium::Core::byte Magic2 = Reader.ReadByte();
	const Elysium::Core::byte Magic3 = Reader.ReadByte();
	if (Magic1 != u8'E' || Magic2 != u8'G' || Magic3 != u8'E')
	{
		throw ContentLoadException(u8"Unknown file format.");
	}

    const Elysium::Core::uint16_t FormatVersion = Reader.ReadUInt16();
    switch (FormatVersion)
    {
    case 1:
        break;
    default:
        throw ContentLoadException(u8"Unknown file version.");
    }

    const Elysium::Core::uint32_t ContentLength = Reader.ReadUInt32();

    return ContentReader(Manager, Reader, AssetName);
}

Elysium::Graphics::Content::ContentReader::ContentReader(const ContentManager& Manager, Elysium::Core::IO::BinaryReader& InputReader, const Elysium::Core::String& AssetName) noexcept
    : _GraphicsDevice(Manager.GetGraphicsDevice()), _AssetName(AssetName), _InputReader(InputReader)
{ }
