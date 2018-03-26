#include <cstdint>

static constexpr std::uint32_t MAGAZINE_WIDTH = 512;
static constexpr std::uint32_t MAGAZINE_HEIGHT = 512;

// Some of these values trigger unused debug dialogues etc..
struct MagazineHeader
{
	std::uint8_t magic[6];
	std::uint32_t v1;
	std::uint32_t padding;
	std::uint16_t v2;
	std::uint32_t unknown;
	std::uint32_t unknown_2; // timestamps? checksum?
	std::uint32_t unknown_3;
	std::uint32_t versioning_1;
	std::uint32_t versioning_2;

	MagazineHeader()
	{
		magic[0] = 0x32; magic[1] = 0x30;
		magic[2] = 0x43; magic[3] = 0x4D;
		magic[4] = 0x24; magic[5] = 0x00;

		v1 = 0x10000800;
		v2 = 16;
		unknown = 1615974587;
		unknown_2 = 4109395719;
		unknown_3 = 4109395719;
		versioning_1 = 269;
		versioning_2 = 1048576;
	}
};