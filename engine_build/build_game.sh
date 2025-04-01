#!/bin/bash

BUILDER=DENGID-GAME-BUILDER

RETURNCODE=0

echo -e "\e[32m${BUILDER}: Building the project...\e[0m"
make all
if [ $? -eq 0 ]; then
    echo -e "\e[32m${BUILDER}: The project has been built successfully.\e[0m"
else
    echo -e "\e[31m${BUILDER}: An error occured while building.\e[0m"
    RETURNCODE=1
fi

exit $RETURNCODE
