cmake \
-DCMAKE_FIND_ROOT_PATH="/opt/adtools" \
-DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY \
-DCMAKE_SYSTEM_NAME="AmigaOS" \
-DCMAKE_SYSTEM_PROCESSOR="PowerPC" \
-DCMAKE_C_COMPILER="ppc-amigaos-gcc" \
-DCMAKE_CXX_COMPILER="ppc-amigaos-g++" \
-DCMAKE_ASM_COMPILER="ppc-amigaos-as" \
-DCMAKE_MAKE_PROGRAM="make" \
-DCMAKE_CXX_FLAGS_INIT="-mcrt=newlib -athread=native" \
-DCMAKE_C_FLAGS_INIT="-mcrt=newlib -athread=native" \
-DCMAKE_EXE_LINKER_FLAGS="-use-dynld" \
-DUNIX=1 -DAMIGA=1 \
-DCMAKE_INSTALL_PREFIX="/qt6-amiga" \
-DQT_HOST_PATH="/usr/local/Qt-6.2.0" \
-DQT_QMAKE_TARGET_MKSPEC=amiga-g++ \
-DQT_FEATURE_dlopen=ON \
-DQT_FEATURE_thread=ON \
-DQT_FEATURE_network=ON \
-DQT_FEATURE_ssl=ON \
-DQT_FEATURE_openssl=ON \
-DQT_FEATURE_openssl_linked=ON \
-DQT_FEATURE_library=ON \
-DQT_FEATURE_glib=OFF \
../amiga-qt6

# cmake -DCMAKE_PREFIX_PATH="/qt6-amiga" \
# -DCMAKE_FIND_ROOT_PATH="/opt/adtools" \
# -DCMAKE_FIND_ROOT_PATH_MODE_INCLUDE=ONLY \
# -DCMAKE_FIND_ROOT_PATH_MODE_LIBRARY=ONLY \
# -DCMAKE_SYSTEM_NAME="AmigaOS" \
# -DCMAKE_SYSTEM_PROCESSOR="PowerPC" \
# -DCMAKE_C_COMPILER="ppc-amigaos-gcc" \
# -DCMAKE_CXX_COMPILER="ppc-amigaos-g++" \
# -DCMAKE_ASM_COMPILER="ppc-amigaos-as" \
# -DCMAKE_MAKE_PROGRAM="make" \
# -DCMAKE_CXX_FLAGS_INIT="-mcrt=newlib -athread=native -fpermissive" \
# -DCMAKE_C_FLAGS_INIT="-mcrt=newlib -athread=native" \
# -DCMAKE_CXX_STANDARD_LIBRARIES="-lunix -lauto" \
# -DUNIX=1 -DAMIGA=1 \
# -DCMAKE_INSTALL_PREFIX="/qt6-amiga" \
# -DQT_HOST_PATH="/usr/local/Qt-6.2.0" \
# -DQT_QMAKE_TARGET_MKSPEC=amiga-g++ \
# -DQT_FEATURE_thread=ON \
# -DQT_FEATURE_network=ON \
# -DQT_FEATURE_glib=OFF \
# -DQT_FEATURE_libudev=OFF \
# -DQT_FEATURE_evdev=OFF \
# -DQT_FEATURE_concurrent=ON \
# -DQT_FEATURE_sql=ON \
# -DQT_FEATURE_future=ON \
# -DQT_FEATURE_process=ON \
# -DQT_FEATURE_processenvironment=ON \
# -DQT_FEATURE_systemsemaphore=ON \
# -DQT_BUILD_TOOLS_WHEN_CROSSCOMPILING=OFF \
# -DCMAKE_EXE_LINKER_FLAGS="-use-dynld -athread=native" \
# ../amiga-qt6/

# cmake \
# -DCMAKE_PREFIX_PATH="/usr/local/Qt-6.2.0" \
# -DCMAKE_INSTALL_PREFIX="/usr/local/Qt-6.2.0" \
# ..