#!/bin/bash
# Enhanced memory and thread safety tests for philosophers

echo "=== COMPREHENSIVE VALGRIND TESTS ==="

if ! command -v valgrind &> /dev/null; then
    echo "Valgrind not found. Please install valgrind to run memory tests."
    exit 1
fi

echo "Test 1: Memory leak detection"
echo "Running: 4 philosophers, no death scenario"
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --run-libc-freeres=no \
         --suppressions=/dev/null \
         ./philo 4 800 200 200 5

echo ""
echo "Test 2: Memory leak with philosopher death"
echo "Running: 4 philosophers, death scenario"
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         ./philo 4 310 400 200

echo ""
echo "Test 3: Thread safety - Race condition detection (Helgrind)"
echo "Running: 5 philosophers"
valgrind --tool=helgrind \
         --history-level=full \
         --conflict-cache-size=10000000 \
         ./philo 5 800 200 200 3

echo ""
echo "Test 4: Data race detection (DRD)"
echo "Running: 3 philosophers"
valgrind --tool=drd \
         --check-stack-var=yes \
         --show-confl-seg=yes \
         --show-stack-usage=yes \
         ./philo 3 800 200 200 2

echo ""
echo "Test 5: Deadlock detection"
echo "Running: 2 philosophers (potential deadlock scenario)"
valgrind --tool=helgrind \
         --track-lockorders=yes \
         ./philo 2 800 200 200 3

echo ""
echo "Test 6: File descriptor tracking"
echo "Running: 4 philosophers with fd tracking"
valgrind --tool=memcheck \
         --track-fds=yes \
         --leak-check=full \
         ./philo 4 800 200 200 5