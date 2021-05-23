cmake_minimum_required(VERSION 3.1)

option(RUN_PROD "Prod?" OFF)

set(project_name donarity) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/SitePath.hpp
        src/controller/StaticController.hpp
        src/StaticFileManager.cpp
        src/StaticFileManager.hpp
        src/FilesIndex.cpp
        src/FilesIndex.hpp
        src/Sitemap.cpp
        src/Sitemap.hpp
        src/dto/EmployeeDto.hpp src/controller/EmployeeController.hpp src/db/EmployeeDb.hpp src/DatabaseComponent.hpp src/dto/ConfigDto.hpp src/service/EmployeeService.cpp src/service/EmployeeService.hpp src/dto/PageDto.hpp)

## link libs
set(ENV{LIBRESSL_ROOT_DIR} "/opt/homebrew/opt/libressl")
set(ENV{LIBRESSL_INCLUDE_DIR} "/opt/homebrew/opt/libressl/include")

find_package(oatpp              1.2.5 REQUIRED)
find_package(oatpp-libressl     1.2.5 REQUIRED)
find_package(oatpp-zlib         1.2.5 REQUIRED)
find_package(oatpp-postgresql   1.2.5 REQUIRED)
find_package(ZLIB)

include(FindPkgConfig) # <-- include pkg-config needed by FindLibreSSL.cmake script
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake") # <-- use FindLibreSSL.cmake in /cmake folder

find_package(LibreSSL 3.0.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-test
        PUBLIC oatpp::oatpp-libressl
        PUBLIC oatpp::oatpp-zlib
        PUBLIC oatpp::oatpp-postgresql
        PUBLIC ZLIB::ZLIB
)

target_include_directories(${project_name}-lib
        PUBLIC /usr/local/include
)

link_directories(/usr/local/lib)

target_include_directories(${project_name}-lib PUBLIC src)

add_definitions(
        -DFRONT_PATH="${CMAKE_CURRENT_LIST_DIR}/../../front/build"
        -DAPI_BASE="/api"
        # Path to config file #
        -DCONFIG_PATH="${CMAKE_CURRENT_LIST_DIR}/resources/config.json"
)

if(RUN_PROD)
    add_definitions(-DOATPP_TARGET_APP)
endif()

## add executables

add_executable(${project_name}
        src/App.cpp
)

target_link_libraries(${project_name} ${project_name}-lib)
add_dependencies(${project_name} ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
)
target_link_libraries(${project_name}-test ${project_name}-lib)
add_dependencies(${project_name}-test ${project_name}-lib)

