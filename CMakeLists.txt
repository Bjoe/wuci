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

find_package(wt CONFIG REQUIRED)

find_library(UCI_LIBRARY uci)
find_path(UCI_INCLUDE uci.h)
# uci depends on ubox
find_library(UBOX_LIBRARY ubox)
find_path(UBOX_INCLUDE libubox/usock.h)

add_executable(wuci
    main.cpp
    webmain.cpp
    vpnpage.cpp
    vpnuploadpage.cpp
    wlanpage.cpp
    wlanconfig.cpp
    errorcode.cpp
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
