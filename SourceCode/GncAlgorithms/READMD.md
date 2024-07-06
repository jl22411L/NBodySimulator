# Overview

GncAlgorithms is split up into the different sections of GNC. The idea behind the
module is organise different algorithms for different parts of the GNC stack. It is worth noting that these algorithms are meant to be
representetive of what goes on board an actual system and hence there
performance and efficiency should be prioritised.

## Guidance

Guidance is meant to represent the determination algorithms for the simulator.

## Navigation

Navigation relates to the path planning side of the module. This is to determine
where the body should be or going. The output of Navigation will primarely
be the input to the control algorithm.

## Control

Control is used to determine what the inputs to the system should be, primarely
to actuators.
