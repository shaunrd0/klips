# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.26)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(
    #[[NAME]]   temp-humidity-web
    VERSION     0.1
    DESCRIPTION "Temperature and humidity from DHT sensor served on a web page"
    LANGUAGES   CXX
)
message(STATUS "[Klips] Configuring example: ${PROJECT_NAME}")

# For writing pure cmake components, see the documentation
# https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-guides/build-system.html#writing-pure-cmake-components
idf_build_set_property(COMPILE_OPTIONS "-Wno-error" APPEND)
