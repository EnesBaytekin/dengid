#!/bin/bash

BUILDER=DENGID-GAME-BUILDER

RETURNCODE=0

# Check if docker is running
if ! systemctl is-active --quiet docker.socket; then
    echo -e "\e[32m${BUILDER}: Starting docker...\e[0m"
    # Start docker if not running
    sudo systemctl start docker.socket
    if ! systemctl is-active --quiet docker.socket; then
        echo -e "\e[31m${BUILDER}: Docker could not be started.\e[0m"
        exit 1
    fi
    DOCKER_STARTED=true
else
    echo -e "\e[32m${BUILDER}: Docker is already running.\e[0m"
    DOCKER_STARTED=false
fi

# Create and delete a container to build the project
echo -e "\e[32m${BUILDER}: Building the project in a container...\e[0m"
cd ..
docker run --rm -v .:/app dengid-builder:v0.2 echo > /dev/null && cd engine_build && make clean all && cp -r icon.png game_build/
if [ $? -eq 0 ]; then
    echo -e "\e[32m${BUILDER}: The project has been built successfully.\e[0m"
else
    echo -e "\e[31m${BUILDER}: An error occured while building.\e[0m"
    RETURNCODE=1
fi
echo -e "\e[32m${BUILDER}: Container is deleted.\e[0m"

if [ "$DOCKER_STARTED" = true ]; then
    if [[ $1 == "--no-stop" || $1 == "-n" ]]; then
        # Do not stop docker if --no-stop flag is given
        echo -e "\e[33m${BUILDER}: Docker is left running.\e[0m"
    else
        # Stop docker if it was not running before the script
        echo -e "\e[32m${BUILDER}: Stopping docker...\e[0m"
        sudo systemctl stop docker.socket
    fi
fi

exit $RETURNCODE
