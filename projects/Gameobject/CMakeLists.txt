#--------------------------------------------------------------------------
# S0012E_Group_Engine project
#--------------------------------------------------------------------------

ADD_LIBRARY(
    Gameobject
    GameObj.h
    CameraObj
    PLayer.h
    Player.cc
)

TARGET_LINK_LIBRARIES(Gameobject core render)
ADD_DEPENDENCIES(Gameobject core render)