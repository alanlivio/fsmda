#!/bin/bash

### profilie configuration
n=2
declare -a classes=("active" "passive" "mediacapture" "ondemand")
declare -a profiles=("profile_pairing" "profile_remove_device" \
  "profile_prepare" "profile_command" \
  "profile_variable"  "profile_bufferd_command")
app_id=dc05b236-0cce-4f1d-996b-edd11a66d907

### redirect erros to /dev/null
#exec 1>> /dev/null
exec 2>> /dev/null

### clean logs
rm fsmda_profiling.log

### profiling
for class in "${classes[@]}";do
    ### profile_prepare
    echo "Running $n times of profile_prepare for $class class..."
    rm -rf fsmda_pairing_profile.log
    for ((i=1; i<=$n; i++));do
      ./release_fake_child_parent.sh
      ./fake_parent_helper --device_class=$class --application_id=$app_id --profile_pairing \
         >> fsmda_profiling.log &
      ./fake_child_helper --device_class=$class --application_id=$app_id --profile_pairing \
         >> fsmda_profiling.log
      ./release_fake_child_parent.sh
    done
    grep "fsmda_profiling_child profile_pairing $class" < fsmda_profiling.log \
     |awk '{ SUM += $4; N += 1} END { printf "child_average=%d\n",SUM/N}'
    grep "fsmda_profiling_parent profile_pairing $class" < fsmda_profiling.log \
     |awk '{ SUM += $4; N += 1} END { printf "parent_average=%d\n",SUM/N }'
done
