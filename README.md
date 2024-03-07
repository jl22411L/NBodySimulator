## SET UP ##

# Clang #
Clang auto formatter is used to manage code quality. Install Clang-Format by Xaver Hellauer. Then go to your user settings json file and add the following settings:
```
"clang-format.executable": "C:/Users/jason/Desktop/Projects/NBodySimulator/.Configuration/Clang/clang-format.exe",
"cmake.configureOnOpen": true
```

When you run the `SetUpDevelopmentEnvironment.sh` script, the up to date clang formatting file should be moved into your workspace.

## FRAMES ##

| Frame Name           | Abbreviation | Description                                   | Definition of x-axis | Definition of y-axis | Definition of z-axis  |
|:--------------------:|:------------:|:---------------------------------------------:|:--------------------:|:--------------------:|:----------------------:|
| Fixed Frame          | Fix          | Origin which all frames are based around.     | [1,0,0]              | [0,1,0]              | [0,0,1]                |
| Satellite Body Frame | SB           | Frame used to define the body of a satellite. | Longitudinal Axis    | Lateral Axis         | Cross Product of x & y |
