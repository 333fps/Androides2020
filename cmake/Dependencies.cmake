#
#	Androids 2020
#
#	Dependencies
#

add_dependencies(${PROJECT_NAME} "copy_resources_folder_${PROJECT_NAME}")

find_package( SFML COMPONENTS system window graphics CONFIG REQUIRED )
target_link_libraries( ${PROJECT_NAME} PRIVATE sfml-system sfml-graphics sfml-window sfml-audio )
