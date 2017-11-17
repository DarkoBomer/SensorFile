# - Config file for the djiosdkcore package
# It defines the following variables
#  DJIOSDK_INCLUDE_DIRS - include directories for djiosdk
#  DJIOSDK_LIBRARIES    - libraries to link against

# Compute paths
get_filename_component(DJIOSDK_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
set(DJIOSDK_INCLUDE_DIRS "${DJIOSDK_CMAKE_DIR}/../../../include/djiosdk")

# Our library dependencies (contains definitions for IMPORTED targets)
include("${DJIOSDK_CMAKE_DIR}/djiosdkTargets.cmake")

# These are IMPORTED targets created by djiosdkTargets.cmake
set(DJIOSDK_LIBRARIES djiosdk-core)

