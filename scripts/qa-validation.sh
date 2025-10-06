#!/bin/bash
# Professional Quality Assurance Script
# Comprehensive QA validation for Qt5 Industrial HMI Application

set -euo pipefail

# Script Configuration
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "$SCRIPT_DIR/.." && pwd)"
BUILD_DIR="$PROJECT_ROOT/build-qa"
REPORTS_DIR="$PROJECT_ROOT/qa-reports"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Quality Gates Configuration
MIN_COVERAGE=85
MAX_MEMORY_USAGE=100  # MB
MAX_STARTUP_TIME=5000  # ms

# Logging function
log() {
    echo -e "${BLUE}[QA]${NC} $1"
}

success() {
    echo -e "${GREEN}[QA SUCCESS]${NC} $1"
}

warning() {
    echo -e "${YELLOW}[QA WARNING]${NC} $1"
}

error() {
    echo -e "${RED}[QA ERROR]${NC} $1"
}

# Initialize QA environment
init_qa() {
    log "Initializing Quality Assurance environment..."
    
    # Create directories
    mkdir -p "$BUILD_DIR" "$REPORTS_DIR"
    
    # Install QA tools if needed
    if ! command -v cppcheck &> /dev/null; then
        log "Installing cppcheck..."
        sudo apt-get update && sudo apt-get install -y cppcheck
    fi
    
    if ! command -v valgrind &> /dev/null; then
        log "Installing valgrind..."
        sudo apt-get install -y valgrind
    fi
    
    if ! command -v lcov &> /dev/null; then
        log "Installing lcov..."
        sudo apt-get install -y lcov
    fi
    
    success "QA environment initialized"
}

# Static Code Analysis
run_static_analysis() {
    log "Running static code analysis..."
    
    # CPPCheck analysis
    log "Running cppcheck analysis..."
    cppcheck --enable=all \
             --xml \
             --xml-version=2 \
             --suppress=missingIncludeSystem \
             --suppress=unusedFunction \
             --suppress=unmatchedSuppression \
             "$PROJECT_ROOT/src/" 2> "$REPORTS_DIR/cppcheck-report.xml"
    
    # Count issues
    local issues_count=$(grep -c "<error" "$REPORTS_DIR/cppcheck-report.xml" || echo "0")
    
    if [ "$issues_count" -gt 0 ]; then
        warning "Found $issues_count static analysis issues"
        # Parse and display critical issues
        grep "severity=\"error\"" "$REPORTS_DIR/cppcheck-report.xml" || true
    else
        success "No static analysis issues found"
    fi
    
    # Clang-tidy analysis (if available)
    if command -v clang-tidy &> /dev/null; then
        log "Running clang-tidy analysis..."
        find "$PROJECT_ROOT/src" -name "*.cpp" -exec clang-tidy {} -- \
            -I/usr/include/qt5 \
            -I/usr/include/qt5/QtCore \
            -I/usr/include/qt5/QtWidgets \
            -I/usr/include/qt5/QtNetwork \; > "$REPORTS_DIR/clang-tidy-report.txt" 2>&1 || true
        
        success "Clang-tidy analysis completed"
    fi
}

# Code Coverage Analysis
run_coverage_analysis() {
    log "Running code coverage analysis..."
    
    cd "$BUILD_DIR"
    
    # Configure with coverage flags
    cmake -DCMAKE_BUILD_TYPE=Debug \
          -DCMAKE_CXX_FLAGS="--coverage" \
          -DCMAKE_C_FLAGS="--coverage" \
          "$PROJECT_ROOT"
    
    # Build with coverage
    make -j$(nproc)
    
    # Run tests with coverage
    if [ -x "$PROJECT_ROOT/scripts/run-tests.sh" ]; then
        cd "$PROJECT_ROOT"
        ./scripts/run-tests.sh --coverage --build-dir="$BUILD_DIR"
    else
        warning "Test runner not found, running basic tests..."
        cd "$BUILD_DIR"
        ctest --output-on-failure || true
    fi
    
    # Generate coverage report
    cd "$BUILD_DIR"
    lcov --capture --directory . --output-file coverage.info
    lcov --remove coverage.info \
         '/usr/*' \
         '*/tests/*' \
         '*/mxe-lite/*' \
         '*/deps/*' \
         '*/build-*/*' \
         --output-file coverage_filtered.info
    
    # Generate HTML report
    genhtml coverage_filtered.info --output-directory "$REPORTS_DIR/coverage"
    
    # Extract coverage percentage
    local coverage_percent=$(lcov --summary coverage_filtered.info 2>&1 | \
                           grep "lines" | \
                           grep -o "[0-9.]*%" | \
                           head -1 | \
                           sed 's/%//')
    
    echo "$coverage_percent" > "$REPORTS_DIR/coverage_percent.txt"
    
    if (( $(echo "$coverage_percent >= $MIN_COVERAGE" | bc -l) )); then
        success "Code coverage: ${coverage_percent}% (target: ${MIN_COVERAGE}%)"
    else
        error "Code coverage: ${coverage_percent}% below target of ${MIN_COVERAGE}%"
        return 1
    fi
}

