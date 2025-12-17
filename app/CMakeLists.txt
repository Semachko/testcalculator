set(CMAKE_AUTOMOC ON)
set(QT_QML_GENERATE_QMLLS_INI ON)

add_executable(testcalculator WIN32 main.cpp gui.cpp)
find_package(Qt6 REQUIRED COMPONENTS Core Quick)
qt_standard_project_setup(REQUIRES 6.8)
target_include_directories(testcalculator 
    PUBLIC 
    include
    ../library/include
)
target_link_libraries(testcalculator PRIVATE
    Qt6::Quick
    Qt6::Core
    corecalculator
)

qt_add_qml_module(testcalculator
    URI Gui
    VERSION 1.0
    QML_FILES 
        Main.qml
)