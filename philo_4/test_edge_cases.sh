#!/bin/bash
# filepath: test_edge_cases.sh

echo "=== EDGE CASE TESTS ==="

# Test 1: Invalid arguments
echo "Test 1: Invalid number of arguments"
./philo 4 800 200
echo "Expected: Error message"
echo ""

# Test 2: Zero values
echo "Test 2: Zero philosophers"
./philo 0 800 200 200
echo "Expected: Error message"
echo ""

# Test 3: Negative values  
echo "Test 3: Negative time_to_die"
./philo 4 -800 200 200
echo "Expected: Error message"
echo ""

# Test 4: Non-numeric arguments
echo "Test 4: Non-numeric argument"
./philo abc 800 200 200
echo "Expected: Error message"
echo ""

# Test 5: Very large numbers
echo "Test 5: Very large numbers"
./philo 5 2147483647 200 200 5
echo ""