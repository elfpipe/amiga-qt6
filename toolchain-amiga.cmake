# this one is important
SET(CMAKE_SYSTEM_NAME AmigaOS)
#this one not so much
SET(CMAKE_SYSTEM_VERSION 1)

# specify the cross compiler
SET(CMAKE_C_COMPILER   ppc-amigaos-gcc)
SET(CMAKE_CXX_COMPILER ppc-amigaos-g++)
SET(CMAKE_MAKE_PROGRAM make)
SET(CMAKE_ASM_COMPILER ppc-amigaos-as)

#compiler flags
#SET(GCC_COVERAGE_COMPILE_FLAGS "-mcrt=newlib")
#SET(GCC_COVERAGE_LINK_FLAGS    "-mcrt=newlib")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${GCC_COVERAGE_LINK_FLAGS}")

# where is the target environment
SET(CMAKE_FIND_ROOT_PATH  /opt/adtools)

# search for programs in the build host directories
SET(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
# for libraries and headers in the target directories
SET(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
SET(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -athread=native")
