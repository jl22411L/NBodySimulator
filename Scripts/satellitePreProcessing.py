#!/bin/env/python

from pathlib import Path
from math import pi as PI
import numpy as np
import configparser
import argparse
import yaml

# [ref:https://downloads.rene-schwarz.com/download/M001-Keplerian_Orbit_Elements_to_Cartesian_State_Vectors.pdf]


# ----------------------------------------------------------------------------- #
# CONSTANTS
# ----------------------------------------------------------------------------- #

# Universal Gravitation Constant
UNIVERSAL_GRAVITATIONAL_CONSTANT_KM3KGS2 = 6.6743 * 10**-20

# Tolerance for pure quaternion
GMATH_QUATERNION_ZERO_TOLERANCE = 1 * 10**-10

# ----------------------------------------------------------------------------- #
# FUNCTION DEFINITION
# ----------------------------------------------------------------------------- #


def quaternionFrameRotation(quaternion_in: np.ndarray, vector_in: np.ndarray):
  """
  @details      Function which will perform a quaternion rotation on an input
                vector.

  @param[in]    quaternion_in
                Array containing quaternion with with the scalar element being
                the 4th element in array.

  @param[in]    vector_in
                Input vector which will be rotated.
  """

  # Find quaternion conjugate
  quaternionConj = quaternionConjugate(quaternion_in)

  # Make vector component a pure quaternion
  pureQuaternion = np.zeros(4)
  pureQuaternion[0] = vector_in[0]
  pureQuaternion[1] = vector_in[1]
  pureQuaternion[2] = vector_in[2]

  # Perform first multiplication
  intermediateQuaternion = quaternionMultiplication(
    pureQuaternion, quaternion_in)

  # Perform second multiplication
  pureQuaternionOutput = quaternionMultiplication(
    quaternionConj, intermediateQuaternion)

  # Check that output is a pure quaternion
  if pureQuaternionOutput[3] > GMATH_QUATERNION_ZERO_TOLERANCE:
    print('Tolerance of output pure quaternion is not met.')
    print(f'pureQuaternionOutput = {pureQuaternionOutput}')
    raise ValueError

  # Extract vector from pure quaternion
  outputVector_out = pureQuaternionOutput[0:3]

  return outputVector_out


def quaternionConjugate(quaternion_in: np.ndarray):
  """
  @details      Function which finds the quaternion conjugate.

  @param[in]    quaternion_in
                Input quaternion with 4th element being the scalar element.

  @return       quaternionConjugate_out
                Output quaternion conjugate of input quaternion.
  """

  # Find the conjugate of the quaternion
  quaternionConjugate_out = np.zeros(4)
  quaternionConjugate_out[0] = -quaternion_in[0]
  quaternionConjugate_out[1] = -quaternion_in[1]
  quaternionConjugate_out[2] = -quaternion_in[2]
  quaternionConjugate_out[3] = quaternion_in[3]

  return quaternionConjugate_out


def quaternionMultiplication(pQuaternion_in: np.ndarray, qQuaternion_in: np.ndarray):
  """
  @details      Function which performs quaternion multiplication of two
                elements. The format of the result is:
                outputQuaternion_out = p*q

  @param[in]    pQuaternion_in
                Input p quaternion

  @param[in]    qQuaternion_in
                Input q quaternion

  @return       outputQuaternion_out
                Output quaternion after the quaternion multiplication
  """

  # Create array for output quaternion
  outputQuaternion_out = np.zeros(4)

  # Extract elements of input quaternion
  xP = pQuaternion_in[0]
  yP = pQuaternion_in[1]
  zP = pQuaternion_in[2]
  sP = pQuaternion_in[3]
  xQ = qQuaternion_in[0]
  yQ = qQuaternion_in[1]
  zQ = qQuaternion_in[2]
  sQ = qQuaternion_in[3]

  # Perform quaternion multiplation
  outputQuaternion_out[0] = xP * sQ + yP * zQ - zP * yQ + sP * xQ
  outputQuaternion_out[1] = -xP * zQ + yP * sQ + zP * xQ + sP * yQ
  outputQuaternion_out[2] = xP * yQ - yP * xQ + zP * sQ + sP * zQ
  outputQuaternion_out[3] = -xP * xQ - yP * yQ - zP * zQ + sP * sQ

  return outputQuaternion_out


