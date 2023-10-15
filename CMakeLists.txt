cmake_minimum_required(VERSION 3.20)

project(Fractal VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
set(CMAKE_BUILD_TYPE Debug)
# set(GLFW_VULKAN_STATIC True)

find_package(glfw3 3.3 REQUIRED)
find_package(OpenCL REQUIRED)
# find_package(Vulkan REQUIRED)

# add_executable(${PROJECT_NAME} src/main.cpp src/window.cpp)
# add_executable(${PROJECT_NAME} src/main.cpp)
add_executable(${PROJECT_NAME} src/main.cpp)

# target_link_libraries(${PROJECT_NAME} Vulkan::Vulkan)
target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} OpenCL::OpenCL)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src")

# cmake_minimum_required(VERSION 3.0.0)
#
# project(firebreak VERSION 0.0.1 DESCRIPTION "Wrapper above the VulkanAPI")
#
# if(UNIX) if (APPLE) message("\nBuilding for Mac OS...\n") else()
# message("\nBuilding for Linux...\n") endif() elseif(WIN32) message("\nBuilding
# for Windows...\n") endif()
#
# include_directories(${PROJECT_SOURCE_DIR}/include $ENV{VULKAN_INCLUDE_PATH})
#
# set(GCC_COVERAGE_COMPILE_FLAGS "-std=c++14") set(GCC_COVERAGE_LINK_FLAGS "")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}
# ${GCC_COVERAGE_LINK_FLAGS}")
#
# set(${BINARY_DIR} "${CMAKE_BINARY_DIR}") set(${CMAKE_LIBRARY_OUTPUT_DIRECTORY}
# "${BINARY_DIR}/lib") set(${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
# "${BINARY_DIR}/lib") # For sample code in the future:
# set(${CMAKE_RUNTIME_OUTPUT_DIRECTORY} "${BINARY_DIR}/bin")
#
# set(SOURCE ${PROJECT_SOURCE_DIR}/source/fbClassAllocator.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassBuffer.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassBufferView.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassCache.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassCommandBuffer.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassCommandPool.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassComputePipeline.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassDevice.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassDeviceMemory.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassFence.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassGraphicsPipeline.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassImage.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassImageView.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassInstance.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassPipeline.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassQueue.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassRender.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassSemaphore.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassShader.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassSurface.cpp
# ${PROJECT_SOURCE_DIR}/source/fbClassSwapchain.cpp )
#
# add_library(${PROJECT_NAME} SHARED ${SOURCE})
#
# target_link_libraries(${PROJECT_NAME} $ENV{VULKAN_LIB_PATH}$ENV{VULKAN_LIB})
#
# #set_target_properties(firebreak PROPERTIES VERSION ${PROJECT_VERSION})
# #set_target_properties(firebreak PROPERTIES SOVERSION 1)
# #set_target_properties(firebreak PROPERTIES PUBLIC_HEADER
# include/firebreak.hpp) #target_include_directories(firebreak PRIVATE include)
# #target_include_directories(firebreak PRIVATE source) #include(GNUInstallDirs)
# #install(TARGETS firebreak LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
# PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
# #configure_file(firebreak.pc.in firebreak.pc @ONLY) #install(FILES
# ${CMAKE_BINARY_DIR}/firebreak.pc DESTINATION
# ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
