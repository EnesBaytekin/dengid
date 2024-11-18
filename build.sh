#!/bin/bash

if ! [ -d lib ]; then
    mkdir lib
fi

if [ -d lib/SDL2 ]; then
    echo -e "\e[32mSDL2 is already exist\e[0m"
else
    echo -e "\e[33mdownloading SDL2...\e[0m"
    cd lib
    wget https://github.com/libsdl-org/SDL/releases/download/release-2.30.9/SDL2-2.30.9.tar.gz
    tar -xvzf SDL2-2.30.9.tar.gz
    rm SDL2-2.30.9.tar.gz
    mv SDL2-2.30.9 SDL2
    cd SDL2
    echo -e "\e[33mbuilding SDL2...\e[0m"
    ./configure --prefix=$(pwd)/build
    make
    make install
    cd ../..
    echo -e "\e[32mSDL2 is ready\e[0m"
fi

if [ -d lib/imgui ]; then
    echo -e "\e[32mimgui is already exist\e[0m"
else
    echo -e "\e[33mcloning imgui...\e[0m"
    cd lib
    git clone https://github.com/ocornut/imgui.git
    cd ..
    echo -e "\e[32mimgui is ready\e[0m"
fi

echo -e "\e[33mbuilding the project...\e[0m"
make clean all

