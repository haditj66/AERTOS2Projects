################################################ 
#this is an autogenerated file using cgen's macro2 command. Dont modify this file here unless it is in user sections 
################################################



#Cgen_Start(CGEN_PROJECT_DIRECTORY "C:/AERTOSProjects/commonAOs")

MATH(EXPR _arg_ONLY_CREATE_LIBRARY "${_arg_ONLY_CREATE_LIBRARY}+1")
include("C:/AERTOSProjects/commonAOs/AEConfigProject.cmake")
MATH(EXPR _arg_ONLY_CREATE_LIBRARY "${_arg_ONLY_CREATE_LIBRARY}-1")

#CREATE_TARGET_INTEGRATIONEXE(NAME_OF_TARGET commonAOs
#LOCATION_OF_TARGET "C:/AERTOSProjects/commonAOs"
#LibrariesToLinkTo AECoreLib 
#ONLY_CREATE_LIBRARY TRUE
#)  
#Cgen_End_Session()
 

CREATE_TARGET_INTEGRATIONEXE(NAME_OF_TARGET ${INTEGRATION_TARGET_NAME}
LOCATION_OF_TARGET ${INTEGRATION_TARGET_DIRECTORY}
LibrariesToLinkTo AECoreLib commonAOs_lib
LIST_OF_TESTS defaultTest
) 