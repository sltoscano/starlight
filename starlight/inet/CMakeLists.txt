
# Define the inet sources.
set(INET_SRCS
    inet.h
    inet.cpp
    inet-win32.cpp
    inet-posix.cpp
)

add_library(inet
    ${INET_SRCS}
)

