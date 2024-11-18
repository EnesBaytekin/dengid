#!/bin/bash

docker run --name builder -v .:/app dengid-builder:v0.1 make
docker rm builder
