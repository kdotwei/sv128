# Build Static Library
lib_LIBRARIES = libsv128.a
libsv128_a_SOURCES = sv128.cpp sv_logger.cpp

# Install Headers
pkgincludedir = $(includedir)/sv128
pkginclude_HEADERS = sv128.h sv_logger.h

# Build Test App (No Install)
noinst_PROGRAMS = test_app
test_app_SOURCES = main.cpp
test_app_LDADD = libsv128.a

# Distribute Documentation
EXTRA_DIST = README.md LICENSE API_DOCS.md