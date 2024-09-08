## SET UP ##

# Clang #
Clang auto formatter is used to manage code quality. Install Clang-Format by Xaver Hellauer. Then go to your user settings json file and add the following settings:
```
"clang-format.executable": "C:/Users/jason/Desktop/Projects/NBodySimulator/.Configuration/Clang/clang-format.exe",
"cmake.configureOnOpen": true
```

When you run the `SetUpDevelopmentEnvironment.sh` script, the up to date clang formatting file should be moved into your workspace.

# VARIABLE NAMING CONVENTION #

Variables follow the camel case naming convention with the following format.

\<name\>_\<frame\>_\<unit\>_\<input/output\>

Note: If one or more of tags is not required then it can be ommited from the variable. For example, if a vector is independent of a frame, a frame
tag should not be included. (The obvious exception is the 'name' tag)

Note: These conventions where introduced after start of development and hence not all the code may follow it. It is advised that the variable naming conventions be changed at any available oppertunity.

### name ###

This is the name of the variable. Generally it should contain at least 2 descriptive words, although there may be exceptions to having 1. The purpose is to make it easy to identify what the variable represents.


### frame ###

This is to indicate the frame which the vector is orientated against. It does not necessairly mean that it is the frame the variable is in as during transitions you can have a vector that is within an intermediatary frame. If a vector is in the orientation of frame1 but has its origin in frame 2 then the 'frame' is frame1 but the vector is relative to frame2. Hence the term 'RelTo\<frame2\>' should be used in the name tag.

### unit ###

This part of the tag represents the unit of the variable. All units should be lower case, except for places where it may be easier to read if camel case was used. Numbers represent the power to raise the unit to the left.

For example kg m per seconds squared (Newton) is kgms2

### in/out ###

This is to indicate if the variable is an input to a function or an output to a function. If the variable is defined within a function then this part should be ommitted. 

# FRAMES #

Unless in very specific situations, all frames can be assumed to follow a right handed orthogonal axis system. For more infomration about rotations, read the ** ROTATION SEQUENCES** section.

|   Frame Name    | Abbreviation |                  Description                 |   Origin  | Definition of x-axis |  Definition of y-axis  |     Definition of z-axis     |                      Note                      |
|:---------------:|:------------:|:--------------------------------------------:|:---------:|:--------------------:|:----------------------:|:----------------------------:|:----------------------------------------------:|
|  Fixed Frame    |     Fix      | Origin which all frames are based around.    |  [0,0,0]  |      [1,0,0]         |         [0,1,0]        |            [0,0,1]           |                                                |
|   Body Frame    |     Bod      | Frame used to define the body of rigid body. |    COG    |  Longitudinal Axis   |      Lateral Axis      |    Cross Product of x & y    | Note that definition may vary for some bodies. |
| Perifocal Frame |     Per      | Frame used to project orbits of satellites.  | Body1 COG |  Towards Periapsis   | Cross Product of x & z | Unit angular momentum vector | y-axis is parrallel to the Semilatus rectum    |
 
# ROTATIONS #
## QUATERNIONS ##

The standard for quaternions in this project is:

quaternion = [

  X_QUATERNION_COMPONENT,

  Y_QUATERNION_COMPONENT,

  Z_QUATERNION_COMPONENT,

  S_QUATERNION_COMPONENT

]

where, s represents the scalar component.

If applicable, a quaternion can also be broken down into its scalar and vector components:

quaternion_gibs_vector = [

  X_QUATERNION_COMPONENT,

  Y_QUATERNION_COMPONENT,

  Z_QUATERNION_COMPONENT

]

quaternion_scaler = S_QUATERNION_COMPONENT

## EULER ANGLES ##

The standard for Euler Angle vectors is 123 (XYZ).

eulerAngle = [

  ROLL,

  PITCH,

  YAW
  
]

## ROTATION SEQUENCES ##

Whenever euler angles are involved, the rotation sequence is 321 (ZYX).

Positive rotation is defined with respect to the right hand rule.

Yaw is defined as rotation around the z-axis
Pitch is defined as rotation around the y-axis
Roll is defined as rotation around the x-axis
