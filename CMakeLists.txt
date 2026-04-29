cmake_minimum_required(VERSION 3.16)
project(IVSCalculator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

# ── Build the calculator executable ──────────────────────────────────────────
add_executable(calculator
    src/gui.cpp
    src/parser.cpp
    src/math_lib.cpp
)

target_link_libraries(calculator PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

# ── Bundle ALL shared library dependencies ────────────────────────────────────
set_target_properties(calculator PROPERTIES
    INSTALL_RPATH "$ORIGIN/../lib/ivscalculator"
    BUILD_WITH_INSTALL_RPATH TRUE
)

# Use CMake's file(GET_RUNTIME_DEPENDENCIES) to collect everything
install(CODE "
    file(GET_RUNTIME_DEPENDENCIES
        EXECUTABLES \$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/bin/calculator
        RESOLVED_DEPENDENCIES_VAR   resolved
        UNRESOLVED_DEPENDENCIES_VAR unresolved
        PRE_EXCLUDE_REGEXES
            \"^libpthread\" \"^libc\\.\" \"^libm\\.\" \"^libdl\\.\"
            \"^librt\\.\"  \"^ld-linux\"
        POST_EXCLUDE_REGEXES
            \"/lib/x86_64-linux-gnu/libc\"
    )
    foreach(dep \${resolved})
        file(INSTALL
            DESTINATION \"\${CMAKE_INSTALL_PREFIX}/lib/ivscalculator\"
            TYPE SHARED_LIBRARY
            FOLLOW_SYMLINK_CHAIN
            FILES \"\${dep}\"
        )
    endforeach()
")

# ── Install rules ─────────────────────────────────────────────────────────────
include(GNUInstallDirs)

install(TARGETS calculator
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Also install Qt platform plugin (required for Qt apps to start)
get_target_property(QT6_WIDGETS_LIB Qt6::Widgets LOCATION)
get_filename_component(QT6_LIB_DIR ${QT6_WIDGETS_LIB} DIRECTORY)

install(FILES ${QT6_LIB_DIR}/../plugins/platforms/libqxcb.so
    DESTINATION lib/ivscalculator/platforms
    OPTIONAL
)
install(FILES ${QT6_LIB_DIR}/../plugins/platforms/libqwayland-generic.so
    DESTINATION lib/ivscalculator/platforms
    OPTIONAL
)

# qt.conf tells Qt where to find its plugins
install(CODE "
    file(WRITE \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/bin/qt.conf\"
        \"[Paths]\nPlugins=../lib/ivscalculator\n\")
")

install(FILES packaging/calculator.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
    OPTIONAL
)

# ── CPack configuration ───────────────────────────────────────────────────────
set(CPACK_PACKAGE_NAME        "IVSCalculator")
set(CPACK_PACKAGE_VENDOR      "Bear Together Stronk")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "IVS Calculator – Qt6 scientific calculator")
set(CPACK_PACKAGE_VERSION     ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT     "xferenj00@stud.fit.vutbr.cz")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README  "${CMAKE_SOURCE_DIR}/README.md")

# ── Generator selection ───────────────────────────────────────────────────────
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "xferenj00")
set(CPACK_DEBIAN_PACKAGE_DEPENDS  "")
set(CPACK_DEBIAN_PACKAGE_SECTION  "utils")

list(APPEND CPACK_GENERATOR "TGZ")

include(CPack)
