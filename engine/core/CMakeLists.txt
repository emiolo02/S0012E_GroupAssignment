#--------------------------------------------------------------------------
# core
#--------------------------------------------------------------------------

SET(files_core
	stb_image.h
	stb_image.cc
	app.h
	app.cc
	nlohmann/json.hpp
	math/mat4.h
	math/vec2.h
	math/vec3.h
	math/vec4.h)
SOURCE_GROUP("core" FILES ${files_core})
	
SET(files_pch ../config.h ../config.cc)
SOURCE_GROUP("pch" FILES ${files_pch})
ADD_LIBRARY(core STATIC ${files_core} ${files_pch})
TARGET_PCH(core ../)
ADD_DEPENDENCIES(core glew)
TARGET_LINK_LIBRARIES(core PUBLIC engine exts glew)
