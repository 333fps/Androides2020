#
#	Androids 2020
#
#	Source files
#

set( sources_files
			"main.cpp"
			"Android.cpp"
			"AndroidDemo.cpp"
			"AssetManager.cpp"
			"CurrentLevel.cpp"
			"Game.cpp"
			"GameEngine.cpp"
			"Human.cpp"
			"HumanDemo.cpp"
			"InputManager.cpp"
			"Levels.cpp"
			"Map.cpp"
			"SplashScreen.cpp"
			"Sprite.cpp"
			"State.cpp"
			"StateDemo.cpp"
			"StateGameOver.cpp"
			"StateMachine.cpp"
			"StateMenu.cpp"
			"StatePlay.cpp"
			"StateSplashScreen.cpp"
			"Transition.cpp"
)

add_executable( ${PROJECT_NAME}
								${RC}
								${sources_files}
)

target_compile_options( ${PROJECT_NAME} PRIVATE $<$<COMPILE_LANGUAGE:CXX>:${CXX_COMPILE_FLAGS}> )

target_include_directories( ${PROJECT_NAME} PRIVATE "." )

if( UNIX )
	set_target_properties( ${PROJECT_NAME} PROPERTIES
								VERSION ${PROJECT_VERSION}
								SOVERSION ${PROJECT_VERSION_MAJOR} )
endif()

if( WIN32 )
		set( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup" )
		set_target_properties( ${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE )
endif()
