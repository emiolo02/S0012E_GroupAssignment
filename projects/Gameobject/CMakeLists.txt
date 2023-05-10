#--------------------------------------------------------------------------
# S0012E_Group_Engine project
#--------------------------------------------------------------------------

ADD_LIBRARY(
    Gameobject
)

TARGET_LINK_LIBRARIES(Gameobject core render)
ADD_DEPENDENCIES(Gameobject core render)