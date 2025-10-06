# CMake generated Testfile for 
# Source directory: /workspaces/qpcetu/tests
# Build directory: /workspaces/qpcetu/build-tests/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(UnitTest_IndustrialController "/workspaces/qpcetu/build-tests/tests/test_industrialcontroller")
set_tests_properties(UnitTest_IndustrialController PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/qpcetu/tests/CMakeLists.txt;74;add_test;/workspaces/qpcetu/tests/CMakeLists.txt;0;")
add_test(UnitTest_UdpService "/workspaces/qpcetu/build-tests/tests/test_udpservice")
set_tests_properties(UnitTest_UdpService PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/qpcetu/tests/CMakeLists.txt;84;add_test;/workspaces/qpcetu/tests/CMakeLists.txt;0;")
add_test(IntegrationTest_UDP_Discovery "/workspaces/qpcetu/build-tests/tests/test_udp_integration")
set_tests_properties(IntegrationTest_UDP_Discovery PROPERTIES  _BACKTRACE_TRIPLES "/workspaces/qpcetu/tests/CMakeLists.txt;94;add_test;/workspaces/qpcetu/tests/CMakeLists.txt;0;")
