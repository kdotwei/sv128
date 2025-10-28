#!/bin/bash

# autogen.sh - Generate the build system for sv128

set -e

echo "Running aclocal..."
aclocal

echo "Running autoheader..."
autoheader

echo "Running automake..."
automake --add-missing --copy

echo "Running autoconf..."
autoconf

echo "Autotools setup complete!"
echo "You can now run: ./configure && make"