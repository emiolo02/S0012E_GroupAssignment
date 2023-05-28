#--------------------------------------------------------------------------
# S0012E_Group_Engine project
#--------------------------------------------------------------------------

ADD_LIBRARY(
    World
    Dummy.cc
    Scene.h
    SpawnGen.h
    ResourceManager.h
    ResourceManager.cc
)

TARGET_LINK_LIBRARIES(World core render)
ADD_DEPENDENCIES(World core render)