include_directories(.)

add_library(libCMT
    CMT.cpp
)

target_link_libraries(libCMT
    tracker)

add_executable(CMT
    main.cpp
)

target_link_libraries(CMT
    libCMT
    tracker
    ${OpenCV_LIBRARIES}
)

