# Parent project does not export its library target, so this CML implicitly
# depends on being added from it, i.e. the testing is done only from the build
# tree and is not feasible from an install location

project(compositingTests LANGUAGES CXX)

# ---- Dependencies ----

find_package(Catch2 REQUIRED)
include(Catch)

# ---- Tests ----

add_executable(compositing_test
    source/compositing_test.cxx
)

target_link_libraries(
    compositing_test PRIVATE
    compositing_lib
    Catch2::Catch2WithMain
)
target_compile_features(compositing_test PRIVATE cxx_std_20)

catch_discover_tests(compositing_test)

# ---- End-of-file commands ----

add_folders(Test)
