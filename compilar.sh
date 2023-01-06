#!/bin/bash
find . -maxdepth 1 -name '*.cpp' -execdir g++ -o braco '{}' -lGL -lGLU -lglut \;
./braco
