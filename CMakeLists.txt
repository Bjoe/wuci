cmake_minimum_required(VERSION 3.5)

project(wuci LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set wt_DIR:PATH=/..../Development/wt/usr/lib/cmake/wt
find_package(wt CONFIG REQUIRED)

add_executable(wuci main.cpp webmain.cpp vpnpage.cpp wlanpage.cpp)

target_link_libraries(wuci PUBLIC
  Wt::Wt
  Wt::HTTP
)
target_compile_features(wuci PUBLIC cxx_std_17)

install(TARGETS wuci RUNTIME DESTINATION bin)
