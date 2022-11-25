# Sets the following variables:
#
#  SDL2_FOUND
#  SDL2_INCLUDE_DIR
#  SDL2_LIBRARY

SET(SDL2_SEARCH_PATHS
    ~/Library/Frameworks
    /Library/Frameworks
    /usr/local
    /usr
    /sw # fink
    /opt/local # darwinports
    /opt/csw # blastwave
    /opt)

find_path(SDL2_INCLUDE_DIR
    NAMES SDL.h
    PATH_SUFFIXES include include/SDL2
    PATHS ${SDL2_SEARCH_PATHS})

find_library(SDL2_LIBRARY
    NAMES SDL2
    PATH_SUFFIXES lib
    PATHS ${SDL2_SEARCH_PATHS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(SDL2 DEFAULT_MSG SDL2_LIBRARY SDL2_INCLUDE_DIR)

mark_as_advanced(SDL2_INCLUDE_DIR SDL2_LIBRARY)