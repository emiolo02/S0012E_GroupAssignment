#--------------------------------------------------------------------------
# S0012E_Group_Engine project
#--------------------------------------------------------------------------

ADD_LIBRARY(
    Resource
    GraphicsNode.h
    GraphicsNode.cc
    TextureResource.h
    TextureResource.cc
    MeshResource.h
    MeshResource.cc
    ShaderResource.h
    ShaderResource.cc
    )

TARGET_LINK_LIBRARIES(Resource core render)
ADD_DEPENDENCIES(Resource core render)