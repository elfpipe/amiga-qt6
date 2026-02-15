export PKG_CONFIG_PATH="/opt/ppc-amigaos/ppc-amigaos/SDK/local/clib4/lib/pkgconfig:/opt/ppc-amigaos/ppc-amigaos/SDK/clib4/lib/pkgconfig"
cmake \
-G "Unix Makefiles" \
-DCMAKE_TOOLCHAIN_FILE="/home/elfpipe2/code/amiga-qt6/toolchain-amigaos4-clib4.cmake" \
-DCMAKE_MAKE_PROGRAM=/usr/bin/make \
-DCMAKE_INSTALL_PREFIX="/qt6-amiga" \
-DQT_INSTALL_PREFIX="/qt6-amiga" \
-DQT_HOST_PATH="/usr/local/Qt-6.2.0" \
-DQT_QMAKE_TARGET_MKSPEC=amiga-g++ \
-DUNIX=1 -DAMIGA=1 \
-DQT_FEATURE_dlopen=ON \
-DQT_FEATURE_thread=ON \
-DQT_FEATURE_network=ON \
-DQT_FEATURE_ssl=ON \
-DQT_FEATURE_openssl=ON \
-DQT_FEATURE_openssl_linked=OFF \
-DQT_FEATURE_library=ON \
-DQT_FEATURE_concurrent=ON \
-DQT_FEATURE_sql=ON \
-DQT_FEATURE_future=ON \
-DQT_FEATURE_process=ON \
-DQT_FEATURE_processenvironment=ON \
-DQT_FEATURE_systemsemaphore=ON \
-DQT_FEATURE_brotli=ON \
-DQT_FEATURE_icu=ON \
-DQT_FEATURE_libudev=OFF \
-DQT_FEATURE_evdev=OFF \
-DQT_FEATURE_pcre2=ON -DQT_FEATURE_system_pcre2=ON \
-DQT_FEATURE_sql_odbc=OFF \
-DQT_FEATURE_system_sqlite=ON \
-DQT_FEATURE_qml_debug=OFF \
-DBUILD_SHARED_LIBS=OFF \
-DQT_BUILD_TOOLS_WHEN_CROSSCOMPILING=OFF \
..




#-DQT_BUILD_EXAMPLES=ON \
#/amiga-qt6
# -Wl,--verbose