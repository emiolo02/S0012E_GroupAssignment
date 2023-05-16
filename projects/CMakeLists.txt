#--------------------------------------------------------------------------
# S0012E_Group_Engine project
#--------------------------------------------------------------------------

PROJECT(S0012E_Group_Engine)

ADD_SUBDIRECTORY(Component)
ADD_SUBDIRECTORY(Gameobject)
ADD_SUBDIRECTORY(Input)
ADD_SUBDIRECTORY(Light)
ADD_SUBDIRECTORY(Resource)
ADD_SUBDIRECTORY(World)

FILE(GLOB root_headers *.h)
FILE(GLOB root_sources *.cc)
FILE(GLOB root_shaders *.glsl)

SET(files_example ${root_headers} ${root_sources} ${root_shaders})
SOURCE_GROUP("S0012E_Group_Engine" FILES ${files_example})


ADD_EXECUTABLE(S0012E_Group_Engine ${files_example})
TARGET_LINK_LIBRARIES(S0012E_Group_Engine core render Component Gameobject Input Light Resource World  )
ADD_DEPENDENCIES(S0012E_Group_Engine core render)

if (MSVC)
	set_property(TARGET S0012E_Group_Engine PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif()