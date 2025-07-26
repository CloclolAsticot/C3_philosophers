#!/bin/bash
# filepath: test_stress.sh

echo "=== STRESS TESTS ==="

# Test 1: Many philosophers
echo "Test 1: Many philosophers"
./philo 20 800 200 200 5
echo ""

# Test 2: Very fast eating
echo "Test 2: Very fast actions"
./philo 5 800 1 1 10
echo ""

# Test 3: Long simulation
echo "Test 3: Long running simulation"
timeout 30s ./philo 4 5000 200 200 50
echo ""

# Test 4: Maximum philosophers
echo "Test 4: Maximum philosophers"
./philo 200 800 200 200 3
echo ""