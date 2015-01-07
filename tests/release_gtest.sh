#!/bin/bash
killall lt-testsuit_gtest testsuit_gtest &> /dev/null
rm -rf /dev/shm/sem.fsmda_semaphore_* 
exit 0
