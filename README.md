# RTv1
**RTv1** is a simple CPU-based [raytracer](https://en.wikipedia.org/wiki/Ray_tracing_(graphics)) school project for [Hive](https://www.hive.fi/en/) by [ekantane](https://github.com/EmmaKantanen) and [ikarjala](https://github.com/chrisuka).\
Written in C on top of SDL2. Uses ikarjala's [libft](https://github.com/chrisuka/42_libft).

![Preview Scene](/resources/images/pillars.png)

## Features
* Sphere, cylinder (infinite), cone (infinite), plane (infinite)
* Ambient light
* Multiple point lights with falloff
* Material colors
* Gloss / Specular
* Custom scene file type / parser

## Installation
Note: currently only supports MacOS!
Prerequisites are `clang` and `make`. SDL2 is provided as a framework package within the repo.

`cd` to the root of the repository and run `make`. The default rules are -Wall -Wextra -Werror. For convenience there are also:
* `make W` for stricter rules (-Wimplicit -Wunused -Wconversion)
* `make O` for speed optimization (-O3)
* `make D` for a debug build

## Usage
`./rtv1 <scene_description_file>` Try the provided sample scenes in `eval_tests/`.
