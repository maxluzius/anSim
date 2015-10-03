#
# Try to find GLFW3 library and include path.
# Once done this will define
#
# GLFW3_FOUND
# GLFW3_INCLUDE_PATH
# GLFW3_LIBRARY
# 

set(GLFW3_ROOT_ENV $ENV{GLFW3_ROOT})

IF(APPLE)
    set(GLFW3_ROOT_ENV $ENV{CVK_DEPENDENCIES_OSX}/glfw/)
ENDIF(APPLE)

IF (MINGW)
    FIND_PATH( GLFW3_INCLUDE_PATH GLFW/glfw3.h
        ${GLFW3_ROOT_ENV}/include
    )

    FIND_LIBRARY( GLFW3_LIBRARY
        NAMES glfw3
        PATHS
        ${GLFW3_ROOT_ENV}/lib-mingw
    )

ELSEIF (MSVC)
    FIND_PATH( GLFW3_INCLUDE_PATH GLFW/glfw3.h
        ${GLFW3_ROOT_ENV}/include
    )

    IF (MSVC10)
        FIND_LIBRARY( GLFW3_LIBRARY
            NAMES glfw3
            PATHS
            ${GLFW3_ROOT_ENV}/lib-msvc100
        )
    ELSE()
        FIND_LIBRARY( GLFW3_LIBRARY
            NAMES glfw3
            PATHS
            ${GLFW3_ROOT_ENV}/lib-msvc110
        )
    ENDIF ()
ELSEIF(APPLE)

    FIND_PATH(GLFW3_INCLUDE_PATH GLFW/glfw3.h DOC "Path to GLFW include directory."
	HINTS ${GLFW3_ROOT_ENV}/include
	PATHS ${GLFW3_ROOT_ENV}/include
    )
    
    FIND_LIBRARY( GLFW3_LIBRARY
        NAMES libglfw3.a glfw
        PATHS ${GLFW3_ROOT_ENV}/lib
    )

ELSE()
	FIND_PATH(GLFW3_INCLUDE_PATH GLFW/glfw3.h)
	FIND_LIBRARY(GLFW3_LIBRARY
        NAMES glfw3 glfw
	PATH_SUFFIXES dynamic) 
ENDIF ()



SET(GLFW3_FOUND "NO")
IF (GLFW3_INCLUDE_PATH AND GLFW3_LIBRARY)
	SET(GLFW3_LIBRARIES ${GLFW3_LIBRARY})
	SET(GLFW3_FOUND "YES")
    message("EXTERNAL LIBRARY 'GLFW3' FOUND")
ELSE()
    message("ERROR: EXTERNAL LIBRARY 'GLFW3' NOT FOUND")
ENDIF (GLFW3_INCLUDE_PATH AND GLFW3_LIBRARY)
