#!/bin/bash
# filepath: test_performance.sh

echo "=== PERFORMANCE TESTS ==="

echo "Test 1: Timing precision check"
echo "Running: ./philo 2 400 200 200 10"
time ./philo 2 400 200 200 10

echo ""
echo "Test 2: No unnecessary delays"
echo "Running: ./philo 4 800 200 200 5"
time ./philo 4 800 200 200 5

echo ""
echo "Test 3: Death detection speed"
echo "Running: ./philo 4 200 300 100"
time ./philo 4 200 300 100