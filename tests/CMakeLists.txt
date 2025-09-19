set(CMAKE_AUTOMOC ON)
enable_testing()

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Test Network)

add_executable(test_mainwindow
	test_mainwindow.cpp
	${CMAKE_SOURCE_DIR}/src/mainwindow.cpp
	${CMAKE_SOURCE_DIR}/src/datawidget.cpp
	${CMAKE_SOURCE_DIR}/src/animatedprogressbar.cpp
	${CMAKE_SOURCE_DIR}/src/graphwidget.cpp
	${CMAKE_SOURCE_DIR}/src/udpservice.cpp
	${CMAKE_SOURCE_DIR}/src/pages/dashboardpage.cpp
	${CMAKE_SOURCE_DIR}/src/pages/graphspage.cpp
	${CMAKE_SOURCE_DIR}/src/pages/settingspage.cpp
	${CMAKE_SOURCE_DIR}/src/pages/udpresponsepage.cpp
)
target_link_libraries(test_mainwindow Qt5::Core Qt5::Widgets Qt5::Test Qt5::Network)
target_include_directories(test_mainwindow PRIVATE ${CMAKE_SOURCE_DIR}/src)

add_test(NAME TestMainWindow COMMAND test_mainwindow)

add_executable(test_datawidget
    unit/test_datawidget.cpp
    ${CMAKE_SOURCE_DIR}/src/datawidget.cpp
)
target_link_libraries(test_datawidget Qt5::Core Qt5::Widgets Qt5::Test Qt5::Network)
target_include_directories(test_datawidget PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME TestDataWidget COMMAND test_datawidget)

add_executable(test_animatedprogressbar
    unit/test_animatedprogressbar.cpp
    ${CMAKE_SOURCE_DIR}/src/animatedprogressbar.cpp
)
target_link_libraries(test_animatedprogressbar Qt5::Core Qt5::Widgets Qt5::Test Qt5::Network)
target_include_directories(test_animatedprogressbar PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME TestAnimatedProgressBar COMMAND test_animatedprogressbar)

add_executable(test_graphwidget
    unit/test_graphwidget.cpp
    ${CMAKE_SOURCE_DIR}/src/graphwidget.cpp
)
target_link_libraries(test_graphwidget Qt5::Core Qt5::Widgets Qt5::Test Qt5::Network)
target_include_directories(test_graphwidget PRIVATE ${CMAKE_SOURCE_DIR}/src)
add_test(NAME TestGraphWidget COMMAND test_graphwidget)
