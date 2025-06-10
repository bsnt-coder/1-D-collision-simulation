# 1-D-Collision-simulation

# Problem Summary

We have \( n \) point objects in a one-dimensional, gravity-free universe. Each object has:
- A mass \( m_i \)
- An initial position \( x_i \)
- An initial velocity \( v_i \)

The objects are numbered from left to right, so \( x_0 < x_1 < . . . . < x_{n-1} \).

## Key Points:
1. **Elastic Collisions**: When two objects collide, the collision is elastic, meaning both momentum and kinetic energy are conserved.
2. **Collision Representation**: A collision between objects \( i \) and \( i+1 \) is represented as a tuple \((t, i, x)\), where:
   - \( t \) is the time of the collision.
   - \( i \) is the index of the left object in the collision.
   - \( x \) is the position at which the collision occurs.

3. **Order of Collisions**: Collisions need to be listed in chronological order. If multiple collisions happen at the same time, they are ordered from left to right (i.e., smaller index first).

## Inputs:
- **M**: A list of masses for the objects.
- **x**: A sorted list of initial positions for the objects.
- **v**: A list of initial velocities for the objects.
- **m**: A non-negative integer specifying the maximum number of collisions to record.
- **T**: A non-negative float specifying the maximum time until which we need to record collisions.


## Overview
Simulates elastic collisions between `n` objects in a one-dimensional, gravity-free universe. The function calculates collisions based on given masses, initial positions, and velocities.

## Features
- Simulates up to `m` collisions or until time `T` is reached.
- Outputs collisions in chronological order.
- Handles elastic collisions conserving both momentum and kinetic energy.
- Efficiently runs in O(n + m log n) time.


## Output:
- A list of collision events (up to \( m \) events or until time \( T \) is reached), each represented as a tuple \((t, i, x)\).

## Requirements:
1. **Data Structures**: The function should use appropriate data structures to efficiently compute and store collision events.
2. **Time Complexity**: The function should run in \( O(n + m log n) \) time.
