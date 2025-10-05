#!/bin/bash

# Professional Test Runner for Industrial HMI
# Qt5 Widgets C++17 Test Suite
# Cross-platform test execution with comprehensive reporting

set -e

echo "🧪 Industrial HMI Test Suite Runner"
echo "=================================="
echo ""

# Configuration
PROJECT_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build-tests"
COVERAGE_DIR="${PROJECT_ROOT}/coverage"
REPORTS_DIR="${PROJECT_ROOT}/test-reports"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Helper functions
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Check dependencies
check_dependencies() {
    print_status "Checking test dependencies..."
    
    # Check Qt5 Test module
    if ! pkg-config --exists Qt5Test; then
        print_error "Qt5Test module not found. Install with: sudo apt install qtbase5-dev"
        exit 1
    fi
    
    # Check CMake
    if ! command -v cmake &> /dev/null; then
        print_error "CMake not found. Install with: sudo apt install cmake"
        exit 1
    fi
    
    print_success "All dependencies found"
}

# Setup test build directory
setup_build_dir() {
    print_status "Setting up test build directory..."
    
    # Clean previous test build if requested
    if [[ "$1" == "--clean" ]]; then
        rm -rf "${BUILD_DIR}"
        print_status "Cleaned previous test build"
    fi
    
    mkdir -p "${BUILD_DIR}"
    mkdir -p "${REPORTS_DIR}"
    
    if [[ "$ENABLE_COVERAGE" == "true" ]]; then
        mkdir -p "${COVERAGE_DIR}"
    fi
}

# Configure test build
configure_tests() {
    print_status "Configuring test build..."
    
    cd "${BUILD_DIR}"
    
    local cmake_args=(
        "-DCMAKE_BUILD_TYPE=Debug"
        "-DBUILD_TESTS=ON"
        "${PROJECT_ROOT}"
    )
    
    # Add coverage if requested
    if [[ "$ENABLE_COVERAGE" == "true" ]]; then
        cmake_args+=("-DENABLE_COVERAGE=ON")
        print_status "Coverage reporting enabled"
    fi
    
    cmake "${cmake_args[@]}"
    
    if [[ $? -eq 0 ]]; then
        print_success "Test configuration completed"
    else
        print_error "Test configuration failed"
        exit 1
    fi
}

# Build test suite
build_tests() {
    print_status "Building test suite..."
    
    cd "${BUILD_DIR}"
    make -j$(nproc)
    
    if [[ $? -eq 0 ]]; then
        print_success "Test suite built successfully"
    else
        print_error "Test build failed"
        exit 1
    fi
}

# Run specific test category
run_test_category() {
    local category="$1"
    local description="$2"
    
    print_status "Running ${description}..."
    
    cd "${BUILD_DIR}"
    
    case "$category" in
        "unit")
            ctest -R "UnitTest_*" -V --output-on-failure
            ;;
        "integration")
            ctest -R "IntegrationTest_*" -V --output-on-failure
            ;;
        "performance")
            ctest -R "PerformanceTest_*" -V --output-on-failure
            ;;
        "all")
            ctest -V --output-on-failure
            ;;
        *)
            print_error "Unknown test category: $category"
            return 1
            ;;
    esac
    
    local exit_code=$?
    
    if [[ $exit_code -eq 0 ]]; then
        print_success "${description} passed"
    else
        print_error "${description} failed"
    fi
    
    return $exit_code
}

# Generate test coverage report
generate_coverage() {
    if [[ "$ENABLE_COVERAGE" != "true" ]]; then
        print_warning "Coverage not enabled, skipping report generation"
        return 0
    fi
    
    print_status "Generating coverage report..."
    
    cd "${BUILD_DIR}"
    
    # Check if gcov is available
    if ! command -v gcov &> /dev/null; then
        print_warning "gcov not found, skipping coverage report"
        return 0
    fi
    
    # Generate coverage data
    find . -name "*.gcda" -exec gcov {} \;
    
    # Check if lcov is available for HTML report
    if command -v lcov &> /dev/null && command -v genhtml &> /dev/null; then
        print_status "Generating HTML coverage report..."
        
        lcov --capture --directory . --output-file "${COVERAGE_DIR}/coverage.info"
        lcov --remove "${COVERAGE_DIR}/coverage.info" '/usr/*' '*/tests/*' '*/mocks/*' --output-file "${COVERAGE_DIR}/coverage_filtered.info"
        genhtml "${COVERAGE_DIR}/coverage_filtered.info" --output-directory "${COVERAGE_DIR}/html"
        
        print_success "HTML coverage report generated: ${COVERAGE_DIR}/html/index.html"
    else
        print_warning "lcov/genhtml not found, install with: sudo apt install lcov"
        print_status "Basic coverage data generated in build directory"
    fi
}

