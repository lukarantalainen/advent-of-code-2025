cmake_minimum_required(VERSION 4.0)
project(AOC25)


add_executable(main
    main.cpp
    day01.cpp
    day02.cpp
    day03.cpp
    day04.cpp
    day05.cpp
    day06.cpp
)

target_sources(main
  PRIVATE
    main.cpp
)

