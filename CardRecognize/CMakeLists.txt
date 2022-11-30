#<>cmake不同版本之间的兼容
# 该版本号应为胜任该模块编译的最小版本
cmake_minimum_required(VERSION 3.10)

#识别当前文件名，将当前文件夹名设置为项目名称
string(REGEX REPLACE ".*/\(.*\)" "\\1" CURDIR_NAME ${CMAKE_CURRENT_SOURCE_DIR})

project(${CURDIR_NAME} VERSION 0.1)

#设置子项目，假设所有库都位于同一层级，且具有相同的文件结构

SET(PATH_COM_REPO $ENV{PATH_COM_REPO})
SET(LD_LIBRARY_PATH $ENV{LD_LIBRARY_PATH})

find_package(OpenCV  REQUIRED
  opencv_core
  opencv_highgui
  )


# 位于<com_repo>/com_lib的库
set(LIST_COM_LIB
#  gtest
  )

# 位于<com_repo>/private_lib的库
set(LIST_PRIVATE_LIB
  )

# 位于<com_repo>/public_lib的库
set(LIST_PUBLIC_LIB
#  cppgc
opencv_basic
  )


# 编译选项
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )

# # 将当前文件文件夹下的所有cpp和.h文件添加到一个列表，编译动态库时将包含所有cpp
file(GLOB_RECURSE CPP_LIB "${CMAKE_CURRENT_SOURCE_DIR}/src/*")
file(GLOB_RECURSE H_LIB "${CMAKE_CURRENT_SOURCE_DIR}/include/*")
file(GLOB_RECURSE CONFIG_CMAKE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/*")


if(BUILD_SHARED_LIBS)
    #add_definitions(-DBUILD_SHARED_LIBS_ON)
add_definitions(-DBUILD_SHARED_LIBS_OFF)
else()
    add_definitions(-DBUILD_SHARED_LIBS_OFF)
endif()

#set(BUILD_SHARED_LIBS ON)

# 默认将编译的目标库设置为静态库
# 可用设置BUILD_SHARED_LIBS为ON/OFF控制编译成动态库或者静态库
# -DBUILD_SHARED_LIBS=OFF -DBUILD_SHARED_LIBS=ON \
# set(BUILD_SHARED_LIBS ON)
add_library(${PROJECT_NAME}
  ${CPP_LIB}
  ${H_LIB}
  )


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  )

#预设<com_repo>路径 使用cmake 时可以通过cmake . -DPATH_COM_REPO=<com_repo>进行自定义设置
SET(PATH_COM_REPO
  "/home/sxy/Work/com_repo/scripts/com_repo_init/../../"
  CACHE
  STRING
  "Some user-specified option")
SET(EXPORT_TO_CURRENT_PROJECT OFF CACHE BOOL "Some user-specified option")

if(EXPORT_TO_CURRENT_PROJECT)
    SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/export)
endif()

STRING(REGEX REPLACE ".+/(.+)\\.*" "\\1" COMPILER_SUFFIX ${CMAKE_C_COMPILER})

#将依赖的库添加到当前项目
FOREACH(MYSUBLIB ${LIST_COM_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/com_lib/${MYSUBLIB}/
    ${PATH_COM_REPO}/com_lib_out/${MYSUBLIB}_${COMPILER_SUFFIX}.out/)
endif()
ENDFOREACH(MYSUBLIB)

FOREACH(MYSUBLIB ${LIST_PRIVATE_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/private_lib/${MYSUBLIB}/
    ${PATH_COM_REPO}/private_lib_out/${MYSUBLIB}_${COMPILER_SUFFIX}.out/)
endif()
ENDFOREACH(MYSUBLIB)

FOREACH(MYSUBLIB ${LIST_PUBLIC_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/public_lib/${MYSUBLIB}/
    ${PATH_COM_REPO}/public_lib_out/${MYSUBLIB}_${COMPILER_SUFFIX}.out/)
endif()
ENDFOREACH(MYSUBLIB)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_SOURCE_DIR}/src
  )

#<>为什么有版本限制
if (DEFINED CMAKE_VERSION AND NOT "${CMAKE_VERSION}" VERSION_LESS "2.8.11")
  target_include_directories(${PROJECT_NAME}
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif()

#设置安装路径,输出头文件与库文件
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/  DESTINATION  ${CMAKE_BINARY_DIR}/include)

install(TARGETS ${PROJECT_NAME} DESTINATION  ${CMAKE_BINARY_DIR}/lib)

install(FILES ${CONFIG_CMAKE} DESTINATION  ${CMAKE_BINARY_DIR}/share)


# 本本项目链接相应的库
target_link_libraries(
  ${PROJECT_NAME}
  ${LIST_COM_LIB}
  ${LIST_PRIVATE_LIB}
  ${LIST_PUBLIC_LIB}
  )


## 这部分代码用于运行创建gtest测试程序
## 在可执行目录下生成一个可执行文件
#cxx_library(gtest_test "${cxx_strict}" gtest/main.cpp)
#target_link_libraries(gtest_test gtest ${PROJECT_NAME} -lgcov)
#cxx_executable(tpg_main gtest/tpg_main/ gtest_test)
##该步骤用于执行 需要运行make test后进行运行测试程序.Qt设置构建步骤后可以自动运行
## gtest若测试未通过,会停止并报错
#add_test(${PROJECT_NAME}_test tpg_main)
## 该语句用于设置测试程序的输出
## gtest可以不设置输出
##set_tests_properties(${PROJECT_NAME}_test PROPERTIES PASS_REGULAR_EXPRESSION "5")



#enable_testing()

set( CMAKE_BUILD_TYPE Debug )

#set(GTEST_LIB gtest gtest_main)
## 添加测试用例
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gtest/)

#set(GTEST_LIB gtest gtest_main)
#add_executable(gtest-toml
#  ${CMAKE_CURRENT_SOURCE_DIR}/gtest/tpg_main/tpg_main.cpp)
#target_link_libraries(gtest-toml ${PROJECT_NAME} gtest gtest_main)
#add_test(NAME gtest-toml COMMAND gtest-toml)


#add_executable(test_minus test/c/test_minus.cc)
#target_link_libraries(test_add math gtest gtest_main)
#target_link_libraries(test_minus math gtest gtest_main)

#add_test(NAME test_minus COMMAND test_minus)
