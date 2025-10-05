# Professional Testing Framework

## Industrial HMI Qt5 C++17 Test Suite

This directory contains a comprehensive testing framework for the Industrial HMI application, implementing enterprise-grade testing practices with Qt5 Test framework.

## 🏗️ **Testing Architecture**

### **Framework Structure**
```
tests/
├── CMakeLists.txt              # Professional test build configuration
├── README.md                   # This documentation
├── unit/                       # Unit tests (isolated component testing)
│   ├── test_industrialcontroller.cpp
│   ├── test_udpservice.cpp
│   ├── test_controllermanager.cpp
│   ├── test_strategies.cpp
│   ├── test_commands.cpp
│   └── test_statemachine.cpp
├── integration/                # Integration tests (component interaction)
│   ├── test_udp_integration.cpp
│   ├── test_controller_integration.cpp
│   └── test_performance.cpp
└── mocks/                      # Mock objects for testing
    ├── mockindustrialcontroller.h/cpp
    ├── mockudpservice.h/cpp
    └── mockcontrollermanager.h/cpp
```

### **Test Categories**

#### **1. Unit Tests** 🔬
- **Purpose**: Test individual components in isolation
- **Coverage**: Core business logic, state management, data processing
- **Mock Usage**: External dependencies replaced with controllable mocks
- **Execution Time**: < 5 seconds per test suite

**Test Suites:**
- `test_industrialcontroller`: Controller state management and error handling
- `test_udpservice`: Network discovery and protocol handling
- `test_controllermanager`: Multi-controller coordination logic
- `test_strategies`: Strategy pattern implementation
- `test_commands`: Command pattern with undo/redo
- `test_statemachine`: State machine transitions and validation

#### **2. Integration Tests** 🔗
- **Purpose**: Test component interactions and workflows
- **Coverage**: UDP discovery → Controller registration → Data management
- **Real Dependencies**: Limited use of actual network components
- **Execution Time**: < 30 seconds per test suite

**Test Suites:**
- `test_udp_integration`: Complete discovery workflow
- `test_controller_integration`: Multi-controller management scenarios
- `test_performance`: Real-time data throughput validation

#### **3. Performance Tests** ⚡
- **Purpose**: Validate real-time performance requirements
- **Coverage**: Data throughput, memory usage, response times
- **Benchmarks**: Industrial HMI performance standards
- **Execution Time**: < 60 seconds per test suite

## 🚀 **Quick Start**

### **Running All Tests**
```bash
# From project root
cd scripts
./run-tests.sh
```

### **Running Specific Test Categories**
```bash
# Unit tests only
./run-tests.sh --unit

# Integration tests only  
./run-tests.sh --integration

# Performance tests only
./run-tests.sh --performance
```

### **With Test Coverage**
```bash
# Run all tests with coverage report
./run-tests.sh --coverage

# Run unit tests with coverage
./run-tests.sh --unit --coverage
```

### **Clean Build**
```bash
# Force clean rebuild of tests
./run-tests.sh --clean
```

## 📊 **Test Coverage & Reporting**

### **Coverage Targets**
- **Unit Tests**: > 90% line coverage
- **Integration Tests**: > 80% workflow coverage
- **Critical Paths**: 100% coverage (error handling, state machines)

### **Report Generation**
Tests generate comprehensive reports in multiple formats:

1. **Console Output**: Real-time test results with colored indicators
2. **Test Summary**: Detailed text report in `test-reports/`
3. **Coverage Report**: HTML coverage analysis (when enabled)
4. **Performance Metrics**: Benchmark results and timing analysis

### **Coverage Tools**
- **GCC Coverage**: Built-in gcov support for line/branch coverage
- **LCOV**: HTML coverage report generation
- **Qt5 Test**: Signal verification and memory leak detection

## 🔧 **Test Configuration**

### **CMake Integration**
The testing framework is fully integrated with the main build system:

```cmake
# Enable tests in debug mode
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON ..

# Enable coverage reporting
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON -DENABLE_COVERAGE=ON ..
```

### **Mock Objects**
Professional mock implementations provide:
- **Controllable Behavior**: Configure responses, delays, failures
- **State Verification**: Track calls, parameters, state changes  
- **Signal Testing**: Qt signal/slot verification
- **Thread Safety**: Safe for concurrent testing scenarios

### **Test Data Management**
- **Deterministic Data**: Reproducible test scenarios
- **Realistic Datasets**: Industrial controller response formats
- **Edge Cases**: Boundary conditions and error scenarios
- **Performance Data**: Large datasets for throughput testing

