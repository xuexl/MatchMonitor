﻿cmake_minimum_required(VERSION 3.5)

project(match LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})


add_executable(match
  main.cxx
  MainWindow.cxx
  MainWindow.h
  MainWindow.ui  

  QImageViewerWithAnchor.cxx
  QImageViewerWithAnchor.h  
  QImageViewer.cxx
  QImageViewer.h

  TemplateDialog.cxx
  TemplateDialog.h
  TemplateDialog.ui
  
  ImageLoader.cxx
  ImageLoader.h
)

target_link_libraries(match PRIVATE Qt5::Widgets ${OpenCV_LIBS})
