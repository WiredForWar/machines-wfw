
set(DEFAULT_USE_STANDALONE_LAYOUT TRUE)
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(DEFAULT_USE_STANDALONE_LAYOUT DEV_BUILD)
endif()