FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -y \
    build-essential \
    cmake \
    git \
    wget \
    libx11-dev \
    libxcursor-dev \
    libxrandr-dev \
    libxinerama-dev \
    libxi-dev \
    libgl1-mesa-dev \
    vulkan-tools \
    libvulkan-dev \
    mesa-vulkan-drivers

RUN wget https://libsdl.org/release/SDL2-2.30.9.tar.gz && \
    tar -xzf SDL2-2.30.9.tar.gz && \
    cd SDL2-2.30.9 && \
    ./configure && make && make install && \
    cd .. && rm -rf SDL2-2.30.9 SDL2-2.30.9.tar.gz

RUN git clone https://github.com/ocornut/imgui.git /imgui

ENV VULKAN_SDK=/usr/lib/x86_64-linux-gnu
ENV PATH=$VULKAN_SDK/bin:$PATH
ENV LD_LIBRARY_PATH=$VULKAN_SDK/lib:$LD_LIBRARY_PATH

WORKDIR /app
