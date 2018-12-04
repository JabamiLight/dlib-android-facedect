
cmake_minimum_required(VERSION 3.4.1)
set(PATH_TO_NATIVE ${PATH_TO_MEDIACORE}/src/main/cpp)
set(PATH_TO_PRE_BUILT ${PATH_TO_MEDIACORE}/libs/${ANDROID_ABI})

include_directories(BEFORE ${PATH_TO_MEDIACORE}/libs/include/)

file(GLOB  FFMPEG_DECODE_SOURCE "*.cpp")#包含当前目录的cpp文件
add_definitions(-DDLIB_PNG_SUPPORT)
add_library(opencv
        SHARED
        ${FFMPEG_DECODE_SOURCE}
        )


target_link_libraries(opencv
                    log
                    z
                    ${PATH_TO_PRE_BUILT}/libopencv_java3.so
                    ${PATH_TO_PRE_BUILT}/libdlib.so
                    )


