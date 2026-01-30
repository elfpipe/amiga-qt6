# Cross mode + compilers
set(CMAKE_SYSTEM_NAME AmigaOS)
set(CMAKE_SYSTEM_PROCESSOR PowerPC)
set(CMAKE_C_COMPILER   ppc-amigaos-gcc)
set(CMAKE_CXX_COMPILER ppc-amigaos-g++)
set(CMAKE_ASM_COMPILER ppc-amigaos-as)
# set(CMAKE_MAKE_PROGRAM /usr/bin/ninja)
set(CLIB4_SYSROOT "/opt/ppc-amigaos/ppc-amigaos/SDK")     # <— adjust

# Only search the sysroot for headers/libs/packages
set(CMAKE_FIND_ROOT_PATH "${CLIB4_SYSROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)   # host tools from host
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# Try-compile shouldn’t try to run target binaries
# set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Amiga C runtime (be consistent)
set(CMAKE_C_FLAGS_INIT   "-mcrt=clib4 -athread=native")
set(CMAKE_CXX_FLAGS_INIT "-mcrt=clib4 -athread=native")
set(CMAKE_EXE_LINKER_FLAGS "-use-dynld -mcrt=clib4 -athread=native")

set(UNIX 1)
set(AMIGA 1)

# Prefixes CMake will scan inside the sysroot
list(APPEND CMAKE_PREFIX_PATH
  "${CLIB4_SYSROOT}/clib4"
  "${CLIB4_SYSROOT}/local/clib4"
)

list(APPEND CMAKE_LIBRARY_PATH
  "${CLIB4_SYSROOT}/clib4/lib"
  "${CLIB4_SYSROOT}/local/clib4/lib"
)
list(APPEND CMAKE_INCLUDE_PATH
  "${CLIB4_SYSROOT}/clib4/include"
  "${CLIB4_SYSROOT}/local/clib4/include"
)