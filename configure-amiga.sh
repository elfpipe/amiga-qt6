cmake \
-DCMAKE_SYSTEM_NAME="Generic" \
-DCMAKE_SYSTEM_PROCESSOR="PowerPC" \
-DCMAKE_C_COMPILER="ppc-amigaos-gcc" \
-DCMAKE_CXX_COMPILER="ppc-amigaos-g++" \
-DCMAKE_ASM_COMPILER="ppc-amigaos-as" \
-DCMAKE_MAKE_PROGRAM="make" \
-DCMAKE_CXX_FLAGS_INIT="-mcrt=newlib -athread=native" \
-DCMAKE_C_FLAGS_INIT="-mcrt=newlib" \
-DUNIX=1 \
-DCMAKE_INSTALL_PREFIX="/qt5-amiga" \
-DQT_HOST_PATH="/usr/local/Qt-6.2.0" \
-DQT_QMAKE_TARGET_MKSPEC=amiga-g++ \
-DQT_FEATURE_dlopen=OFF \
-DQT_FEATURE_thread=OFF \
-DQT_FEATURE_network=OFF \
../amiga-qt6