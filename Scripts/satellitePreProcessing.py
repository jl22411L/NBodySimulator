#!/bin/env/python

from pathlib import Path
from math import pi as PI
import numpy as np
import configparser
import argparse
import yaml


# ----------------------------------------------------------------------------- #
#                                   CONSTANTS                                   #
# ----------------------------------------------------------------------------- #

# Conversion Constants
DEG_TO_RAD = PI / 180

# Universal Gravitation Constant
UNIVERSAL_GRAVITATIONAL_CONSTANT_KM3KGS2 = 6.6743 * 10**-20


def keplarianToCartesian(massBody1_kg_in: float,
                         massBody2_kg_in: float,
                         semiMajorAxis_km_in: float,
                         eccentricity_in: float,
                         inclintaion_rad_in: float,
                         argOfPeriapsis_rad_in: float,
                         raans_rad_in: float,
                         timeSincePeriapsis_s_in: float) -> tuple:
  """
  @details      Function which finds the initial conditions of two bodies in a
                cartesian frame from the keplarian elements relative to body 1.

                Body 2 is assumed to be the smaller body and hence the one which
                is seen orbiting with reference to body 1.

                It is assumed that at time 0, body 1 will be at the periapsis of
                the orbit.

  @param[in]    massBody1_kg_in
                Mass of body 1, which is the stationary body

  @param[in]    massBody2_kg_in
                Mass of body 2, which is the orbiting body

  @param[in]    semiMajorAxis_km_in
                Semi major axis of the orbit in km.

  @param[in]    eccentricity_in
                Eccentricty of the orbit

  @param[in]    inclintaion_rad_in
                Inclination of the orbit

  @param[in]    argOfPeriapsis_rad_in
                Argument of Periapsis of the orbit

  @param[in]    raans_rad_in
                Right Accension of Accending Nodes

  @param[in]    timeSincePeriapsis_s_in
                Time since periapsis of the orbit

  @return       (orbitalPositionRelFix_Bod1_km_out,
                orbitalVelocityRelFix_Bod1_km_out)
  """

  # Find standard gravitational parameters (mu)
  # https://en.wikipedia.org/wiki/Standard_gravitational_parameter
  gravitationalParameter_km3kg2s2 = (UNIVERSAL_GRAVITATIONAL_CONSTANT_KM3KGS2 *
                                     massBody1_kg_in +
                                     UNIVERSAL_GRAVITATIONAL_CONSTANT_KM3KGS2 *
                                     massBody2_kg_in)

  # Find the angular momentum of the orbit
  orbitalAngularMomentum_km2s = np.sqrt(semiMajorAxis_km_in *
                                        gravitationalParameter_km3kg2s2 *
                                        (1 - eccentricity_in**2))

  # Find time period of orbit
  orbitalTimePeriod_s = (2 * PI *
                         semiMajorAxis_km_in ** (3 / 2) /
                         np.sqrt(gravitationalParameter_km3kg2s2))

  # Find the time since periapsis
  while timeSincePeriapsis_s_in > orbitalTimePeriod_s:
    # Keep subtracting orbital time period until time is less then a period
    timeSincePeriapsis_s_in -= orbitalTimePeriod_s

  # Find the average angular rate of body 2
  averageAngularRate_rads = 2 * PI / orbitalTimePeriod_s

  # Find the mean anomonly
  meanAnomoly = averageAngularRate_rads * timeSincePeriapsis_s_in

  # Find the eccentric anomoly
  eccentricAnomoly = findEccentricAnomoly(meanAnomoly, eccentricity_in)

  # Find the true anomoly
  trueAnomoly = 2 * np.arctan2(np.sqrt(1 + eccentricity_in) *
                               np.tan(eccentricAnomoly / 2),
                               np.sqrt(1 - eccentricity_in))

  # Check to make sure true anomoly is positive
  if trueAnomoly < 0:
    trueAnomoly + 2 * PI

  # Find the position magnitude of body 2 with respect to body 1
  orbitalPositionMag_km = ((orbitalAngularMomentum_km2s**2) /
                           gravitationalParameter_km3kg2s2 /
                           (1 + eccentricity_in * np.cos(trueAnomoly)))

  # Find the position vector of body 2 with respect to body 1 in the orbit frame
  orbitalPosition_Per_km = orbitalPositionMag_km * np.array([
      np.cos(trueAnomoly),
      np.sin(trueAnomoly),
      0
  ])

  # Find the velocity magnitude of the orbit
  orbitalVelocityMag_kms = (gravitationalParameter_km3kg2s2 /
                            orbitalAngularMomentum_km2s)

  # Find the velocity vector of body 2 with respect to body 1 in the orbit frame
  orbitalVelocity_Per_kms = orbitalVelocityMag_kms * np.array([
      -np.sin(trueAnomoly),
      eccentricity_in + np.cos(trueAnomoly),
      0
  ])

  # Create dcm for rotation around z axis for raans
  zRaansRotationDcm = np.array([
      [np.cos(raans_rad_in), np.sin(raans_rad_in), 0],
      [-np.sin(raans_rad_in), np.cos(raans_rad_in), 0],
      [0, 0, 1]
  ])

  # Create dcm for rotation around x axis for inclination
  xInclinationDcm = np.array([
      [1, 0, 0],
      [0, np.cos(inclintaion_rad_in), np.sin(inclintaion_rad_in)],
      [0, -np.sin(inclintaion_rad_in), np.cos(inclintaion_rad_in)]
  ])

  # Create dcm for rotation around z axis for argument of periapsis
  zArgumentOfPeriapsisDcm = np.array([
      [np.cos(argOfPeriapsis_rad_in), np.sin(argOfPeriapsis_rad_in), 0],
      [-np.sin(argOfPeriapsis_rad_in), np.cos(argOfPeriapsis_rad_in), 0],
      [0, 0, 1]
  ])

  # Find rotation matrix from Perifocal frame to Bod1 frame
  perToBod1Dcm = (zArgumentOfPeriapsisDcm @
                  xInclinationDcm @
                  zRaansRotationDcm).transpose()

  # Find the position of body 2 in body1 frame relative to the fixed frame
  orbitalPositionRelFix_Bod1_km_out = perToBod1Dcm @ orbitalPosition_Per_km

  # Find the velocity of body 2 in body1 frame relative to the fixed frame
  orbitalVelocityRelFix_Bod1_km_out = perToBod1Dcm @ orbitalVelocity_Per_kms

  return (orbitalPositionRelFix_Bod1_km_out, orbitalVelocityRelFix_Bod1_km_out)