# Generate test report summary
generate_report() {
    print_status "Generating test report summary..."
    
    local report_file="${REPORTS_DIR}/test-summary-$(date +%Y%m%d-%H%M%S).txt"
    
    {
        echo "Industrial HMI Test Suite Report"
        echo "Generated: $(date)"
        echo "Build Directory: ${BUILD_DIR}"
        echo ""
        echo "Test Results:"
        echo "============="
        
        cd "${BUILD_DIR}"
        ctest --verbose 2>&1 | tee -a "${report_file}"
        
    } > "${report_file}"
    
    print_success "Test report saved: ${report_file}"
}

# Main execution flow
main() {
    local test_category="all"
    local clean_build=false
    
    # Parse command line arguments
    while [[ $# -gt 0 ]]; do
        case $1 in
            --unit)
                test_category="unit"
                shift
                ;;
            --integration)
                test_category="integration"
                shift
                ;;
            --performance)
                test_category="performance"
                shift
                ;;
            --coverage)
                export ENABLE_COVERAGE="true"
                shift
                ;;
            --clean)
                clean_build=true
                shift
                ;;
            --help)
                echo "Usage: $0 [OPTIONS]"
                echo ""
                echo "Options:"
                echo "  --unit         Run only unit tests"
                echo "  --integration  Run only integration tests"
                echo "  --performance  Run only performance tests"
                echo "  --coverage     Enable test coverage reporting"
                echo "  --clean        Clean previous build"
                echo "  --help         Show this help message"
                echo ""
                echo "Examples:"
                echo "  $0                          # Run all tests"
                echo "  $0 --unit --coverage        # Run unit tests with coverage"
                echo "  $0 --integration --clean    # Clean build and run integration tests"
                exit 0
                ;;
            *)
                print_error "Unknown option: $1"
                print_error "Use --help for usage information"
                exit 1
                ;;
        esac
    done
    
    # Show configuration
    print_status "Test Configuration:"
    echo "  Category: $test_category"
    echo "  Coverage: ${ENABLE_COVERAGE:-false}"
    echo "  Clean build: $clean_build"
    echo ""
    
    # Execute test pipeline
    check_dependencies
    
    if [[ "$clean_build" == true ]]; then
        setup_build_dir --clean
    else
        setup_build_dir
    fi
    
    configure_tests
    build_tests
    
    # Run tests based on category
    case "$test_category" in
        "unit")
            run_test_category "unit" "Unit Tests"
            ;;
        "integration")
            run_test_category "integration" "Integration Tests"
            ;;
        "performance")
            run_test_category "performance" "Performance Tests"
            ;;
        "all")
            local overall_result=0
            
            run_test_category "unit" "Unit Tests" || overall_result=1
            run_test_category "integration" "Integration Tests" || overall_result=1
            run_test_category "performance" "Performance Tests" || overall_result=1
            
            if [[ $overall_result -eq 0 ]]; then
                print_success "All test categories passed!"
            else
                print_error "Some test categories failed"
            fi
            ;;
    esac
    
    local test_result=$?
    
    # Generate reports
    generate_coverage
    generate_report
    
    # Summary
    echo ""
    echo "🏁 Test Suite Complete"
    echo "====================="
    
    if [[ $test_result -eq 0 ]]; then
        print_success "All tests passed successfully!"
        echo ""
        echo "📊 Reports generated:"
        echo "  - Test summary: ${REPORTS_DIR}/"
        if [[ "$ENABLE_COVERAGE" == "true" ]]; then
            echo "  - Coverage report: ${COVERAGE_DIR}/html/index.html"
        fi
        echo ""
        print_success "Industrial HMI is ready for deployment! 🚀"
    else
        print_error "Some tests failed. Please review the output above."
        echo ""
        echo "🔧 Troubleshooting tips:"
        echo "  - Run individual test categories with --unit, --integration, or --performance"
        echo "  - Check test reports in ${REPORTS_DIR}/"
        echo "  - Use --clean to rebuild tests from scratch"
        exit 1
    fi
}

# Execute main function with all arguments
main "$@"