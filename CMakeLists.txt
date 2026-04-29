cmake_minimum_required(VERSION 3.16)
project(IVSCalculator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)          # replaces your manual moc step

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# ── Build the calculator executable ──────────────────────────────────────────
add_executable(calculator
    src/gui.cpp
    src/parser.cpp
    src/math_lib.cpp
)
target_link_libraries(calculator PRIVATE Qt6::Widgets)

# ── Install rules ─────────────────────────────────────────────────────────────
include(GNUInstallDirs)   # gives CMAKE_INSTALL_BINDIR, DATADIR, etc.

install(TARGETS calculator
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}   # → /usr/local/bin
)

# Optional: install a desktop entry for the app menu
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
# Linux .deb
set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "xferenj00")
set(CPACK_DEBIAN_PACKAGE_DEPENDS  "libqt6widgets6 (>= 6.0)")
set(CPACK_DEBIAN_PACKAGE_SECTION  "utils")

# Linux .rpm  ← uncomment if you also want RPM
# list(APPEND CPACK_GENERATOR "RPM")
# set(CPACK_RPM_PACKAGE_REQUIRES "qt6-qtbase >= 6.0")

# .tar.gz for generic Linux
list(APPEND CPACK_GENERATOR "TGZ")

include(CPack)
