project( testOpenCV )
find_package( OpenCV REQUIRED )
add_executable( testOpenCV testOpenCV )
target_link_libraries( testOpenCV ${OpenCV_LIBS} )
