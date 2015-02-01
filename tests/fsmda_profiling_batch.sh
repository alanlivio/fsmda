#/bin/bash
rm -rf local_1.log distributed_1.log
./fsmda_profiling.sh  -n 100 >  fsmda_profiling_local.log
./fsmda_profiling.sh  -n 100 >> fsmda_profiling_local.log
./fsmda_profiling.sh  -n 100 >> fsmda_profiling_local.log
./fsmda_profiling.sh  -n 100 >> fsmda_profiling_local.log
./fsmda_profiling.sh  -n 100 >> fsmda_profiling_local.log
cat fsmda_profiling_local.log | grep -v fake_child_helper |grep -v fsmda_parent |grep  -v MockParentClassHandler |grep -v fake_parent_helper|grep -v MockChildClassHandler |grep -v MockActivePlayer > fsmda_profiling_local.csv &&\
./fsmda_profiling.sh --remote_machine 192.168.1.101 -n 100 >  fsmda_profiling_distributed.log
./fsmda_profiling.sh --remote_machine 192.168.1.101 -n 100 >> fsmda_profiling_distributed.log
./fsmda_profiling.sh --remote_machine 192.168.1.101 -n 100 >> fsmda_profiling_distributed.log
./fsmda_profiling.sh --remote_machine 192.168.1.101 -n 100 >> fsmda_profiling_distributed.log
./fsmda_profiling.sh --remote_machine 192.168.1.101 -n 100 >> fsmda_profiling_distributed.log
cat fsmda_profiling_distributed.log | grep -v fake_child_helper |grep -v fsmda_parent |grep  -v MockParentClassHandler |grep -v fake_parent_helper|grep -v MockChildClassHandler |grep -v MockActivePlayer > fsmda_profiling_distributed.csv

