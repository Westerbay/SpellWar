#!/bin/bash

set -e

echo "Building..."
mkdir -p build && cd build

cmake .. -DCMAKE_BUILD_TYPE=Release 
make -j$(nproc)

cd ..
cp build/SpellWar ./SpellWar
echo "Done !"

