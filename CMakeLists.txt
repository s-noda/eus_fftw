project(eus_fftw)

cmake_minimum_required(VERSION 2.4.6)

find_package(catkin COMPONENTS cmake_modules)
find_package(Eigen REQUIRED)

find_path (FFTW_INCLUDES fftw3.h)
find_library (FFTW_LIBRARIES NAMES fftw3)

find_path (SoundTouch_INCLUDES soundtouch/SoundTouch.h /usr/local/include /usr/include)
find_library (SoundTouch_LIBRARIES NAMES SoundTouch)

include_directories(${Eigen_INCLUDE_DIRS})
include_directories(${EIGEN_INCLUDE_DIRS})
include_directories(${FFTW_INCLUDES})
include_directories(${SoundTouch_INCLUDES})

## include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

catkin_package()

add_executable(eus_fftw_test src/eus_fftw_test.c)
TARGET_LINK_LIBRARIES(eus_fftw_test ${FFTW_LIBRARIES})

add_executable(eus_soundtouch_test src/eus_soundtouch_test.cpp)
TARGET_LINK_LIBRARIES(eus_soundtouch_test ${SoundTouch_LIBRARIES})

add_library(eus_fftw SHARED src/eus_fftw_lib.cpp)
TARGET_LINK_LIBRARIES(eus_fftw ${FFTW_LIBRARIES})

