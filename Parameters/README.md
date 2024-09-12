# Body Parameters

These parameters are meant to capture the default parameters for bodies.

*NOTE: These parameters will not be copied into the Parameters folder. A copy
should be moved into the respective SpecificParameters folder to be used within
simulation.*

# Model Parameters

These are paremters for different models. This could include software models as
well as models of physical hardware.

*NOTE: These parameters will not be copied into the Parameters folder. A copy
should be moved into the respective SpecificParameters folder to be used within
simulation.*

# Simulation Parameters

These are paremeters that realte to the simulation. In general there should be
one ini file for each module, at most and as a rule of thumb. The idea being
that these parameters are related to how realistic the simulation is.

*NOTE: These parameters will not be copied into the Parameters folder. A copy
should be moved into the respective SpecificParameters folder to be used within
simulation.*

# Test Parameters

The specific parameters are meant to be used to have flexibility with 
parameters when it comes to running different simulations. Within the
**TestParameters** directory, there should be folders which mach the
directory wihin TestCase. This is to make managing the parameters within
the *RunTest.sh* folder easier to manage.

What happens is first the parameters from Default parameters are originally
added to the **Parameters** folder within the **TestRun**. Then, if a **-s** flag
is parsed in the **./RunTest.sh** folder, then parameters are copied from the
respective parameter folder and overwrite them.

The reason for this set up is because each *TestCase* will have its own
unique configuration which will be standard for it but may be different
from the general parameters. Then, you may want to have different
configurations for this specific test case. Hence, the **DefaultParameters** 
are meant to capture the default conditions for the test case, while the
**SpecificParameters** are meant to capture parameters for the different
variations from the default test case.
