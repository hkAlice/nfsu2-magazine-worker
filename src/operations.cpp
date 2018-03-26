#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm>

#include "../libs/lodepng/lodepng.h"

#include "operations.h"
#include "magazine.h"

static constexpr auto MAGAZINE_EXPORT_NAME = "magazine";

std::uint32_t Operations::exportMagazineToPNG( const std::vector< std::string >& pathList, bool preserveAlpha )
{
	static const size_t magazineCount = pathList.size();

	std::vector< std::uint8_t > magazine;
	std::vector< std::uint8_t > pngOutput;

	for( std::uint32_t i = 0; i < magazineCount; i++ )
	{
		std::cout << "Exporting " + std::string( pathList[i] ) << std::endl;

		auto error = lodepng::load_file( magazine, pathList[i] );

		if( error != 0 )
		{
			std::cout << "Failed to load file. (" + std::to_string( error ) + ")" << std::endl;
			return error;
		}

		transformRawImage( magazine, true, preserveAlpha );

		error = lodepng::encode( pngOutput, magazine, MAGAZINE_WIDTH, MAGAZINE_HEIGHT );

		if( error != 0 )
		{
			std::cout << "Failed to encode image. (" + std::to_string( error ) + ")" << std::endl;
			return error;
		}

		error = lodepng::save_file( pngOutput, std::string( MAGAZINE_EXPORT_NAME + std::to_string( i ) ) + ".png" );

		if( error != 0 )
		{
			std::cout << "Failed to save image. (" + std::to_string( error ) + ")" << std::endl;
			return error;
		}
	}

	return 0;
}

std::uint32_t Operations::importPNGIntoMagazine( const std::vector< std::string >& pathList )
{
	std::vector< std::uint8_t > png;
	std::vector< std::uint8_t > image;
	std::vector< std::uint8_t > magazine;
	std::uint32_t width, height;

	std::cout << "Importing PNG " + std::string( pathList[0] ) + " into magazine " + std::string( pathList[1] ) << std::endl;

	auto error = lodepng::load_file( png, pathList[0] );

	if( error != 0 )
	{
		std::cout << "Failed to load file. (" + std::to_string( error ) + ")" << std::endl;
		return 0;
	}

	error = lodepng::decode( image, width, height, png );

	if( error ) std::cout << "decoder error " << error << ": " << lodepng_error_text( error ) << std::endl;

	if( width != 512 || height != 512 )
		std::cout << "Warning - PNG image does not match magazine size (512x512)" << std::endl;

	transformRawImage( image, false, false );

	error = lodepng::load_file( magazine, pathList[1] );

	if( error != 0 )
	{
		std::cout << "Failed to load file. (" + std::to_string( error ) + ")" << std::endl;
		return 0;
	}

	std::fill( magazine.begin() + 0x24, magazine.end(), 0 );
	std::copy( image.begin(), image.end(), magazine.begin() + 0x24 );

	error = lodepng::save_file( magazine, pathList[1] );

	if( error != 0 )
	{
		std::cout << "Failed to save image. (" + std::to_string( error ) + ")" << std::endl;
		return 0;
	}

	return 0;
}