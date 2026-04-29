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
set_target_properties(calculator PROPERTIES
    INSTALL_RPATH "$ORIGIN/../lib/ivscalculator"
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH_USE_LINK_PATH FALSE
)

# ── Install rules ─────────────────────────────────────────────────────────────
include(GNUInstallDirs)
install(TARGETS calculator
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Hardcoded all shared library dependencies
install(FILES
    /usr/lib/x86_64-linux-gnu/libQt6Widgets.so.6
    /usr/lib/x86_64-linux-gnu/libQt6Core.so.6
    /usr/lib/x86_64-linux-gnu/libQt6Gui.so.6
    /usr/lib/x86_64-linux-gnu/libQt6DBus.so.6
    /usr/lib/x86_64-linux-gnu/libEGL.so.1
    /usr/lib/x86_64-linux-gnu/libfontconfig.so.1
    /usr/lib/x86_64-linux-gnu/libX11.so.6
    /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
    /usr/lib/x86_64-linux-gnu/libxkbcommon.so.0
    /usr/lib/x86_64-linux-gnu/libGLX.so.0
    /usr/lib/x86_64-linux-gnu/libOpenGL.so.0
    /usr/lib/x86_64-linux-gnu/libpng16.so.16
    /usr/lib/x86_64-linux-gnu/libharfbuzz.so.0
    /usr/lib/x86_64-linux-gnu/libmd4c.so.0
    /usr/lib/x86_64-linux-gnu/libfreetype.so.6
    /usr/lib/x86_64-linux-gnu/libz.so.1
    /usr/lib/x86_64-linux-gnu/libicui18n.so.74
    /usr/lib/x86_64-linux-gnu/libicuuc.so.74
    /usr/lib/x86_64-linux-gnu/libicudata.so.74
    /usr/lib/x86_64-linux-gnu/libdouble-conversion.so.3
    /usr/lib/x86_64-linux-gnu/libb2.so.1
    /usr/lib/x86_64-linux-gnu/libpcre2-16.so.0
    /usr/lib/x86_64-linux-gnu/libpcre2-8.so.0
    /usr/lib/x86_64-linux-gnu/libzstd.so.1
    /usr/lib/x86_64-linux-gnu/libGLdispatch.so.0
    /usr/lib/x86_64-linux-gnu/libexpat.so.1
    /usr/lib/x86_64-linux-gnu/libxcb.so.1
    /usr/lib/x86_64-linux-gnu/libdbus-1.so.3
    /usr/lib/x86_64-linux-gnu/libgraphite2.so.3
    /usr/lib/x86_64-linux-gnu/libbz2.so.1.0
    /usr/lib/x86_64-linux-gnu/libbrotlidec.so.1
    /usr/lib/x86_64-linux-gnu/libbrotlicommon.so.1
    /usr/lib/x86_64-linux-gnu/libgomp.so.1
    /usr/lib/x86_64-linux-gnu/libXau.so.6
    /usr/lib/x86_64-linux-gnu/libXdmcp.so.6
    /usr/lib/x86_64-linux-gnu/libsystemd.so.0
    /usr/lib/x86_64-linux-gnu/libbsd.so.0
    /usr/lib/x86_64-linux-gnu/libcap.so.2
    /usr/lib/x86_64-linux-gnu/libgcrypt.so.20
    /usr/lib/x86_64-linux-gnu/liblz4.so.1
    /usr/lib/x86_64-linux-gnu/liblzma.so.5
    /usr/lib/x86_64-linux-gnu/libmd.so.0
    /usr/lib/x86_64-linux-gnu/libgpg-error.so.0
    DESTINATION lib/ivscalculator
)

# Qt platform plugins
get_target_property(QT_QMAKE Qt6::qmake IMPORTED_LOCATION)
execute_process(COMMAND ${QT_QMAKE} -query QT_INSTALL_PLUGINS
    OUTPUT_VARIABLE QT_PLUGINS_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
install(FILES ${QT_PLUGINS_DIR}/platforms/libqxcb.so
    DESTINATION lib/ivscalculator/platforms
    OPTIONAL
)
install(FILES ${QT_PLUGINS_DIR}/platforms/libqwayland-generic.so
    DESTINATION lib/ivscalculator/platforms
    OPTIONAL
)

# qt.conf tells Qt where to find its plugins
install(CODE "
    file(WRITE \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/bin/qt.conf\"
        \"[Paths]\nPlugins=../lib/ivscalculator\n\")
")

# Wrapper script so 'calculator.sh' works without setting QT_QPA_PLATFORM manually
install(CODE "
    file(WRITE \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/bin/calculator.sh\"
        \"#!/bin/sh\nQT_QPA_PLATFORM=xcb \\\"\$(dirname \\\"\$0\\\")/calculator\\\" \\\"\$@\\\"\n\")
    file(CHMOD \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/bin/calculator.sh\"
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
")

install(FILES packaging/calculator.desktop
    DESTINATION ${CMAKE_INSTALL_DATADIR}/applications
    OPTIONAL
)

# ── CPack configuration ───────────────────────────────────────────────────────
set(CPACK_PACKAGE_NAME        "IVSCalculator")
set(CPACK_PACKAGE_VENDOR      "Bear Together Stronk")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "IVS Calculator - Qt6 scientific calculator")
set(CPACK_PACKAGE_VERSION     ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT     "xferenj00@stud.fit.vutbr.cz")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README  "${CMAKE_SOURCE_DIR}/README.md")

# ── Generator selection ───────────────────────────────────────────────────────
set(CPACK_GENERATOR "DEB;TGZ")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "xferenj00")
set(CPACK_DEBIAN_PACKAGE_DEPENDS  "libc6 (>= 2.17), libstdc++6 (>= 5.2)")
set(CPACK_DEBIAN_PACKAGE_SECTION  "utils")

include(CPack)
