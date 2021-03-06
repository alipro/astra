# add subdirs

include_directories(${ASTRA_INCLUDE_DIR})

set(CMAKE_DEBUG_POSTFIX "-d")

include(InstallPDB)

#set the rpath to look in the same directory for other Astra libs
if(ASTRA_OSX)
  set(CMAKE_INSTALL_RPATH "@loader_path")
elseif(ASTRA_UNIX)
  set(CMAKE_INSTALL_RPATH "$ORIGIN")
endif()

add_subdirectory(astra_core)
add_subdirectory(astra)
add_subdirectory(astra_core_api)
add_subdirectory(plugins)

if (NOT ASTRA_ANDROID AND ASTRA_STREAMPLAYER)
  add_subdirectory(common)
endif()

if (ASTRA_ANDROID)
  add_subdirectory(jni)
  add_subdirectory(android)
endif()

set (_projname "ProxyPreprocessor")

add_custom_target(${_projname} ALL
  COMMENT "=== LPP ==="
  COMMAND ${CLISP_EXECUTABLE} "lpp.cl" "../include"
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/lpp/"
  COMMAND ${CLISP_EXECUTABLE} "lpp.cl" "../src"
  WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/lpp/")

add_dependencies(astra_core ${_projname})
add_dependencies(astra ${_projname})
add_dependencies(astra_core_api ${_projname})
add_dependencies(openni_sensor ${_projname})

add_dependencies(${SDK_DEPENDENT_TARGET} astra_core)
add_dependencies(${SDK_DEPENDENT_TARGET} astra)
add_dependencies(${SDK_DEPENDENT_TARGET} astra_core_api)
add_dependencies(${SDK_DEPENDENT_TARGET} openni_sensor)

if (ASTRA_XS AND ASTRA_HAND)
  add_dependencies(${SDK_DEPENDENT_TARGET} orbbec_hand)
  add_dependencies(orbbec_hand ${_projname})
endif()

if (ASTRA_XS)
  add_dependencies(${SDK_DEPENDENT_TARGET} orbbec_xs)
  add_dependencies(orbbec_xs ${_projname})
endif()

if (ASTRA_SKELETON)
  add_dependencies(${SDK_DEPENDENT_TARGET} orbbec_skeleton)
  add_dependencies(orbbec_skeleton ${_projname})
endif()

if (NOT ASTRA_ANDROID)
  if (ASTRA_MOCK_DEVICE)
    add_dependencies(${SDK_DEPENDENT_TARGET} mock_sensor)
  endif()

  add_dependencies(${SDK_DEPENDENT_TARGET} copytoml_astra)

  if (ASTRA_HAND)
    add_dependencies(${SDK_DEPENDENT_TARGET} copytoml_hand)
  endif()

  if (ASTRA_STREAMPLAYER)
    add_dependencies(${SDK_DEPENDENT_TARGET} FrameSerialization)
  endif()
endif()
