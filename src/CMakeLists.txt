INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

#Build the app
SET(Headers
    ./calc.hpp
    ./game.hpp
    ./map.hpp
    ./menu.hpp
    ./parameters.hpp
    ./player.hpp
    ./weapon.hpp
)

SET(Sources
    ./main.cpp
    ./calc.cpp
    ./game.cpp
    ./map.cpp
    ./menu.cpp
    #./parameters.cpp
    ./player.cpp
    ./weapon.cpp
)

ADD_EXECUTABLE(ArtilleryGame ${Sources} ${Headers})


#TARGET_INCLUDE_DIRECTORIES(ArtilleryGame PUBLIC 
#                            ${MPI_CXX_INCLUDE_PATH} 
#                          )


TARGET_LINK_LIBRARIES(ArtilleryGame PUBLIC
                        sfml-window
                        sfml-graphics
                        sfml-system)
