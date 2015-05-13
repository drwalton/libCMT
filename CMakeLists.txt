include_directories(.)

add_library(libCMT
    CMT.cpp
)

add_executable(CMT
    main.cpp
)

target_link_libraries(CMT
    libCMT
    ${OpenCV_LIBRARIES}
)

