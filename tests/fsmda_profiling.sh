#!/bin/bash

#profilie configuration
n=2
declare -a classes=("active" "passive" "mediacapture" "ondemand")
app_id=dc05b236-0cce-4f1d-996b-edd11a66d907

# redirect erros to /dev/null
#exec 1>> /dev/null
exec 2>> /dev/null

# clean logs
for class in "${classes[@]}";do
    echo "Running $n instances for $class..."
    rm -rf fsmda_pairing_profile.log
    for ((i=1; i<=$n; i++));do
      ./release_fake_child_parent.sh
      ./fake_parent_helper --device_class=$class --application_id=$app_id  2>&1 &>/dev/null &
      ./fake_child_helper --device_class=$class --application_id=$app_id --enable_profiling >> fsmda_pairing_profile.log
      ./release_fake_child_parent.sh
    done
    grep "fsmda_profiling pairing $class" < fsmda_pairing_profile.log |awk '{ SUM += $4; N += 1} END { print SUM/N }'
done
#grep "fsmda_profiling pairing active" < fsmda_pairing_profile.log
