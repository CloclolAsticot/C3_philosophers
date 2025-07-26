#!/bin/bash
# filepath: test_basic.sh

echo "=== BASIC PHILOSOPHERS TESTS ==="

# Test 1: Basic functionality
echo "Test 1: Basic case - 4 philosophers, should not die"
./philo 4 410 200 200
echo ""

# Test 2: One philosopher (should die)
echo "Test 2: One philosopher - should die"
./philo 1 800 200 200
echo ""

# Test 3: Two philosophers
echo "Test 3: Two philosophers"
./philo 2 800 200 200
echo ""

# Test 4: With meal count
echo "Test 4: 5 philosophers, each must eat 7 times"
./philo 5 800 200 200 7
echo ""