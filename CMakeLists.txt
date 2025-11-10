cmake_minimum_required(VERSION 3.16)

project(7z2sfx LANGUAGES C)

add_executable(7z2sfx main.c)

include(GNUInstallDirs)
install(TARGETS 7z2sfx
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
