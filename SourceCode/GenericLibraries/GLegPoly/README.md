# MODULE INFO

This module contains functions relating to Legendre Polynomials. It was decided that these deserve there own module rather then be integrated into GMath module because it is a wide topic and it was expected that things could get complicated when it came to implementation of the different functionalities. Hence, to try and contain the mess, its own module was given to allow for more flexebility when developing the different functionality.

The name of the module is LegPoly which is a shortened version for Legendre Polynomials. The naming of functions and variables was a challenge to keep short.

## Optimised Code

This module can be quite lengthy and it is intended that some of these functions get implemented in actual flight code. Hence, at the time of writing, it was decided that it would be best to split the module into 2 sub sections, code that can be developed and tested for simulation along with optimised code which can be implemented in flight hardware.

The reason for the split is the intention that the flight code will not be as readable and follow the general coding standards implemented in the NBS but will be more performative. Further, the intention is to also allow for the the performative code to be compared to the general code to verify that it works correctly.

# Legendre Polynomials

Legendre Polynomials are a range of polynomials which have a bunch of proeprties about how they relate to each other. They're application is primarel to spherical harmonics and in the context of the NBS there main application is to finding the magnetic field vector. Essentially, the Legendre Polynomials are used to simulate spheres of different shapes and harmonics and summing them together to get a complex spherical harmonic output which varies with time (similar to fourier series). It essentially allows for imperical modelling of spherical objeects and how they change with time.

With Legendre Polynomials there are different orders (m) and degrees (n). Within this module, n represents the rows and m represents columns of an array output. Essentially, the different orders are different classes of Legendre Polynomials. (It is quite complciated and takes a bit of reading to understand what the different orders don't understand - not fully understood at time of writing but know how to find them and apply them to equtions). One thing to note is that abs(m) \< n.

There is also the possibility to have negative degrees, however that is not implemented in this module.