def findEccentricAnomoly(meanAnomly_rad_in: float,
                         eccentricity_in: float,
                         maxIterations_in: int = 10000,
                         tolerance_in: float = 10**(-16)):
  """
  @details      This function finds the eccentric anomoly using Newton-Raphson
                method.

  @param[in]    meanAnomly_rad_in
                Mean anomoly of the orbit in radians

  @param[in]    eccentricity_in
                Eccentricity of the orbit

  @param[in]    maxIterations_in
                Max iterations to solve for the eccentric anomly

  @param[in]    tolerance_in
                Tolerance for how accurate

  @return       eccentricAnomoly_rad_out
                Ecentric Anomoly
  """

  # Declare initial guess for ecentricic anomoly
  eccentricAnomoly_rad_out = meanAnomly_rad_in

  for i in range(0, maxIterations_in):
    # Find the functino output of the ecentric anomoly
    functionOutput = (eccentricAnomoly_rad_out - eccentricity_in *
                      np.sin(eccentricAnomoly_rad_out) - meanAnomly_rad_in)

    # Find the tangent line value of the ecentric anomoly
    tangentFuntcionOutput = 1 - eccentricity_in * \
        np.cos(eccentricAnomoly_rad_out)

    # Update guess for ecentric anomoly
    eccentricAnomoly_rad_out -= functionOutput / tangentFuntcionOutput

    # Check if tolerance has been reached by function output and if so break loop
    if functionOutput < tolerance_in:
      break

  return eccentricAnomoly_rad_out


