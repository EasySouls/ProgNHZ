cmake_minimum_required(VERSION 3.26)
project(ProgNZH_THSTAM C)

set(CMAKE_C_STANDARD 23)

add_executable(ProgNZH_THSTAM main.c
        game.c
        character.c
        io.c
        inventory.c
        location.c
        location.h
)
