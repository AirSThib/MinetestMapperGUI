cmake_minimum_required(VERSION 3.10)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(USE_FOLDERS ON)
include(getGitVersion)

project(MinetestMapperGUI
	VERSION ${git_version_major}.${git_version_minor}.${git_version_patch}.${git_commits_since_last_tag}
	DESCRIPTION "Graphical userinterface for Minetestmapper"
	LANGUAGES CXX)

message(STATUS "Version: ${PROJECT_VERSION}.")

if(MSVC_VERSION GREATER_EQUAL 1900)
	# MSVC does not support c++ 11 but c++ 14
	set(CMAKE_CXX_STANDARD 14)
else()
	set(CMAKE_CXX_STANDARD 11)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
	main.cpp
	mainwindow.cpp
	colorlineedit.cpp
	geometry.cpp
	geometrywidget.cpp
	configdialog.cpp
	makecolors.cpp
	drawmapfigure.cpp
	drawmapfiguretablemodel.cpp
	figuredelegate.cpp
	minetestmapperexe.cpp
	colorstxtwizard.cpp
	translator.cpp
)

set(HEADERS
	mainwindow.h
	colorlineedit.h
	geometry.h
	geometrywidget.h
	configdialog.h
	makecolors.h
	drawmapfigure.h
	drawmapfiguretablemodel.h
	figuredelegate.h
	minetestmapperexe.h
	colorstxtwizard.h
	translator.h
)

set(FORMS
	mainwindow.ui
	geometrywidget.ui
	configdialog.ui
)

set(RESOURCES
	minetestmappergui.qrc
)

set(TRANSLATIONS
	translations/gui_de.ts
	translations/gui_en.ts
)

if(${git_commits_since_last_tag} EQUAL 0)
	set (PRERELEASE 0)
else()
	set (PRERELEASE 1)
endif()

set(BUILD_BRANCH ${git_current_branch})
if(BUILD_BRANCH STREQUAL "master")
	set (SPECIALBUILD 0)
else()
	set (SPECIALBUILD 1)
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

configure_file(MinetestMapperGui.in.rc MinetestMapperGui.rc)

source_group("UI Files" FILES ${FORMS})
find_package(Qt5LinguistTools REQUIRED)
set_source_files_properties(${TRANSLATIONS} PROPERTIES OUTPUT_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/translations/")
qt5_create_translation(QM_FILES ${CMAKE_CURRENT_SOURCE_DIR} ${TRANSLATIONS})
add_executable(MinetestMapperGUI ${SOURCES} ${HEADERS} ${FORMS} ${RESOURCES} ${QM_FILES} ${CMAKE_CURRENT_BINARY_DIR}/MinetestMapperGui.rc)

find_package(Qt5 COMPONENTS Core Gui Widgets)

target_link_libraries(MinetestMapperGUI Qt5::Core Qt5::Gui Qt5::Widgets)
if(WIN32)
	find_package(Qt5WinExtras CONFIG REQUIRED)
	target_link_libraries(MinetestMapperGUI Qt5::WinExtras)
	# Get rid of the console window
	set_target_properties(MinetestMapperGUI PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

target_compile_definitions(MinetestMapperGUI PRIVATE GIT_VERSION="${PROJECT_VERSION}")

if(WIN32)
	# Get the location of the qmake exe
	get_target_property(qmake_executable Qt5::qmake IMPORTED_LOCATION)
	# Get the dir of it
	get_filename_component(qt_bin_dir "${qmake_executable}" DIRECTORY)
	message(STATUS "qt_bin_dir: ${qt_bin_dir}")
	find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${qt_bin_dir}")
	message(STATUS "WINDEPLOYQT_EXECUTABLE: ${WINDEPLOYQT_EXECUTABLE}")
	add_custom_command(TARGET MinetestMapperGUI POST_BUILD
		COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:MinetestMapperGUI>
			--dir "${CMAKE_CURRENT_BINARY_DIR}"
			--libdir $<TARGET_FILE_DIR:MinetestMapperGUI>
			--plugindir $<TARGET_FILE_DIR:MinetestMapperGUI>
			--no-compiler-runtime
			--no-opengl-sw
			--no-angle
		WORKING_DIRECTORY ${qt_bin_dir}
		COMMENT "Running windeployqt..."
		)

	configure_file(mtmapperenv.bat mtmapperenv.bat COPYONLY)
endif()

# Installation
###############################################################################

set(INSTALL_RUNTIME_DIR "bin")
if(WIN32)
	set(INSTALL_RUNTIME_DIR ".")
endif()


set(CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION ${INSTALL_RUNTIME_DIR})
include(InstallRequiredSystemLibraries)

#set(CPACK_PACKAGE_EXECUTABLES MinetestMapperGUI "Minetest Mapper GUI")

install(TARGETS MinetestMapperGUI
	RUNTIME DESTINATION ${INSTALL_RUNTIME_DIR}
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/translations/
	DESTINATION "translations"
	FILES_MATCHING PATTERN "*.qm"
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/translations/
	DESTINATION "translations"
	FILES_MATCHING PATTERN "*.png"
)

if(WIN32)
	#copy required dlls to install dir
	install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Release/
			DESTINATION ${INSTALL_RUNTIME_DIR}
			CONFIGURATIONS Release
			FILES_MATCHING PATTERN "*.dll")
	install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/Debug/
			DESTINATION ${INSTALL_RUNTIME_DIR}
			CONFIGURATIONS Debug
			FILES_MATCHING PATTERN "*.dll")
	install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/RelWithDebInfo/
			DESTINATION ${INSTALL_RUNTIME_DIR}
			CONFIGURATIONS RelWithDebInfo
			FILES_MATCHING PATTERN "*.dll")
	install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/MinSizeRel/
			DESTINATION ${INSTALL_RUNTIME_DIR}
			CONFIGURATIONS RelWithDebInfo
			FILES_MATCHING PATTERN "*.dll")
elseif(UNIX)
	install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/images/icon.svg" DESTINATION "/usr/local/share/icons/hicolor/scalable/apps" RENAME "MinetestMapperGUI.svg")
	install(FILES "MinetestMapperGUI.desktop" DESTINATION "/usr/share/applications") 
endif()

include(CPack)
