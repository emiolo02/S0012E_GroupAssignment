#--------------------------------------------------------------------------
# S0012E_Group_Engine project
#--------------------------------------------------------------------------

ADD_LIBRARY(
    Physics
    Physics.h
    Physics.cc
)

TARGET_LINK_LIBRARIES(Physics core render)
ADD_DEPENDENCIES(Physics core render)