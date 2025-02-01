#!/bin/bash

set -e

echo "Building..."
rm -rf build
mkdir build && cd build

cmake .. -DCMAKE_BUILD_TYPE=Release 
make -j$(nproc)

cd ..
cp build/SpellWar ./SpellWar
rm -rf build
echo "Done !"