def saveSatelliteState(initialPosition_km_in: np.ndarray,
                       initialVelocity_kms_in: np.ndarray,
                       fileDir_in: Path):
  """
  @details      This function will find an ini file and update its position and
                velocity inputs.

                The reason this function is formatted the way it is, is to
                preserve the comments and format of the original ini file.

  @param[in]    initialPosition_km_in
                Initial position to update the ini file.

  @param[in]    initialVelocity_kms_in
                Initial velocity to update the ini file.

  @param[in]    fileDir_in
                Directory to ini file to update the parameters

  @return       This function has not return
  """
  # Check to make sure input directory is a path object
  if type(fileDir_in) is not Path:
    fileDir_in = Path(fileDir_in)

  # Check that input directory exists
  if fileDir_in.is_file() is not True:
    raise RuntimeError(f'"{fileDir_in}" can not be found to save inputs')

  with open(fileDir_in, 'r') as paramFile:
    # Initiate variable to keep track of file contents
    fileContent = ''

    # Read first line of file
    line = paramFile.readline()

    # Iterate through file until reaching end of file
    while line:
      # Check line represents initial position and if update to new position
      if line[0:23] == 'fixedFramePosition_m[0]':
        line = f'fixedFramePosition_m[0] = {initialPosition_km_in[0] * 1000}\n'
      elif line[0:23] == 'fixedFramePosition_m[1]':
        line = f'fixedFramePosition_m[1] = {initialPosition_km_in[1] * 1000}\n'
      elif line[0:23] == 'fixedFramePosition_m[2]':
        line = f'fixedFramePosition_m[2] = {initialPosition_km_in[2] * 1000}\n'

      # Check line represents initial velocity and if update to new velocity
      if line[0:24] == 'fixedFrameVelocity_ms[0]':
        line = (f'fixedFrameVelocity_ms[0] = '
                f'{initialVelocity_kms_in[0] * 1000}\n')
      elif line[0:24] == 'fixedFrameVelocity_ms[1]':
        line = (f'fixedFrameVelocity_ms[1] = '
                f'{initialVelocity_kms_in[1] * 1000}\n')
      elif line[0:24] == 'fixedFrameVelocity_ms[2]':
        line = (f'fixedFrameVelocity_ms[2] = '
                f'{initialVelocity_kms_in[2] * 1000}\n')

      # Add line to file content
      fileContent += line

      # Read next line
      line = paramFile.readline()

  # Write the updated file content
  with open(fileDir_in, 'w') as paramFile:
    paramFile.write(fileContent)


