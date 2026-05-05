cmake_minimum_required(VERSION 3.31)

option(MDR_DISABLE_BLE "Disable Windows BLE backend (avoids C++/WinRT dependency, e.g. for MinGW builds)" OFF)

if (MDR_DISABLE_BLE)
    set(SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/PlatformWindows.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/PlatformWindowsBLE_stub.cpp"
    )
    set(EXTRA_LIBS "")
else()
    set(SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/PlatformWindows.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/PlatformWindowsBLE.cpp"
    )
    set(EXTRA_LIBS windowsapp.lib)
endif()

file(
    GLOB INCLUDES
    "${CMAKE_CURRENT_LIST_DIR}/*.hpp"
)

add_library(mdr_PlatformWindows ${SOURCES} ${INCLUDES})
target_link_libraries(mdr_PlatformWindows PRIVATE mdr-c fmt::fmt ws2_32.lib rpcrt4.lib Bthprops.lib ${EXTRA_LIBS})
