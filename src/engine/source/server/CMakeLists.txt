set(ENGINE_SERVER_SOURCE_DIR ${ENGINE_SOURCE_DIR}/server/src)
set(ENGINE_SERVER_INCLUDE_DIR ${ENGINE_SOURCE_DIR}/server/include)

####################################################################################################
# Dependencies
####################################################################################################
CPMAddPackage(
  NAME libuv
  GITHUB_REPOSITORY libuv/libuv
  GIT_TAG v1.34.2
  VERSION 1.34.2
  OPTIONS
      "BUILD_SHARED_LIBS ON"
      "BUILD_TESTS OFF"
      "BUILD_EXAMPLES OFF"
  EXCLUDE_FROM_ALL YES
)
# wazuh/src/engine/build/_deps/libuv-src/src/unix/core.c:1211: warning: Using 'getpwuid_r' in statically linked applications requires at runtime the shared libraries from the glibc version used for linking

CPMAddPackage(
  NAME uvw
  GITHUB_REPOSITORY skypjack/uvw
  GIT_TAG v2.3.1_libuv-v1.34
  VERSION 2.3.1
  OPTIONS
      "BUILD_UVW_LIBS OFF"
      "BUILD_DOCS OFF"
      "BUILD_TESTING OFF"
  EXCLUDE_FROM_ALL YES
)

####################################################################################################
# Sources - Includes
####################################################################################################
add_library(server STATIC
    ${ENGINE_SERVER_SOURCE_DIR}/engineServer.cpp
    ${ENGINE_SERVER_SOURCE_DIR}/endpoint.cpp
    ${ENGINE_SERVER_SOURCE_DIR}/endpoints/unixDatagram.cpp
    ${ENGINE_SERVER_SOURCE_DIR}/endpoints/unixStream.cpp
    ${ENGINE_SERVER_SOURCE_DIR}/protocolHandler.cpp
    ${ENGINE_SERVER_SOURCE_DIR}/protocolHandlers/wStream.cpp
)

#TODO do this better
target_link_libraries(server base uv_a api queue metrics)

target_include_directories(server
    PUBLIC
    ${ENGINE_SERVER_INCLUDE_DIR}
    ${uvw_SOURCE_DIR}/src/
)

# Tests
if(ENGINE_BUILD_TEST)

set(TEST_SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/test/src)
set(UNIT_SRC_DIR ${TEST_SRC_DIR}/unit)

add_executable(server_utest
    ${UNIT_SRC_DIR}/engineServer_test.cpp
    ${UNIT_SRC_DIR}/unixDatagram_test.cpp
    ${UNIT_SRC_DIR}/unixStream_test.cpp
    ${UNIT_SRC_DIR}/protocolHandlerStream_test.cpp
)

target_include_directories(server_utest
    PRIVATE
    ${uvw_SOURCE_DIR}/src/
)

target_link_libraries(server_utest PRIVATE gtest_main server uv_a)
gtest_discover_tests(server_utest)

endif(ENGINE_BUILD_TEST)
