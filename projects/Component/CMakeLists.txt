#--------------------------------------------------------------------------
# S0012E_Group_Engine project
#--------------------------------------------------------------------------

ADD_LIBRARY(
    Component
    CameraComp.cc
    CameraComp.h
    Component.h
    CameraComponent.h
    )

TARGET_LINK_LIBRARIES(Component core render)
ADD_DEPENDENCIES(Component core render)