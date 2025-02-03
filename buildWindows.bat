@echo off
setlocal enabledelayedexpansion

:: Activer l'arrêt en cas d'erreur
goto :main
:err
exit /b 1

:main
echo Building...

IF NOT EXIST build (
        mkdir build 
)
cd build

:: Exécuter CMake
cmake .. -DCMAKE_BUILD_TYPE=Release || goto :err

:: Compiler avec tous les cœurs disponibles
cmake --build . -- /maxcpucount || goto :err

echo Move exe
cd ..
copy build\Debug\SpellWar.exe .\SpellWar.exe || goto :err

echo Done !
