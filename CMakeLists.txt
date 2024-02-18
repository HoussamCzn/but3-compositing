cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    compositing
    VERSION 0.4.1
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare library ----

set(QT_HEADERS
    include/ui/menu.hxx
    include/ui/window.hxx
)
set(QT_SOURCES
    source/ui/menu.cxx
    source/ui/window.cxx
)

add_library(compositing_lib OBJECT
    source/application.cxx
    source/image/ppm.cxx
    source/utils/builder.cxx
    source/utils/loader.cxx
    ${QT_HEADERS}
    ${QT_SOURCES}
)

target_include_directories(
    compositing_lib ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>"
)

target_compile_features(compositing_lib PUBLIC cxx_std_20)

find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
target_link_libraries(compositing_lib PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# ---- Declare executable ----

add_executable(compositing_exe source/main.cxx)
add_executable(compositing::exe ALIAS compositing_exe)

set_property(TARGET compositing_exe PROPERTY OUTPUT_NAME compositing)

target_compile_features(compositing_exe PRIVATE cxx_std_20)

target_link_libraries(compositing_exe PRIVATE compositing_lib)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT compositing_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of compositing"
  )
endif()

include(cmake/dev-mode.cmake)
