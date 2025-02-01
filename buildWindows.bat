@echo off
setlocal enabledelayedexpansion

echo 🛠 Building for Windows...
if exist build rmdir /s /q build
mkdir build && cd build

:: Vérifie si MinGW-w64 est installé
where g++ >nul 2>nul
if %errorlevel% neq 0 (
    echo ❌ MinGW-w64 non trouvé. Installe-le et ajoute-le au PATH.
    exit /b 1
)

:: Vérifie si SDL2 est dans lib
if not exist "..\lib\SDL2" (
    echo 🔽 Téléchargement de SDL2...
    mkdir ..\lib\SDL2
    curl -L -o sdl2.zip https://github.com/libsdl-org/SDL/releases/download/release-2.28.5/SDL2-devel-2.28.5-mingw.zip
    tar -xf sdl2.zip -C ..\lib\SDL2 --strip-components=1
    del sdl2.zip
)

:: Configuration avec CMake
cmake .. -G "MinGW Makefiles" ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DCMAKE_CXX_FLAGS="-O2 -march=x86-64" ^
    -DCMAKE_EXE_LINKER_FLAGS="-static -static-libstdc++ -static-libgcc"

:: Compilation
mingw32-make -j%NUMBER_OF_PROCESSORS%
if %errorlevel% neq 0 (
    echo ❌ Erreur de compilation !
    exit /b 1
)

:: Vérification des dépendances
echo 🔍 Checking dependencies...
for %%f in (SpellWar.exe) do (
    dumpbin /DEPENDENTS %%f | findstr "DLL" > nul
    if !errorlevel! equ 0 (
        echo ❌ Des bibliothèques dynamiques sont encore utilisées !
    ) else (
        echo ✅ Aucune bibliothèque dynamique détectée !
    )
)

cd ..
echo 🚀 Done !

