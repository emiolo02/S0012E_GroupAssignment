#--------------------------------------------------------------------------
# S0012E_Group_Engine project
#--------------------------------------------------------------------------

ADD_LIBRARY(
    Input
    Input.h
    key_1.h
    key_1.cc
)

TARGET_LINK_LIBRARIES(Input core render)
ADD_DEPENDENCIES(Input core render)