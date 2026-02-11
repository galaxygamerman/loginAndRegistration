cmake_minimum_required(VERSION 3.16)

project(loginAndRegistration VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Quick Sql)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(apploginAndRegistration
    main.cpp
)

qt_add_qml_module(apploginAndRegistration
    URI loginAndRegistration
    QML_FILES
        Main.qml
        QML_FILES LoginPage.qml
        QML_FILES RegisterPage.qml
        QML_FILES DashboardPage.qml
        SOURCES databasemanager.h databasemanager.cpp
        RESOURCES assets.qrc
        QML_FILES AuthStatusDialog.qml
        QML_FILES BackgroundImage.qml
        QML_FILES ReturnButton.qml
        QML_FILES BackgroundCard.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(apploginAndRegistration PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.apploginAndRegistration
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(apploginAndRegistration
    PRIVATE Qt6::Quick
    Qt6::Sql
)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/database")
add_custom_target(copy_database_files
    COMMAND ${CMAKE_COMMAND} -E copy_directory_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/database/"
        "${CMAKE_CURRENT_BINARY_DIR}/database/"
    COMMENT "Copying database files if different"
)
add_dependencies(apploginAndRegistration copy_database_files)

include(GNUInstallDirs)
install(TARGETS apploginAndRegistration
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
