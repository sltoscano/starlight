# Some flags for freeglut.
add_definitions( -DFREEGLUT_EXPORTS -DFREEGLUT_STATIC -D_CRT_SECURE_NO_WARNINGS )

# Define the starlight sources.
set(STARLIGHT_SRCS
    main.cpp
    common.h
    communication.cpp
    communication.h
    dbg.cpp
    dbg.h
    glmain.cpp
    glmain.h
    glrender.cpp
    glrender.h
    render.h
    simulation.cpp
    simulation.h
)

set(ENTITIES_SRCS
    entities/asteroid.h
    entities/bullet.h
    entities/entity.cpp
    entities/entity.h
    entities/ship.h
)

# These are used to create visual studio or xcode folders.
source_group(entities FILES ${ENTITIES_SRCS})

include_directories (
    ${OPENGL_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

if(APPLE)
    # We are not using the Apple's framework version, but X11's
    include_directories( /usr/X11/include )
    link_directories( /usr/X11/lib )
    set (OPENGL_LIBRARIES GL GLU GLUT X11)
endif(APPLE)

add_executable(starlight
    ${STARLIGHT_SRCS}
    ${ENTITIES_SRCS}
)

target_link_libraries (
    starlight
    inet
    Box2D
    freeglut_static
    ${OPENGL_LIBRARIES}
)