def satellitePreProcessing(configFile_in: Path,
                           mainBody_in: int = 0):
  """
  @details      This function performs the pre processing to find the satellites
                initial conditions. It takes in a yaml file which has the
                parameters requried by the pre processing.

  @param[in]    configFile_in
                Path to yaml file which contains parameters for pre processing.

  @param[in]    mainBody_in
                Integer representing what the main body of interest is. This is
                so that the main body which should be centered in the simulation
                is placed at the origin of the fixed frame. Default value is to
                place the 0th body at the origin.

  @return       This fucntion has no returns
  """
  # Create config parser object
  iniParser = configparser.ConfigParser()

  # Check to make sure input directory is a path object
  if type(configFile_in) is not Path:
    configFile_in = Path(configFile_in)

  # Check that input directory exists
  if configFile_in.is_file() is not True:
    raise RuntimeError(f'"{configFile_in}" can not be found to save inputs')

  # Extract parameter root directory
  parameterRootDir = configFile_in.parent

  # Open file and load pre processing parameters
  with open(configFile_in, 'r') as configFile:
    parameters = yaml.safe_load(configFile)

  # Initiate variable which will be used to keep track of transformations
  accumlatedTranslation_km = np.zeros(3)
  accumlatedVelocity_kms = np.zeros(3)

  # Initiate list to keep track of bodies positions
  bodyPositionList = [accumlatedTranslation_km]
  bodyVelocityList = [accumlatedVelocity_kms]

  # Start for loop and iterate through, preprocessing for all
  for i in range(1, parameters['nBodies']):
    # Create path object to body i-1 ini file
    prevBodDir = Path(f'{parameterRootDir}/{parameters[f'body{i - 1}']}.ini')

    # Create path object to body i to ini file
    currBodDir = Path(f'{parameterRootDir}/{parameters[f'body{i}']}.ini')

    # Extract keplarian elements
    semiMajorAxis_km = parameters[(
        f'keplarianElementsBody{i - 1}ToBody{i}')][('semiMajorAxis_km')]

    eccentricity = parameters[(
        f'keplarianElementsBody{i - 1}ToBody{i}')][('eccentricity')]

    inclinateion_deg = parameters[(
        f'keplarianElementsBody{i - 1}ToBody{i}')][('inclination_deg')]

    argumentOfPerigee_deg = parameters[
        (f'keplarianElementsBody{i - 1}ToBody{i}')][('argumentOfPerigee_deg')]

    raans_deg = parameters[
        (f'keplarianElementsBody{i - 1}ToBody{i}')][('raans_deg')]

    timeSincePeriapsis_s = parameters[
        (f'keplarianElementsBody{i - 1}ToBody{i}')][('timeSincePeriapsis_s')]

    # Check that prev body ini file exists
    if prevBodDir.is_file() is False:
      raise RuntimeError(f'"{prevBodDir}" can not be found')

    # Check that curent body ini file exists
    if currBodDir.is_file() is False:
      raise RuntimeError(f'"{currBodDir}" can not be found')

    # Open body i-i parameter file
    with open(prevBodDir, 'r') as prevBodyFile:
      # Load parameters from file of previous body
      iniParser.read_file(prevBodyFile)

      # Extract mass of previous body
      prevBodyMass = float(iniParser['InertiaProperties']['rigidBodyMass_kg'])

    # Open body i-i parameter file
    with open(currBodDir, 'r') as currBodyFile:
      iniParser.read_file(currBodyFile)

      # Extract mass of current body
      currBodyMass = float(iniParser['InertiaProperties']['rigidBodyMass_kg'])

    # Find the position and velocity of curr body with respect to prev body
    positionCurrBodyRelToPrevBody_km, velocityCurrBodyRelToPrevBody_km = (
        keplarianToCartesian(prevBodyMass,
                             currBodyMass,
                             semiMajorAxis_km,
                             eccentricity,
                             inclinateion_deg * DEG_TO_RAD,
                             argumentOfPerigee_deg * DEG_TO_RAD,
                             raans_deg * DEG_TO_RAD,
                             timeSincePeriapsis_s))

    # Append the posittion and velcoity to respective lists
    bodyPositionList.append(np.add(positionCurrBodyRelToPrevBody_km,
                                   accumlatedTranslation_km))
    bodyVelocityList.append(np.add(velocityCurrBodyRelToPrevBody_km,
                                   accumlatedVelocity_kms))

    # Add current position and velcoity to respective accumulated vectors
    accumlatedTranslation_km = np.add(accumlatedTranslation_km,
                                      positionCurrBodyRelToPrevBody_km)
    accumlatedVelocity_kms = np.add(accumlatedVelocity_kms,
                                    velocityCurrBodyRelToPrevBody_km)

  # Find the main body of interests position and velocity
  mainBodyPosition_km = bodyPositionList[mainBody_in]
  mainBodyVelocity_kms = bodyVelocityList[mainBody_in]

  # Iterate through all the bodies and shift there values
  for i in range(0, parameters['nBodies']):
    bodyPositionList[i] -= mainBodyPosition_km
    bodyVelocityList[i] -= mainBodyVelocity_kms

  # Save the bodies positions and velocities
  for i, (bodyPosition_km, bodyVelocity_kms) in enumerate(zip(bodyPositionList, bodyVelocityList)):
    # Get direcotry to ini config file to save parameters
    iniConfigFile = configFile_in.parent / f'{parameters[f'body{i}']}.ini'

    # Update the parameters in the ini file
    saveSatelliteState(bodyPosition_km, bodyVelocity_kms, iniConfigFile)


if __name__ == '__main__':
  parser = argparse.ArgumentParser(
      prog='satellitePreProcessing',
      description=('This script will take keplarian parameters and use them to '
                   'update the cartesian state of the satellite.')
  )

  # Add argument to find yaml file with keplarian elements
  parser.add_argument('configFile', type=Path,
                      help=('Directory to yaml file which contains keplarian '
                            'elements of the orbit to model'))

  # Add argument to find yaml file with keplarian elements
  parser.add_argument('-b', '--mainBody', type=int,
                      help=('Integer to represent which body should be '
                            'consdiered the main body. Indexing starts at 0'),
                      required=False,
                      default=0)

  # Parse arguments
  args = parser.parse_args()

  # Run pre-processibng
  satellitePreProcessing(args.configFile, args.mainBody)

  # position = []
  # time = np.linspace(0, 100000000000, 10000)

  # for t in time:
  #   position_tmp, _ = keplarianToCartesian(
  #       1000000000000, 100, 1000, 0.7, 40, 20, 10, t)

  #   position.append(position_tmp.tolist())

  # position = np.array(position)
  # x = position[:, 0]
  # y = position[:, 1]
  # z = position[:, 2]

  # fig = go.Figure(data=go.Scatter3d(
  #     x=x, y=y, z=z
  # ))

  # fig.write_html("c:\\Users\\jason\\Desktop\\Projects\\test.html")
