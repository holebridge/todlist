cmake_minimum_required(VERSION 3.0.0)
project(todolist VERSION 0.1.0)

find_package(SqliteOrm CONFIG REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core Widgets)
qt_standard_project_setup()
add_executable(todolist main.cpp view/edit_dialog.hpp)
target_link_libraries(todolist PRIVATE sqlite_orm::sqlite_orm Qt6::Core Qt6::Widgets)
# set_target_properties(todolist PROPERTIES WIN32_EXECUTABLE ON)