## 📋 **Test Development Guidelines**

### **Unit Test Best Practices**
```cpp
class TestMyComponent : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();     // One-time setup
    void cleanupTestCase();  // One-time cleanup
    void init();            // Before each test
    void cleanup();         // After each test
    
    // Test methods
    void testNormalOperation();
    void testErrorConditions();
    void testEdgeCases();
    void testPerformance();

private:
    MockDependency *m_mock;
    ComponentUnderTest *m_component;
};
```

### **Signal Testing**
```cpp
void TestMyComponent::testSignalEmission()
{
    QSignalSpy spy(m_component, &Component::dataChanged);
    
    m_component->processData(testData);
    
    QCOMPARE(spy.count(), 1);
    QVariantList args = spy.at(0);
    QCOMPARE(args.at(0).toInt(), expectedValue);
}
```

### **Async Testing**
```cpp
void TestMyComponent::testAsyncOperation()
{
    QSignalSpy spy(m_component, &Component::operationComplete);
    
    m_component->startAsyncOperation();
    
    QVERIFY(spy.wait(5000)); // 5 second timeout
    QCOMPARE(spy.count(), 1);
}
```

### **Error Testing**
```cpp
void TestMyComponent::testErrorHandling()
{
    QSignalSpy errorSpy(m_component, &Component::errorOccurred);
    
    m_mock->setFailureMode(true);
    m_component->performOperation();
    
    QCOMPARE(errorSpy.count(), 1);
    QString error = errorSpy.at(0).at(0).toString();
    QVERIFY(error.contains("expected error message"));
}
```

## 🎯 **Continuous Integration**

### **Automated Testing**
Tests are designed for CI/CD integration:
- **Fast Execution**: Unit tests complete in < 30 seconds
- **Reliable Results**: Deterministic behavior, no flaky tests
- **Clear Reporting**: Machine-readable output formats
- **Failure Analysis**: Detailed error messages and stack traces

### **Test Stages**
1. **Smoke Tests**: Basic functionality verification (< 10 seconds)
2. **Unit Tests**: Comprehensive component testing (< 60 seconds)
3. **Integration Tests**: Cross-component validation (< 120 seconds)
4. **Performance Tests**: Benchmark validation (< 180 seconds)

### **Quality Gates**
- ✅ All unit tests must pass
- ✅ Integration tests must pass
- ✅ Code coverage > 85%
- ✅ No memory leaks detected
- ✅ Performance benchmarks met

## 🔍 **Debugging Test Failures**

### **Common Issues**
1. **Signal Timing**: Use `QSignalSpy::wait()` for async signals
2. **Event Loop**: Call `QApplication::processEvents()` when needed
3. **Mock State**: Ensure mocks are properly reset between tests
4. **Resource Cleanup**: Use RAII for automatic cleanup

### **Debug Tools**
```bash
# Run specific test with debug output
ctest -R "UnitTest_IndustrialController" -V

# Run test under debugger
gdb ./build-tests/tests/test_industrialcontroller

# Memory leak detection
valgrind --tool=memcheck ./build-tests/tests/test_industrialcontroller
```

## 📚 **Additional Resources**

### **Qt Test Framework**
- [Qt Test Documentation](https://doc.qt.io/qt-5/qtest.html)
- [QSignalSpy Documentation](https://doc.qt.io/qt-5/qsignalspy.html)
- [Qt Test Best Practices](https://doc.qt.io/qt-5/qttest-tutorial.html)

### **C++ Testing**
- [Google Test Primer](https://google.github.io/googletest/)
- [Modern C++ Testing](https://github.com/onqtam/doctest)
- [Test-Driven Development](https://en.wikipedia.org/wiki/Test-driven_development)

### **Industrial HMI Testing**
- Industrial automation testing standards
- Real-time system validation techniques
- Safety-critical software testing practices

---

## 🎉 **Getting Started**

1. **Install Dependencies**:
   ```bash
   sudo apt install qtbase5-dev cmake build-essential lcov
   ```

2. **Run First Test**:
   ```bash
   cd scripts
   ./run-tests.sh --unit
   ```

3. **View Coverage Report**:
   ```bash
   ./run-tests.sh --unit --coverage
   # Open coverage/html/index.html in browser
   ```

4. **Develop New Tests**:
   - Copy existing test as template
   - Follow naming conventions
   - Add to CMakeLists.txt
   - Run and verify

**Happy Testing! 🧪✨**