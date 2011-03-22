# Some flags for freeglut.
add_definitions( -DFREEGLUT_EXPORTS -DFREEGLUT_STATIC -D_CRT_SECURE_NO_WARNINGS )

# Define the starlight sources.
set(STARLIGHT_SRCS
    main.cpp
)

# These are used to create visual studio folders.
source_group(src FILES ${STARLIGHT_SRCS})

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
)

target_link_libraries (
    starlight
    Box2D
    freeglut_static
    ${OPENGL_LIBRARIES}
)