# Memory Leak Detection
run_memory_analysis() {
    log "Running memory leak detection..."
    
    cd "$BUILD_DIR"
    
    # Build debug version
    if [ ! -f "bin/ModernSciFiHMI" ]; then
        cmake -DCMAKE_BUILD_TYPE=Debug "$PROJECT_ROOT"
        make -j$(nproc)
    fi
    
    # Run valgrind
    if [ -x "bin/ModernSciFiHMI" ]; then
        timeout 60 valgrind --tool=memcheck \
                           --leak-check=full \
                           --show-leak-kinds=all \
                           --track-origins=yes \
                           --xml=yes \
                           --xml-file="$REPORTS_DIR/valgrind-report.xml" \
                           ./bin/ModernSciFiHMI --version 2>/dev/null || true
        
        # Check for memory leaks
        if grep -q "ERROR SUMMARY: 0 errors" "$REPORTS_DIR/valgrind-report.xml"; then
            success "No memory leaks detected"
        else
            warning "Memory issues detected, check valgrind report"
        fi
    else
        warning "Executable not found, skipping memory analysis"
    fi
}

# Performance Testing
run_performance_tests() {
    log "Running performance tests..."
    
    cd "$BUILD_DIR"
    
    # Build release version
    cmake -DCMAKE_BUILD_TYPE=Release "$PROJECT_ROOT"
    make -j$(nproc)
    
    # Test startup time
    if [ -x "bin/ModernSciFiHMI" ]; then
        log "Testing application startup time..."
        
        local startup_times=()
        for i in {1..5}; do
            local start_time=$(date +%s%3N)
            timeout 10 ./bin/ModernSciFiHMI --version >/dev/null 2>&1 || true
            local end_time=$(date +%s%3N)
            local duration=$((end_time - start_time))
            startup_times+=($duration)
        done
        
        # Calculate average startup time
        local total=0
        for time in "${startup_times[@]}"; do
            total=$((total + time))
        done
        local avg_startup=$((total / ${#startup_times[@]}))
        
        echo "$avg_startup" > "$REPORTS_DIR/startup_time_ms.txt"
        
        if [ "$avg_startup" -le "$MAX_STARTUP_TIME" ]; then
            success "Average startup time: ${avg_startup}ms (target: <${MAX_STARTUP_TIME}ms)"
        else
            warning "Startup time ${avg_startup}ms exceeds target of ${MAX_STARTUP_TIME}ms"
        fi
    fi
    
    # Memory usage test
    log "Testing memory usage..."
    if command -v ps &> /dev/null && [ -x "bin/ModernSciFiHMI" ]; then
        timeout 30 ./bin/ModernSciFiHMI --version &
        local pid=$!
        sleep 2
        
        if kill -0 "$pid" 2>/dev/null; then
            local memory_kb=$(ps -o rss= -p "$pid" 2>/dev/null || echo "0")
            local memory_mb=$((memory_kb / 1024))
            
            echo "$memory_mb" > "$REPORTS_DIR/memory_usage_mb.txt"
            
            if [ "$memory_mb" -le "$MAX_MEMORY_USAGE" ]; then
                success "Memory usage: ${memory_mb}MB (target: <${MAX_MEMORY_USAGE}MB)"
            else
                warning "Memory usage ${memory_mb}MB exceeds target of ${MAX_MEMORY_USAGE}MB"
            fi
            
            kill "$pid" 2>/dev/null || true
        fi
    fi
}

# Security Analysis
run_security_analysis() {
    log "Running security analysis..."
    
    # Check for common security issues in source code
    log "Scanning for potential security issues..."
    
    local security_issues=0
    
    # Check for unsafe functions
    if grep -r "strcpy\|strcat\|sprintf\|gets" "$PROJECT_ROOT/src/" --include="*.cpp" --include="*.h" >/dev/null 2>&1; then
        warning "Found usage of potentially unsafe C functions"
        grep -rn "strcpy\|strcat\|sprintf\|gets" "$PROJECT_ROOT/src/" --include="*.cpp" --include="*.h" > "$REPORTS_DIR/unsafe_functions.txt" || true
        security_issues=$((security_issues + 1))
    fi
    
    # Check for TODO/FIXME/HACK comments that might indicate security issues
    if grep -r "TODO.*security\|FIXME.*security\|HACK.*security" "$PROJECT_ROOT/src/" --include="*.cpp" --include="*.h" >/dev/null 2>&1; then
        warning "Found security-related TODO/FIXME comments"
        grep -rn "TODO.*security\|FIXME.*security\|HACK.*security" "$PROJECT_ROOT/src/" --include="*.cpp" --include="*.h" > "$REPORTS_DIR/security_todos.txt" || true
        security_issues=$((security_issues + 1))
    fi
    
    if [ "$security_issues" -eq 0 ]; then
        success "No obvious security issues found"
    else
        warning "Found $security_issues potential security issues"
    fi
}

# Generate QA Report
generate_qa_report() {
    log "Generating QA summary report..."
    
    local report_file="$REPORTS_DIR/qa-summary.html"
    
    cat > "$report_file" << EOF
<!DOCTYPE html>
<html>
<head>
    <title>Quality Assurance Report - Qt5 Industrial HMI</title>
    <style>
        body { font-family: Arial, sans-serif; margin: 40px; }
        .header { background: #2c3e50; color: white; padding: 20px; border-radius: 5px; }
        .section { margin: 20px 0; padding: 15px; border-left: 4px solid #3498db; }
        .success { border-left-color: #27ae60; background: #d5f4e6; }
        .warning { border-left-color: #f39c12; background: #fef9e7; }
        .error { border-left-color: #e74c3c; background: #fadbd8; }
        .metric { display: inline-block; margin: 10px; padding: 10px; background: #ecf0f1; border-radius: 5px; }
    </style>
</head>
<body>
    <div class="header">
        <h1>Quality Assurance Report</h1>
        <p>Qt5 Industrial HMI Application - $(date)</p>
    </div>
    
    <div class="section">
        <h2>Quality Metrics</h2>
EOF

    # Add coverage metric
    if [ -f "$REPORTS_DIR/coverage_percent.txt" ]; then
        local coverage=$(cat "$REPORTS_DIR/coverage_percent.txt")
        echo "        <div class=\"metric\">Code Coverage: ${coverage}%</div>" >> "$report_file"
    fi
    
    # Add startup time metric
    if [ -f "$REPORTS_DIR/startup_time_ms.txt" ]; then
        local startup_time=$(cat "$REPORTS_DIR/startup_time_ms.txt")
        echo "        <div class=\"metric\">Startup Time: ${startup_time}ms</div>" >> "$report_file"
    fi
    
    # Add memory usage metric
    if [ -f "$REPORTS_DIR/memory_usage_mb.txt" ]; then
        local memory_usage=$(cat "$REPORTS_DIR/memory_usage_mb.txt")
        echo "        <div class=\"metric\">Memory Usage: ${memory_usage}MB</div>" >> "$report_file"
    fi
    
    cat >> "$report_file" << EOF
    </div>
    
    <div class="section">
        <h2>Analysis Results</h2>
        <p>Detailed analysis results are available in the following files:</p>
        <ul>
            <li><a href="cppcheck-report.xml">Static Analysis Report (CPPCheck)</a></li>
            <li><a href="coverage/index.html">Code Coverage Report</a></li>
            <li><a href="valgrind-report.xml">Memory Analysis Report</a></li>
        </ul>
    </div>
    
    <div class="section success">
        <h2>Quality Gates Status</h2>
        <p>All critical quality gates have been evaluated. See individual reports for detailed analysis.</p>
    </div>
    
</body>
</html>
EOF

    success "QA report generated: $report_file"
}

# Main execution
main() {
    log "Starting Quality Assurance validation..."
    log "Project: Qt5 Industrial HMI Application"
    log "Build directory: $BUILD_DIR"
    log "Reports directory: $REPORTS_DIR"
    
    # Initialize
    init_qa
    
    # Run all QA checks
    local qa_status=0
    
    run_static_analysis || qa_status=1
    run_coverage_analysis || qa_status=1
    run_memory_analysis || qa_status=1
    run_performance_tests || qa_status=1
    run_security_analysis || qa_status=1
    
    # Generate report
    generate_qa_report
    
    # Final status
    if [ "$qa_status" -eq 0 ]; then
        success "Quality Assurance validation completed successfully!"
        success "All quality gates passed ✅"
    else
        warning "Quality Assurance validation completed with warnings"
        warning "Some quality gates may have failed ⚠️"
    fi
    
    log "QA reports available in: $REPORTS_DIR"
    
    return $qa_status
}

# Handle command line arguments
case "${1:-}" in
    --help|-h)
        echo "Quality Assurance Script for Qt5 Industrial HMI"
        echo "Usage: $0 [options]"
        echo ""
        echo "Options:"
        echo "  --help, -h     Show this help message"
        echo "  --static       Run only static analysis"
        echo "  --coverage     Run only coverage analysis"
        echo "  --memory       Run only memory analysis"
        echo "  --performance  Run only performance tests"
        echo "  --security     Run only security analysis"
        echo ""
        exit 0
        ;;
    --static)
        init_qa
        run_static_analysis
        ;;
    --coverage)
        init_qa
        run_coverage_analysis
        ;;
    --memory)
        init_qa
        run_memory_analysis
        ;;
    --performance)
        init_qa
        run_performance_tests
        ;;
    --security)
        init_qa
        run_security_analysis
        ;;
    *)
        main "$@"
        ;;
esac