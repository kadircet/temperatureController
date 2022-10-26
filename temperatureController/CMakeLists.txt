CMAKE_MINIMUM_REQUIRED(VERSION 3.16)
 
PROJECT(Air_Conditioner_Test VERSION 0.0)

set(HDR
	machine.h
	fan_speed.h
	mock_fan_speed.h
	temperature_sensor.h
	mock_temperature_sensor.h
	temperature_controller.h
)

set(SRC
	temperature_sensor.cpp
	fan_speed.cpp
	temperature_controller.cpp
	temperature_controller_test.cc
)

if(MSVC)
    source_group( "Header Files" FILES ${HDR})
    source_group( "Source Files" FILES ${SRC})
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Air_Conditioner_Test ${SRC} ${HDR})

target_link_libraries(
  Air_Conditioner_Test 
  GTest::gtest_main
  GTest::gmock_main
)

include(GoogleTest)
gtest_discover_tests(Air_Conditioner_Test)