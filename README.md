# Ray Casting Algorithm

## Usage

```
    ./build.sh && ./RayCast
```

## Controls

<br>

Right Click to place a box.<br>
WASD to control the circle.<br>
Right Key to rotate the angle.

## How it Works

<br>

Using the OLC Pixel Game Engine for displaying the graphics, the algorithm trace one ray for each 45° degrees minus the main angle, and 45° degrees plus the main angle. <br>
A ray stop if hit a box, or is to far from the player.