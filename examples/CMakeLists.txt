include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../..)

macro(add_int_example name)
	file(GLOB src ${name}/*.hpp ${name}/*.cpp)
	add_executable(rll.examples.${name} ${src})
	target_link_libraries(rll.examples.${name} rll.int)
	set_target_properties(rll.examples.${name} PROPERTIES COMPILE_DEFINITIONS "RLL_INT")
endmacro(add_int_example)

macro(add_double_example name)
	file(GLOB src ${name}/*.hpp ${name}/*.cpp)
	add_executable(rll.examples.${name} ${src})
	target_link_libraries(rll.examples.${name} rll.double)
	set_target_properties(rll.examples.${name} PROPERTIES COMPILE_DEFINITIONS "RLL_DOUBLE")
endmacro(add_double_example)

add_double_example(cart_pole_balancing)
add_int_example(grid_world_action)
add_int_example(grid_world_state)
add_int_example(tic_tac_toe)
add_int_example(tic_tac_toe_action)
add_int_example(crosses_and_crosses)
