#!/bin/bash


gcc *.c -o dbg -Wall -O3 -std=gnu99 -lraylib -lGL -lGLU -lGLEW -lm -lpthread && ./dbg