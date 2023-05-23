#--------------------------------------------------------------------------
# S0012E_Group_Engine project
#--------------------------------------------------------------------------

ADD_LIBRARY(
    Gameobject
    GameObj.h
    Player.h
    Player.cc
    EnemyAI.h
    EnemyAI.cc
    StaticObj.h
    StaticObj.cc
    MapGen.h
    MapGen.cc
    MapTile.h
    MapTile.cc
    Camera.h
    Camera.cc
)

TARGET_LINK_LIBRARIES(Gameobject core render)
ADD_DEPENDENCIES(Gameobject core render)