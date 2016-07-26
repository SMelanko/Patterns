# Create build dir.
BUILD_DIR=../build
echo -- Creating build directory
mkdir $BUILD_DIR
# Go to the build dir.
pushd $BUILD_DIR

# Run CMake.
echo -- Running CMake
cmake -G"Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ..

# Make.
echo -- Running Make
make
