cmake_minimum_required(VERSION 3.5)

# Setup in OpenWRT SDK
# cd /home/build/openwrt
# touch feeds.conf
# echo "src-link webtoolkit /home/jboehme/Development/wt/source/target/openwrt" > feeds.conf
# cat feeds.conf.default >> feeds.conf
# ./scripts/feeds update -a
# ./scripts/feeds install libuci
# make package/uci/{clean,compile}
# ./scripts/feeds install ubus
# make package/ubus/{clean,compile}
# ./scripts/feeds install boost
# make package/boost/{clean,compile}
# ./scripts/feeds update webtoolkit
# ./scripts/feeds install -a -p webtoolkit
# make package/wt/{clean,compile}


project(wuci LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_VERSION VERSION_LESS "3.8")
  if (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
    set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "-std=c++17")
    set(CMAKE_CXX17_EXTENSION_COMPILE_OPTION "-std=gnu++17")
  elseif (NOT CMAKE_CXX_COMPILER_VERSION VERSION_LESS 5.1)
    set(CMAKE_CXX17_STANDARD_COMPILE_OPTION "-std=c++1z")
    set(CMAKE_CXX17_EXTENSION_COMPILE_OPTION "-std=gnu++1z")
  endif()
endif()

find_package(wt CONFIG REQUIRED)

find_library(UCI_LIBRARY uci)
find_path(UCI_INCLUDE uci.h)

find_library(UBUS_LIBRARY ubus)
find_path(UBUS_INCLUDE libubus.h)

find_library(UBOX_LIBRARY ubox)
find_path(UBOX_INCLUDE libubox/usock.h)

add_executable(wuci
    main.cpp
    webmain.cpp
    vpnpage.cpp
    vpnuploadpage.cpp
    wlanpage.cpp
    universalconfig.cpp
    errorcode.cpp
    messagebus.cpp
)
target_include_directories(wuci PUBLIC ${UCI_INCLUDE} ${UBUS_INCLUDE} ${UBOX_INCLUDE})
target_link_libraries(wuci PUBLIC
  ${UCI_LIBRARY}
  ${UBUS_LIBRARY}
  ${UBOX_LIBRARY}
  Wt::Wt
  Wt::HTTP
)
if(CMAKE_VERSION VERSION_GREATER "3.7")
    target_compile_features(wuci PUBLIC cxx_std_17)
endif()

install(TARGETS wuci RUNTIME DESTINATION bin)

# Notice
#
# Stop service: ubus call service delete '{"name":"uhttpd","instance":"instance1"}'
# Start service:
# List all services: ubus call service list
