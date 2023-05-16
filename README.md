# RTv1
## CPU Raytracer school project
**RTv1** is a simple CPU-based [raytracer](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)) school project for [Hive](https://www.hive.fi/en/) by [EmmaKantanen](https://github.com/EmmaKantanen) and [ickarjala](https://github.com/ickarjala).\
Written in C on top of SDL2. Uses ickarjala's [libft](https://github.com/ickarjala/42-Libft).

![Preview Scene](/resources/images/pillars.png)

## Features
* Sphere, cylinder (infinite), cone (infinite), plane (infinite)
* Ambient light
* Point light with falloff
* Material colors
* Gloss / Specular
* Custom scene file type / parser

## Installation
Note: currently only supports MacOS!
Prerequisites are `clang`, `make` and `cmake`. SDL2 is provided within the repo.

`cd` to the root of the repository and run `make`. The default rules are -Wall -Wextra -Werror. For convenience there are also:
* `make W` for stricter rules (-Wimplicit -Wunused -Wconversion)
* `make O` for speed optimization (-O3)
* `make D` for a debug build

## Usage
`./rtv1 <scene_description_file>` Try the provided sample scenes in `eval_tests/`.