def keplarianToCartesian(massBody1_kg_in: float,
                         massBody2_kg_in: float,
                         semiMajorAxis_km_in: float,
                         eccentricity_in: float,
                         inclintaion_rad_in: float,
                         argOfPeriapsis_rad_in: float,
                         raans_rad_in: float,
                         timeSincePeriapsis_s_in: float,
                         simTime_s_in) -> tuple:
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

  @param[in]    simTime_s_in
                Current time of simulation.

  @return       (orbitalPositionRelFix_Bod1_km_out,
                orbitalVelocityRelFix_Bod1_km_out)
  """

  # Find change in time
  changeInTime_s = simTime_s_in - timeSincePeriapsis_s_in

  # Find standard gravitational parameters (mu)
  # https://en.wikipedia.org/wiki/Standard_gravitational_parameter
  gravitationalParameter_km3kg2s2 = (UNIVERSAL_GRAVITATIONAL_CONSTANT_KM3KGS2 *
                                     massBody1_kg_in +
                                     UNIVERSAL_GRAVITATIONAL_CONSTANT_KM3KGS2 *
                                     massBody2_kg_in)

  # Find time period of orbit
  orbitalTimePeriod_s = (2 * PI *
                         semiMajorAxis_km_in ** (3 / 2) /
                         np.sqrt(gravitationalParameter_km3kg2s2))

  # Find the time since periapsis
  while changeInTime_s > orbitalTimePeriod_s:
    # Keep subtracting orbital time period until time is less then a period
    changeInTime_s -= orbitalTimePeriod_s
  while changeInTime_s < 0:
    # Keep adding orbital time period until time greater than 0
    changeInTime_s += orbitalTimePeriod_s

  # Find the average angular rate of body 2
  averageAngularRate_rads = 2 * PI / orbitalTimePeriod_s

  # Find the mean anomonly
  meanAnomoly = averageAngularRate_rads * changeInTime_s

  # Find the eccentric anomoly
  eccentricAnomoly = findEccentricAnomoly(meanAnomoly, eccentricity_in)

  # Find the true anomoly
  trueAnomoly = 2 * np.arctan2(np.sqrt(1 + eccentricity_in) *
                               np.tan(eccentricAnomoly / 2),
                               np.sqrt(1 - eccentricity_in))

  # Find the position magnitude of body 2 with respect to body 1
  orbitalPositionMag_km = semiMajorAxis_km_in * (
    1 - eccentricity_in * np.cos(eccentricAnomoly))

  # Find the position vector of body 2 with respect to body 1 in the orbit frame
  orbitalPosition_Per_km = orbitalPositionMag_km * np.array([
      np.cos(trueAnomoly),
      np.sin(trueAnomoly),
      0
  ])

  # Find the velocity magnitude of the orbit
  orbitalVelocityMag_kms = (np.sqrt(
    gravitationalParameter_km3kg2s2 * semiMajorAxis_km_in) / orbitalPositionMag_km)

  # Find the velocity vector of body 2 with respect to body 1 in the orbit frame
  orbitalVelocity_Per_kms = orbitalVelocityMag_kms * np.array([
      -np.sin(eccentricAnomoly),
      np.sqrt(1 - eccentricity_in**2) * np.cos(eccentricAnomoly),
      0
  ])

  # Create dcm for rotation around z axis for raans
  zRaansRotationDcm = np.array([
      [np.cos(-raans_rad_in), np.sin(-raans_rad_in), 0],
      [-np.sin(-raans_rad_in), np.cos(-raans_rad_in), 0],
      [0, 0, 1]
  ])

  # Create dcm for rotation around x axis for inclination
  xInclinationDcm = np.array([
      [1, 0, 0],
      [0, np.cos(-inclintaion_rad_in), np.sin(-inclintaion_rad_in)],
      [0, -np.sin(-inclintaion_rad_in), np.cos(-inclintaion_rad_in)]
  ])

  # Create dcm for rotation around z axis for argument of periapsis
  zArgumentOfPeriapsisDcm = np.array([
      [np.cos(-argOfPeriapsis_rad_in), np.sin(-argOfPeriapsis_rad_in), 0],
      [-np.sin(-argOfPeriapsis_rad_in), np.cos(-argOfPeriapsis_rad_in), 0],
      [0, 0, 1]
  ])

  # Find rotation matrix from Perifocal frame to Bod1 frame
  perToBod1Dcm = (zRaansRotationDcm @
                  xInclinationDcm @
                  zArgumentOfPeriapsisDcm)

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
    tangentFuntcionOutput = (1 - eccentricity_in *
                             np.cos(eccentricAnomoly_rad_out))

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

  print(fileDir_in)

  with open(fileDir_in, 'r') as paramFile:
    # Initiate variable to keep track of file contents
    fileContent = ''

    # Read first line of file
    line = paramFile.readline()

    # Iterate through file until reaching end of file
    while line:
      # Check line represents initial position and if update to new position
      if line[0:27] == 'fixedFramePosition_m_Fix[0]':
        line = f'fixedFramePosition_m_Fix[0] = {initialPosition_km_in[0] * 1000}\n'
      elif line[0:27] == 'fixedFramePosition_m_Fix[1]':
        line = f'fixedFramePosition_m_Fix[1] = {initialPosition_km_in[1] * 1000}\n'
      elif line[0:27] == 'fixedFramePosition_m_Fix[2]':
        line = f'fixedFramePosition_m_Fix[2] = {initialPosition_km_in[2] * 1000}\n'

      # Check line represents initial velocity and if update to new velocity
      if line[0:28] == 'fixedFrameVelocity_ms_Fix[0]':
        line = (f'fixedFrameVelocity_ms_Fix[0] = '
                f'{initialVelocity_kms_in[0] * 1000}\n')
      elif line[0:28] == 'fixedFrameVelocity_ms_Fix[1]':
        line = (f'fixedFrameVelocity_ms_Fix[1] = '
                f'{initialVelocity_kms_in[1] * 1000}\n')
      elif line[0:28] == 'fixedFrameVelocity_ms_Fix[2]':
        line = (f'fixedFrameVelocity_ms_Fix[2] = '
                f'{initialVelocity_kms_in[2] * 1000}\n')

      # Add line to file content
      fileContent += line

      # Read next line
      line = paramFile.readline()

  # Write the updated file content
  with open(fileDir_in, 'w') as paramFile:
    paramFile.write(fileContent)


def satellitePreProcessing(configFile_in: Path):
  """
  @details      This function performs the pre processing to find the satellites
                initial conditions. It takes in a yaml file which has the
                parameters requried by the pre processing.

  @param[in]    configFile_in
                Path to yaml file which contains parameters for pre processing.

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
  accumlatedTranslation_Fix_km = np.zeros(3)
  accumlatedVelocity_Fix_kms = np.zeros(3)
  accumulatedQuaternion_FixToCurBod = np.zeros(4)
  accumulatedQuaternion_FixToCurBod[3] = 1.0

  # Initiate list to keep track of bodies positions
  bodyPositionList = [accumlatedTranslation_Fix_km]
  bodyVelocityList = [accumlatedVelocity_Fix_kms]

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

    # Find current time of simulation
    with open(parameterRootDir / 'SimulationParameters.ini', 'r') as simulationFile:
      iniParser.read_file(simulationFile)

    currentSimTime_s = float(iniParser['TimeParameters']['simTimeInitial'])

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
                             np.deg2rad(inclinateion_deg),
                             np.deg2rad(argumentOfPerigee_deg),
                             np.deg2rad(raans_deg),
                             timeSincePeriapsis_s,
                             currentSimTime_s))

    if i > 1:
      # Find quaternion from fix frame to body frame of previous body parameters
      quaternion_PrevBodyToCurBody = parameters[(f'keplarianElementsBody{
          i - 2}ToBody{i - 1}')][(f'quaternion_Body{i - 2}FrameToBody{i - 1}Frame')]
    else:
      quaternion_PrevBodyToCurBody = np.array([0.0, 0.0, 0.0, 1.0])

    # Find accumulated quaternion
    accumulatedQuaternion_FixToCurBod = quaternionMultiplication(
      quaternion_PrevBodyToCurBody, accumulatedQuaternion_FixToCurBod)

    # Find the accumulated quaternion from the current body to the fix frame
    accumulatedQuaternion_CurBodToFix = quaternionConjugate(
      accumulatedQuaternion_FixToCurBod)

    # Rotate vectors by quaternion so that they are in fix frame
    positionCurrBodyRelToPrevBody_Fix_km = quaternionFrameRotation(
      accumulatedQuaternion_CurBodToFix, positionCurrBodyRelToPrevBody_km)
    velocityCurrBodyRelToPrevBody_Fix_km = quaternionFrameRotation(
      accumulatedQuaternion_CurBodToFix, velocityCurrBodyRelToPrevBody_km)

    # Append the posittion and velcoity to respective lists
    bodyPositionList.append(np.add(positionCurrBodyRelToPrevBody_Fix_km,
                                   accumlatedTranslation_Fix_km))
    bodyVelocityList.append(np.add(velocityCurrBodyRelToPrevBody_Fix_km,
                                   accumlatedVelocity_Fix_kms))

    # Add current position and velcoity to respective accumulated vectors
    accumlatedTranslation_Fix_km = np.add(accumlatedTranslation_Fix_km,
                                          positionCurrBodyRelToPrevBody_Fix_km)
    accumlatedVelocity_Fix_kms = np.add(accumlatedVelocity_Fix_kms,
                                        velocityCurrBodyRelToPrevBody_Fix_km)

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

  # Parse arguments
  args = parser.parse_args()

  # Run pre-processibng
  satellitePreProcessing(args.configFile)
