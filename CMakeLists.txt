cmake_minimum_required(VERSION 3.5)

project(wuci LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set wt_DIR:PATH=/..../Development/wt/usr/lib/cmake/wt
find_package(wt CONFIG REQUIRED)

# TODO Should be set via toolchain
set(OPENWRT_TARGET_DIR /home/build/openwrt/staging_dir/target-x86_64_musl)
# ./scripts/feeds update -a
# ./scripts/feeds install libuci
# make package/libuci/install
# TODO Needs proper find_package()
find_library(UCI_LIBRARY name uci PATHS ${OPENWRT_TARGET_DIR}/usr/lib)
find_path(UCI_INCLUDE name uci.h PATHS ${OPENWRT_TARGET_DIR}/usr/include)
# uci depends on ubox
find_library(UBOX_LIBRARY name ubox PATHS ${OPENWRT_TARGET_DIR}/usr/lib)
find_path(UBOX_INCLUDE name libubox/usock.h PATHS ${OPENWRT_TARGET_DIR}/usr/include)

add_executable(wuci
    main.cpp
    webmain.cpp
    vpnpage.cpp
    wlanpage.cpp
    wlanconfig.cpp
    error.cpp
)
target_include_directories(wuci PUBLIC ${UCI_INCLUDE} ${UBOX_INCLUDE})
target_link_libraries(wuci PUBLIC
  ${UCI_LIBRARY}
  ${UBOX_LIBRARY}
  Wt::Wt
  Wt::HTTP
)
target_compile_features(wuci PUBLIC cxx_std_17)

install(TARGETS wuci RUNTIME DESTINATION bin)
