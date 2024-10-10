target_compile_definitions(${PROJECT_NAME} PUBLIC QUARK_GRAPHICS)

include(${COMMON_LIBRARY_DIRECTORY}/glm.cmake)
include(${COMMON_LIBRARY_DIRECTORY}/glad.cmake)

glad_add_library(glad_gl_core_mx_33 REPRODUCIBLE MX API gl:core=3.3)

target_link_libraries(${PROJECT_NAME} PUBLIC
	glm::glm
	glad_gl_core_mx_33
)

add_modules(${PROJECT_NAME}
	src/module.ixx
	src/gl.ixx
	src/scene.ixx
	src/window.ixx
)
