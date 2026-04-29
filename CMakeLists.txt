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

# Install all shared library dependencies (symlinks + real versioned files)
foreach(LIB
    libQt6Widgets.so
    libQt6Core.so
    libQt6Gui.so
    libQt6DBus.so
    libEGL.so
    libfontconfig.so
    libX11.so
    libglib-2.0.so
    libxkbcommon.so
    libGLX.so
    libOpenGL.so
    libpng16.so
    libharfbuzz.so
    libmd4c.so
    libfreetype.so
    libz.so
    libicui18n.so
    libicuuc.so
    libicudata.so
    libdouble-conversion.so
    libb2.so
    libpcre2-16.so
    libpcre2-8.so
    libzstd.so
    libGLdispatch.so
    libexpat.so
    libxcb.so
    libdbus-1.so
    libgraphite2.so
    libbz2.so
    libbrotlidec.so
    libbrotlicommon.so
    libgomp.so
    libXau.so
    libXdmcp.so
    libsystemd.so
    libbsd.so
    libcap.so
    libgcrypt.so
    liblz4.so
    liblzma.so
    libmd.so
    libgpg-error.so
)
    file(GLOB LIB_FILES "/usr/lib/x86_64-linux-gnu/${LIB}*")
    install(FILES ${LIB_FILES} DESTINATION lib/ivscalculator)
endforeach()

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

# Wrapper script
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
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_SOURCE_DIR}/postinst;${CMAKE_SOURCE_DIR}/postrm")

include(CPack)
