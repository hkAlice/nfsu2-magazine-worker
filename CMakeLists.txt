cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0015 NEW)
project(nfsu2_magazine_worker)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin/")


file(GLOB INCLUDE_FILES 
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*"
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)
file(GLOB SOURCE_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c*"
  "${CMAKE_CURRENT_SOURCE_DIR}/libs/lodepng/lodepng.cpp"
)

FILE(WRITE "${CMAKE_CURRENT_BINARY_DIR}/abc.vcxproj.user"
    "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n"
    "<Project ToolsVersion=\"15.0\">\n"
    "  <PropertyGroup>\n"
    "    <LocalDebuggerCommandArguments>-e</LocalDebuggerCommandArguments>\n"
    "    <DebuggerFlavor>WindowsLocalDebugger</DebuggerFlavor>\n"
    "  </PropertyGroup>\n"
    "</Project>")

add_executable(nfsu2_mw ${INCLUDE_FILES} ${SOURCE_FILES})

set_target_properties(nfsu2_mw PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS ON
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin/"
)

include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/libs/lodepng" )

#target_link_libraries(nfsu2_mw ${Boost_LIBRARIES} ${Boost_LIBRARIES})

