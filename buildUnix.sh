#!/bin/bash

set -e

echo "🛠 Building..."
rm -rf build
rm -rf bin
mkdir build && cd build

cmake .. -DCMAKE_BUILD_TYPE=Release 
make -j$(nproc)

cd ..
mkdir bin
cp build/SpellWar bin/SpellWar
rm -rf build
echo "🚀 Done !"

