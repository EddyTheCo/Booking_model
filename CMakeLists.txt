cmake_minimum_required(VERSION 3.24)

include(${CMAKE_CURRENT_BINARY_DIR}/local_conf.cmake OPTIONAL)

include(FetchContent)
FetchContent_Declare(
	ccommon
	GIT_REPOSITORY https://github.com/EddyTheCo/Common.git
	GIT_TAG main
	)
FetchContent_MakeAvailable(ccommon)
version_from_git(
	LOG       OFF
	TIMESTAMP "%Y%m%d%H%M%S"
	)


project(Booking_model VERSION ${VERSION} LANGUAGES CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
include(GNUInstallDirs)

find_package(Qt6 COMPONENTS Core Gui Quick)

FetchContent_Declare(
	MyDesigns
	GIT_REPOSITORY https://github.com/EddyTheCo/MyDesigns.git
	GIT_TAG v0.3.1
	FIND_PACKAGE_ARGS 0.3 CONFIG
	)
FetchContent_MakeAvailable(MyDesigns)

FetchContent_Declare(
	booking
	GIT_REPOSITORY https://github.com/EddyTheCo/booking.git
	GIT_TAG v0.1.2
	FIND_PACKAGE_ARGS 0.1 CONFIG
	)
FetchContent_MakeAvailable(booking)

if(Qt6_FOUND)
	qt_standard_project_setup()
	qt6_add_qml_module(booking_model
		URI  booking_model
		VERSION 1.0
		SOURCES
		src/Hour_model.cpp src/Day_model.cpp  include/Day_model.hpp include/Hour_model.hpp
		QML_FILES
		qml/Day_swipe_view.qml
		qml/Dia_delegate.qml
		qml/Horario_delegate.qml
		qml/Horario_list_view.qml
		qml/window.qml
		RESOURCE_PREFIX
		"/esterVtech.com/imports"
		OUTPUT_TARGETS out_targets_var
		OUTPUT_DIRECTORY
		${CMAKE_BINARY_DIR}/booking_model
		IMPORT_PATH ${CMAKE_BINARY_DIR}
		)

	target_compile_definitions(booking_model PRIVATE WINDOWS_BMODE)
	target_link_libraries(booking_model PUBLIC Qt6::Gui Qt6::Quick)

	target_link_libraries(booking_model PUBLIC MyDesigns booking
		$<$<STREQUAL:$<TARGET_PROPERTY:MyDesigns,TYPE>,STATIC_LIBRARY>:MyDesignsplugin>
		)


	target_include_directories(booking_model PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/booking_model>")

	install(TARGETS booking_model booking_modelplugin ${out_targets_var}
		EXPORT booking_modelTargets
		DESTINATION ${CMAKE_INSTALL_LIBDIR}
		)
	install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/booking_model
		)
	install(DIRECTORY ${CMAKE_BINARY_DIR}/booking_model/
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/QMLPlugins/booking_model
		)
	install(EXPORT booking_modelTargets
		FILE booking_modelTargets.cmake
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/booking_model
		)
	include(CMakePackageConfigHelpers)

	configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
		"${CMAKE_CURRENT_BINARY_DIR}/booking_modelConfig.cmake"
		INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/booking_model
		)
	write_basic_package_version_file(
		"${CMAKE_CURRENT_BINARY_DIR}/booking_modelConfigVersion.cmake"
		VERSION ${VERSION}
		COMPATIBILITY SameMajorVersion
		)
	install(FILES
		${CMAKE_CURRENT_BINARY_DIR}/booking_modelConfig.cmake
		${CMAKE_CURRENT_BINARY_DIR}/booking_modelConfigVersion.cmake
		DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/booking_model
		)
	export(EXPORT booking_modelTargets
		FILE "${CMAKE_CURRENT_BINARY_DIR}/booking_modelTargets.cmake"
		)

	if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
		set(CPACK_PACKAGE_CONTACT "estervtech")
		include(CTest)
		set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-v${SEMVER}-${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_VERSION}-${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_CXX_COMPILER_ID}")
		include(CPack)
	endif()

endif(Qt6_FOUND)


if(BUILD_DOCS)
	get_target_property(build_docs cmake_build_docs SOURCES)
	include(${build_docs})
endif()

