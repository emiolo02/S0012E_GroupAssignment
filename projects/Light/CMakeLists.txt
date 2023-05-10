#--------------------------------------------------------------------------
# S0012E_Group_Engine project
#--------------------------------------------------------------------------

ADD_LIBRARY(
    Light
    PointLight.h
    PointLight.cc
    Sun.h
    Sun.cc
)

TARGET_LINK_LIBRARIES(Light core render)
ADD_DEPENDENCIES(Light core render)