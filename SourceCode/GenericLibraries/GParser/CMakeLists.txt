add_library(GParser
  PrivateFunctions/GParser_clearBuffers.c
  PrivateFunctions/GParser_comment.c
  PrivateFunctions/GParser_findNumberOfSections.c
  PrivateFunctions/GParser_loadDictionary.c
  PrivateFunctions/GParser_loadingKey.c
  PrivateFunctions/GParser_loadingSection.c
  PrivateFunctions/GParser_loadingStringValue.c
  PrivateFunctions/GParser_loadingValue.c
  PrivateFunctions/GParser_waitingEquals.c
  PrivateFunctions/GParser_waitingForCommand.c
  PrivateFunctions/GParser_waitingForNewLine.c
  PrivateFunctions/GParser_waitingValue.c
  PublicFunctions/GParser_loadParams.c
)

