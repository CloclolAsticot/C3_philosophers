#!/bin/bash
# filepath: test_death.sh

echo "=== DEATH DETECTION TESTS ==="

# Test 1: Fast death
echo "Test 1: Should die quickly (time_to_die < time_to_eat)"
./philo 4 310 400 200
echo ""

# Test 2: Edge case death
echo "Test 2: Edge case - very tight timing"
./philo 4 200 190 190
echo ""

# Test 3: One philosopher death
echo "Test 3: One philosopher must die"
./philo 1 400 200 200
echo ""

# Test 4: Many philosophers, tight timing
echo "Test 4: Many philosophers, someone should die"
./philo 10 400 200 200
echo ""