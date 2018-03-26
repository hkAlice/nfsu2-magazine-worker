#include <vector>
#include <algorithm>
#include <cstdint>

#include <iostream>

enum class OperationType
{
	Import,
	Export,
	None
};

class Operations
{
	public:
		static std::uint32_t importPNGIntoMagazine( const std::vector< std::string >& pathList );
		static std::uint32_t exportMagazineToPNG( const std::vector< std::string >& pathList, bool alphaFF );
	private:
		Operations() {};

		// Just swap B and R (BGRA <-> RGBA)
		// Our transformed vector is a copy of the original magazine image,
		// meaning no operation is needed on green or alpha channels
		// Can use it both ways for export <-> import for magazine

		// Shift Left Padding: Circular shift the first 9 pixels, otherwise it'll not align properly
		// It seems that the game renderer itself has no issue with them otherwise, so only used for exporting to PNGs
		static void transformRawImage( std::vector< std::uint8_t >& img, bool shiftLeftPadding = false, bool preserveAlpha = false )
		{
			std::uint32_t index = 0;

			while( index + 4 < img.size() )
			{
				std::swap( img[index], img[index + 2] );
				if( !preserveAlpha ) img[index + 3] = 0xFF;

				index += 4;
			}

			if( shiftLeftPadding )
			{
				std::rotate( img.begin(), img.begin() + 36, img.end() );
			}

			return;
		}
};