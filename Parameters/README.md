# Body Parameters

These parameters are meant to capture the default parameters for bodies.

# Model Parameters

These are paremters for different models. This could include software models as
well as models of physical hardware.

# Specific Parameters

The specific parameters are meant to be used to have flexibility with 
parameters when it comes to running different simulations. Within the
**SpecificParameters** directory, there should be folders which mach the
directory wihin TestCase. This is to make managing the parameters within
the *RunTest.sh* folder easier to manage.

What happens is first the wider parameters are added to the test runs
**Parameters** folder. From this, parameters from the SpecificParameters
are then copied. First parameters within the **DefaultParameters** are
added. What happens is the files within this folder are copied to the
**Parameters** folder in the TestRun. If the file already exists it is
replaced. Then, if the **-s** flag is used, parameters from the specific
configuration are copied over.

The reason for this set up is because each *TestCase* will have its own
unique configuration which will be standard for it but may be different
from the general parameters. Then, you may want to have different
configurations for this specific test case. Hence, the **DefaultParameters** 
are meant to capture the default conditions for the test case, while the
**SpecificParameters** are meant to capture parameters for the different
variations from the default test case.
