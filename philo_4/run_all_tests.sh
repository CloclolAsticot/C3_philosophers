#!/bin/bash
# filepath: run_all_tests.sh

echo "========================================="
echo "    PHILOSOPHERS COMPREHENSIVE TESTS"
echo "========================================="

# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

passed=0
failed=0

run_test() {
    local test_name="$1"
    local command="$2"
    local expected_behavior="$3"
    local timeout_duration="$4"
    
    echo -e "${YELLOW}Running: $test_name${NC}"
    echo "Command: $command"
    
    if [ -n "$timeout_duration" ]; then
        timeout $timeout_duration $command > test_output.tmp 2>&1
        result=$?
    else
        $command > test_output.tmp 2>&1
        result=$?
    fi
    
    case $expected_behavior in
        "should_complete")
            if [ $result -eq 0 ]; then
                echo -e "${GREEN}✓ PASSED${NC}"
                ((passed++))
            else
                echo -e "${RED}✗ FAILED - Expected completion, got exit code $result${NC}"
                ((failed++))
            fi
            ;;
        "should_error")
            if [ $result -ne 0 ]; then
                echo -e "${GREEN}✓ PASSED${NC}"
                ((passed++))
            else
                echo -e "${RED}✗ FAILED - Expected error, but completed successfully${NC}"
                ((failed++))
            fi
            ;;
        "should_timeout")
            if [ $result -eq 124 ]; then
                echo -e "${GREEN}✓ PASSED${NC}"
                ((passed++))
            else
                echo -e "${RED}✗ FAILED - Expected timeout, got exit code $result${NC}"
                ((failed++))
            fi
            ;;
    esac
    
    echo "Output:"
    head -10 test_output.tmp
    echo "---"
    echo ""
}

# Test cases
run_test "Basic functionality" "./philo 4 410 200 200 5" "should_complete" "10s"
run_test "One philosopher dies" "./philo 1 800 200 200" "should_complete" "5s"
run_test "Two philosophers" "./philo 2 800 200 200 3" "should_complete" "10s"
run_test "Death case" "./philo 4 310 400 200" "should_complete" "5s"
run_test "Invalid args - too few" "./philo 4 800" "should_error"
run_test "Invalid args - zero philos" "./philo 0 800 200 200" "should_error"
run_test "Invalid args - negative" "./philo 4 -800 200 200" "should_error"
run_test "Invalid args - non-numeric" "./philo abc 800 200 200" "should_error"
run_test "Stress test - many philos" "./philo 20 800 200 200 3" "should_complete" "15s"
run_test "Long running simulation" "./philo 4 5000 200 200 20" "should_finish" "30s"

# Cleanup
rm -f test_output.tmp

echo "========================================="
echo -e "${GREEN}PASSED: $passed${NC}"
echo -e "${RED}FAILED: $failed${NC}"
echo "========================================="

if [ $failed -eq 0 ]; then
    echo -e "${GREEN}ALL TESTS PASSED! 🎉${NC}"
    exit 0
else
    echo -e "${RED}SOME TESTS FAILED! 😞${NC}"
    exit 1
fi