#!/bin/bash

#profilie configuration
n=2
declare -a classes=("active" "passive" "mediacapture" "ondemand")
declare -a profiles=("profile_pairing" "profile_prepare" "profile_command" "profile_variable" "profile_remove_device" "profile_bufferd_command")
app_id=dc05b236-0cce-4f1d-996b-edd11a66d907

# redirect erros to /dev/null
#exec 1>> /dev/null
exec 2>> /dev/null

# clean logs
rm fsmda_profiling.log

# profiling
for profile in "${profiles[@]}";do
    for class in "${classes[@]}";do
        echo -n "Running $n instances of $profile for $class class... average="
        rm -rf fsmda_pairing_profile.log
        for ((i=1; i<=$n; i++));do
          ./release_fake_child_parent.sh
          ./fake_parent_helper --device_class=$class --application_id=$app_id  2>&1 &>/dev/null &
          ./fake_child_helper --device_class=$class --application_id=$app_id --$profile >> fsmda_profiling.log
          ./release_fake_child_parent.sh
        done
        grep "fsmda_profiling $profile $class" < fsmda_profiling.log |awk '{ SUM += $4; N += 1} END { print SUM/N }'
    done
done
