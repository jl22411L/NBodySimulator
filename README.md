## SET UP ##

# Clang #
Clang auto formatter is used to manage code quality. Install Clang-Format by Xaver Hellauer. Then go to your user settings json file and add the following settings:
```
"clang-format.executable": "C:/Users/jason/Desktop/Projects/NBodySimulator/.Configuration/Clang/clang-format.exe",
"cmake.configureOnOpen": true
```

When you run the `SetUpDevelopmentEnvironment.sh` script, the up to date clang formatting file should be moved into your workspace.

## FRAMES ##

Unless in very specific situations, all frames can be assumed to follow a right handed orthogonal axis system. For more infomration about rotations, read the ** ROTATION SEQUENCES** section.

| Frame Name  | Abbreviation |                  Description                 | Definition of x-axis | Definition of y-axis |  Definition of z-axis  |                      Note                      |
|:-----------:|:------------:|:--------------------------------------------:|:--------------------:|:--------------------:|:----------------------:|:----------------------------------------------:|
| Fixed Frame |     Fix      | Origin which all frames are based around.    |        [1,0,0]       |        [0,1,0]       |         [0,0,1]        |                                                |
| Body Frame  |     Bod      | Frame used to define the body of rigid body. |   Longitudinal Axis  |     Lateral Axis     | Cross Product of x & y | Note that definition may vary for some bodies. |
 
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
