#include <vector>
#include <string>
#include <iostream>

#include "operations.h"

// The magazine original image size is 512w512h

int main( int argc, char *argv[] )
{
	std::cout << "NFSU2 Magazine Worker (itsMaru)" << std::endl;

	bool preserveAlpha = false;
	OperationType opType = OperationType::None;

	std::vector< std::string > pathList;

	for( auto i = 1; i < argc; i++ )
	{
		std::string arg = argv[i];

		if( arg == "-preserveAlpha" )
		{
			preserveAlpha = true;
		}
		else if( arg == "-i" )
		{
			opType = OperationType::Import;
		}
		else
		{
			if( opType == OperationType::None )
				opType = OperationType::Export;

			pathList.push_back( arg );
		}
	}

	int status = 0;

	switch( opType )
	{
		case OperationType::Export:
		{
			status = Operations::exportMagazineToPNG( pathList, preserveAlpha );
			break;
		}
		case OperationType::Import:
		{
			if( pathList.size() != 2 )
			{
				status = 1;
				std::cout << "Only 2 path arguments are supported for importing (-i example.png \"Test Magazine 1\")" << std::endl;
				break;
			}
			
			status = Operations::importPNGIntoMagazine( pathList );
			break;
		}
		default:
		{
			std::cout << "Pass path as argument to export magazine to PNG (can be multiple magazines)" << std::endl;
			std::cout << "-i to import a PNG to a magazine" << std::endl;
			std::cout << "-preserveAlpha (only available for export) preserves the magazine's alpha channel." << std::endl;
			break;
		}
	}

	return status;

}
