################################################ 
#this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
################################################



#Cgen_Start(CGEN_PROJECT_DIRECTORY "C:/Users/hadi/Documents/AERTOSProjects/commonAOs")

MATH(EXPR _arg_ONLY_CREATE_LIBRARY "${_arg_ONLY_CREATE_LIBRARY}+1")
include("C:/Users/hadi/Documents/AERTOSProjects/commonAOs/AEConfigProject.cmake")
MATH(EXPR _arg_ONLY_CREATE_LIBRARY "${_arg_ONLY_CREATE_LIBRARY}-1")

#CREATE_TARGET_INTEGRATIONEXE(NAME_OF_TARGET commonAOs
#LOCATION_OF_TARGET "C:/Users/hadi/Documents/AERTOSProjects/commonAOs"
#LibrariesToLinkTo AECoreLib 
#ONLY_CREATE_LIBRARY TRUE
#)  
#Cgen_End_Session()
  
#Cgen_Start(CGEN_PROJECT_DIRECTORY "C:/Users/hadi/Documents/AERTOSProjects/commonHalAOs")

MATH(EXPR _arg_ONLY_CREATE_LIBRARY "${_arg_ONLY_CREATE_LIBRARY}+1")
include("C:/Users/hadi/Documents/AERTOSProjects/commonHalAOs/AEConfigProject.cmake")
MATH(EXPR _arg_ONLY_CREATE_LIBRARY "${_arg_ONLY_CREATE_LIBRARY}-1")

#CREATE_TARGET_INTEGRATIONEXE(NAME_OF_TARGET commonHalAOs
#LOCATION_OF_TARGET "C:/Users/hadi/Documents/AERTOSProjects/commonHalAOs"
#LibrariesToLinkTo AECoreLib 
#ONLY_CREATE_LIBRARY TRUE
#)  
#Cgen_End_Session()
 

CREATE_TARGET_INTEGRATIONEXE(NAME_OF_TARGET ${INTEGRATION_TARGET_NAME}
LOCATION_OF_TARGET ${INTEGRATION_TARGET_DIRECTORY}
LibrariesToLinkTo AECoreLib commonAOs_lib commonHalAOs_lib
LIST_OF_TESTS defaultTest
) 