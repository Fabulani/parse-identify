cmake_minimum_required(VERSION 3.30)
project(ParseIdentify VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# CPACK WIX properties
set(CPACK_WIX_VERSION 4)
set(CPACK_WIX_UPGRADE_GUID "1291d2e8-2ebc-4241-af29-077ff294c9bf")
set(CPACK_WIX_PRODUCT_ICON "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon.ico")
set(CPACK_WIX_PROGRAM_MENU_FOLDER "ParseIdentify")
set(CPACK_WIX_PROPERTY_ARPHELPLINK "https://github.com/Fabulani/brancco/issues")
set(CPACK_WIX_PROPERTY_ARPURLINFOABOUT "https://github.com/Fabulani/brancco/blob/main/README.md")
set(CPACK_WIX_PROPERTY_ARPURLUPDATEINFO "https://github.com/Fabulani/brancco/releases")

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_GENERATOR "WIX")
set(CPACK_SOURCE_GENERATOR "WIX")


include(CPack)

add_executable(ParseIdentify 
    main.cpp
    src/parser.cpp
    src/pprinter.cpp
)

install(TARGETS ParseIdentify DESTINATION bin)