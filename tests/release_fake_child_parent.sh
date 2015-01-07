#!/bin/bash
killall lt-fake_parent_helper fake_parent_helper lt-fake_parent_helper fake_parent_helper &> /dev/null
rm -rf /dev/shm/sem.fsmda_semaphore_* 
exit 0
