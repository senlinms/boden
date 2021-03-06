##########################################################################
# Files

add_sources(_BDN_NET_FILES _BDN_HEADERS ./)

GenerateTopLevelIncludeFile(_BDN_NET_COMBINED ${CMAKE_CURRENT_BINARY_DIR}/include/bdn/net.h ${CMAKE_CURRENT_LIST_DIR}/include ${_BDN_HEADERS})

set(_BDN_NET_FILES ${_BDN_NET_FILES} ${_BDN_NET_COMBINED})

add_sources(_BDN_NET_FILES _BDN_HEADERS ./${BDN_TARGET})

if( BDN_USES_FK )
    add_sources(_BDN_NET_FILES _BDN_HEADERS ./fk)
endif()

if( BDN_USES_JAVA )
    add_sources(_BDN_NET_FILES _BDN_HEADERS ./java)
    file(GLOB_RECURSE _BDN_JAVA_FILES ./src/java/*.cpp ./java/*.java)
    list(APPEND _BDN_NET_FILES ${_BDN_JAVA_FILES})
endif()

if(BDN_NEEDS_TO_BE_SHARED_LIBRARY OR BDN_SHARED_LIB)
    add_library(net SHARED ${_BDN_NET_FILES})
elseif(BDN_NEEDS_TO_BE_STATIC_LIBRARY OR NOT BDN_SHARED_LIB)
    add_library(net STATIC ${_BDN_NET_FILES})
endif()

target_link_libraries(net PUBLIC foundation)
target_include_directories(net
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    )

target_include_directories(net PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>)

add_clangformat(net)

include(install.cmake)

add_subdirectory(platforms)

target_link_libraries(net INTERFACE ${BDN_NET_PLATFORM_LIBRARIES})
