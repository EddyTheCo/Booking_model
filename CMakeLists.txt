cmake_minimum_required(VERSION 3.16)
project(DLockers VERSION 0.1 LANGUAGES CXX)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Quick)

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
	"/esthervtech.com/imports"
	OUTPUT_TARGETS out_targets_var
	IMPORTS MyDesigns
        IMPORT_PATH
	${CMAKE_BINARY_DIR}/_deps/mydesigns-build
	OUTPUT_DIRECTORY
	${CMAKE_CURRENT_BINARY_DIR}/booking_model
	)

target_link_libraries(booking_model PUBLIC Qt6::Gui Qt6::Quick)

target_include_directories(booking_model PUBLIC  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	"$<INSTALL_INTERFACE:include>")

include(FetchContent)

FetchContent_Declare(
    MyDesigns
    GIT_REPOSITORY git@github.com:EddyTheCo/MyDesigns.git
    GIT_TAG main
)
FetchContent_MakeAvailable(MyDesigns)

FetchContent_Declare(
	booking
	GIT_REPOSITORY git@github.com:EddyTheCo/booking.git
	GIT_TAG main
	)
FetchContent_MakeAvailable(booking)

target_link_libraries(booking_model PUBLIC MyDesigns booking)

target_compile_definitions(booking_model
	PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

install(TARGETS booking_model ${out_targets_var} EXPORT booking_modelTargets DESTINATION bin )
install(DIRECTORY include/ DESTINATION include/)

install(EXPORT booking_modelTargets
	FILE booking_modelTargets.cmake
	DESTINATION lib/cmake/booking_model
	)
include(CMakePackageConfigHelpers)
# generate the config file that is includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/booking_modelConfig.cmake"
	INSTALL_DESTINATION "lib/cmake/booking_model"
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
	)
write_basic_package_version_file(
	"${CMAKE_CURRENT_BINARY_DIR}/booking_modelConfigVersion.cmake"
	VERSION "0.1.1.0"
	COMPATIBILITY AnyNewerVersion
	)
install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/booking_modelConfig.cmake
	${CMAKE_CURRENT_BINARY_DIR}/booking_modelConfigVersion.cmake
	DESTINATION lib/cmake/booking_model
	)
export(EXPORT booking_modelTargets
	FILE "${CMAKE_CURRENT_BINARY_DIR}/booking_modelTargets.cmake"
	)
list(APPEND QML_IMPORT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/qml ${CMAKE_CURRENT_BINARY_DIR}/)
set(QML_IMPORT_PATH ${QML_IMPORT_PATH} PARENT_SCOPE CACHE STRING "" FORCE)
message(STATUS "boutpublisherQML_IMPORT_PATH:${QML_IMPORT_PATH}")
