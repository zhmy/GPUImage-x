cmake_minimum_required(VERSION 3.4.1)

add_library( GPUImage-x-vulkan
             SHARED
             src/main/cpp/testVulkan.cpp
             src/main/cpp/testVulkanJNI.cpp
             src/main/cpp/vulkan_wrapper/vulkan_wrapper.cpp
             )

find_library( log-lib
              log )

target_link_libraries( GPUImage-x-vulkan
                        android
                       ${log-lib}
                       GLESv2
                       jnigraphics )

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
if(COMPILER_SUPPORTS_CXX11)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11   -Werror -DVK_USE_PLATFORM_ANDROID_KHR")
elseif(COMPILER_SUPPORTS_CXX0X)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x   -Werror -DVK_USE_PLATFORM_ANDROID_KHR")
else()
     message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti")