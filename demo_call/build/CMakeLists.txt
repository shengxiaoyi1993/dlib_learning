#win cmake ../ -G "Unix Makefiles" -DCMAKE_PREFIX_PATH=/home/sxy/Software//opencv-3.4.1/ -DPATH_COM_REPO=${PATH_COM_REPO}
# Qt运行程序找不到opencv动态库，Qt -build environment 添加 LD_LIBRARY_PATH /home/sxy/Software//opencv-3.4.1/lib64/
# 执行cmake时添加编译选项，-DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows

cmake_policy(VERSION 3.6)
project(demo_vcpkg_dlib VERSION 0.1)
cmake_minimum_required(VERSION 3.6)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)  #编译.ui程序相关
#set(PKG_CONFIG_USE_CMAKE_PREFIX_PATH ON)
SET(PATH_COM_REPO "/home/sxy/Work/com_repo/scripts/com_repo_init/../../" CACHE STRING "Some user-specified option")
SET(PATH_COMPILER_SDX "" CACHE STRING "Some user-specified option")


#设置子项目，假设所有库都位于同一层级，且具有相同的文件结构



SET(PATH_COM_REPO $ENV{PATH_COM_REPO})
SET(LD_LIBRARY_PATH $ENV{LD_LIBRARY_PATH})
SET(CMAKE_MODULE_PATH $ENV{CMAKE_MODULE_PATH})

#find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_package(dlib CONFIG REQUIRED)


message("CMAKE_MODULE_PATH:" ${CMAKE_MODULE_PATH})
message("OpenCV_CONFIG_PATH:" ${OpenCV_CONFIG_PATH})
message("OpenCV_DIR:" ${OpenCV_DIR})

message("CMAKE_CXX_COMPILER:" ${CMAKE_CXX_COMPILER})

# 位于<com_repo>/com_lib的库
set(LIST_COM_LIB
  #  cjsonobject
  #  glog
  #  opencv_3_4_1
  )

# 位于<com_repo>/private_lib的库
set(LIST_PRIVATE_LIB
  #  encrypt
  )

# 位于<com_repo>/public_lib的库
set(LIST_PUBLIC_LIB
#  macro_glog
  #  uio
  #  msgchannel
  #  socket_channel
  #  toml
#  cppgc
  )





# 编译选项
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11" )
##编译输出路径
#set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}")
#set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

#预设<com_repo>路径 使用cmake 时可以通过cmake . -DPATH_COM_REPO=<com_repo>进行自定义设置
#SET(PATH_COM_REPO "/home/sxy/Work/com_repo/scripts/com_repo_init/../../" CACHE STRING "Some user-specified option")

#include(${CMAKE_CURRENT_SOURCE_DIR}/../../../cmake/common_define.cmake)

#包含文件，以便头文件能够被识别
# <>该处需要优化，可能具有风险
#include_directories(${PATH_COM_REPO})


#项目名称
#project (cv_image_convert)

#编译输出路径
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../../device/www/cgi-bin/)

#将依赖的库添加到当前项目
FOREACH(MYSUBLIB ${LIST_COM_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/com_lib/${MYSUBLIB}/ ${CMAKE_CURRENT_BINARY_DIR}/${MYSUBLIB}.out/)
endif()
ENDFOREACH(MYSUBLIB)

FOREACH(MYSUBLIB ${LIST_PRIVATE_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/private_lib/${MYSUBLIB}/ ${CMAKE_CURRENT_BINARY_DIR}/${MYSUBLIB}.out/)
endif()
ENDFOREACH(MYSUBLIB)

FOREACH(MYSUBLIB ${LIST_PUBLIC_LIB})
if(NOT TARGET ${MYSUBLIB})
  message("add_subdirectory ${MYSUBLIB}")
  add_subdirectory(${PATH_COM_REPO}/public_lib/${MYSUBLIB}/ ${CMAKE_CURRENT_BINARY_DIR}/${MYSUBLIB}.out/)
endif()
ENDFOREACH(MYSUBLIB)

#file(COPY ${CMAKE_SOURCE_DIR}/../resources/car.jpg DESTINATION image)

message("OpenCV_LIBS:" ${OpenCV_LIBS})

add_executable (${PROJECT_NAME}
#  ../src/main.cpp
#机器学习方法解决分配问题
#../src/asign_learning.cpp
# 借助输入输出流和dlib中的压缩/base编码组件进行编码
#../src/file_to_code_ex.cpp
#贝叶斯网络
#../src/bayes_net_from_disk_ex.cpp
#创建贝叶斯网络的工具 x
#../src/bayes_net_gui_ex.cpp
# 贝叶斯网络的简单例子
#../src/bayes_net_ex.cpp
# 显示图片/横向，纵向梯度的范例
#../src/image_ex.cpp
# 构造窗口和可移动对象的简单方法
#../src/gui_api_ex.cpp

# 使用管道进行线程间数据传输
#../src/pipe_ex_2.cpp
# 用桥来实现服务器和客户端，利用pipe管道传输数据结构
#../src/bridge_ex.cpp
# 介绍同步并行计算模型的简单实用，基于dlib::bsp
#../src/bsp_ex.cpp

# 演示一个命令行参数解析工具的使用，和文件压缩和解压缩功能
#../src/compress_stream_ex.cpp
# config文件读取工具 键值对，用{}分级
#../src/config_reader_ex.cpp
# 多类别分类器的训练和使用，基于二元分类（rbf）,向量机和多项式
#../src/multiclass_classification_ex.cpp

../src/custom_trainer_ex.cpp

  )

# 本项目链接相应的库
target_link_libraries(
  ${PROJECT_NAME}
  ${LIST_COM_LIB}
  ${LIST_PRIVATE_LIB}
  ${LIST_PUBLIC_LIB}
  )

target_link_libraries(${PROJECT_NAME} PUBLIC  dlib::dlib)


#set( CMAKE_BUILD_TYPE Release )
