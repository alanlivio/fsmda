#!/bin/bash

### profilie configuration
n=2
app_id=dc05b236-0cce-4f1d-996b-edd11a66d907

### redirect erros to /dev/null
#exec 1> /dev/null
exec 2> /dev/null

### release old log
rm fsmda_profiling.log

### profile_pairing  ########################################
echo "### Running $n times profile_pairing ###"
for class in "active" "passive" "mediacapture" "ondemand";do
    for ((i=1; i<=$n; i++));do
      ./release_fake_child_parent.sh
      ./fake_parent_helper --device_class=$class --application_id=$app_id \
         >> fsmda_profiling.log &
      ./fake_child_helper --device_class=$class --application_id=$app_id --profile_pairing \
         >> fsmda_profiling.log
      ./release_fake_child_parent.sh
    done
    echo -n "$class child average="
    grep "fsmda_child profile_pairing $class" < fsmda_profiling.log \
      |awk '{ SUM += $4; N += 1} END { printf "%s\n",SUM/N}'
done

### profile_remove_device ########################################
echo "### Running $n times profile_remove_device ###"
for class in "active" "passive" "mediacapture" "ondemand";do
    for ((i=1; i<=$n; i++));do
      ./release_fake_child_parent.sh
      ./fake_parent_helper --device_class=$class --application_id=$app_id --profile_remove_device \
         >> fsmda_profiling.log &
      ./fake_child_helper --device_class=$class --application_id=$app_id\
         >> fsmda_profiling.log
      ./release_fake_child_parent.sh
    done
    echo -n "$class parent average="
    grep "fsmda_parent profile_remove_device $class" < fsmda_profiling.log \
      |awk '{ SUM += $4; N += 1} END { printf "%s\n",SUM/N }'
done

### profile_command  ########################################
echo "### Running $n times profile_command ###"
for class in "active";do
    for ((i=1; i<=$n; i++));do
      ./release_fake_child_parent.sh
      ./fake_parent_helper --device_class=$class --application_id=$app_id --profile_command \
         >> fsmda_profiling.log &
      ./fake_child_helper --device_class=$class --application_id=$app_id \
         >> fsmda_profiling.log
      ./release_fake_child_parent.sh
    done
    echo -n "$class parent average="
    grep "fsmda_parent profile_command $class" < fsmda_profiling.log \
      |awk '{ SUM += $4; N += 1} END { printf "%s\n",SUM/N }'
done


### profile_prepare  ########################################
echo "### Running $n times profile_prepare ###"
for class in "active";do
    for ((i=1; i<=$n; i++));do
      ./release_fake_child_parent.sh
      ./fake_parent_helper --device_class=$class --application_id=$app_id --profile_prepare \
         >> fsmda_profiling.log &
      ./fake_child_helper --device_class=$class --application_id=$app_id \
         >> fsmda_profiling.log
      ./release_fake_child_parent.sh
    done
    echo -n "$class parent average="
    grep "fsmda_parent profile_prepare $class" < fsmda_profiling.log \
      |awk '{ SUM += $4; N += 1} END { printf "%s\n",SUM/N }'
done

### profile_variable  ########################################
echo "### Running $n times profile_variable ###"
for class in "active";do
    for ((i=1; i<=$n; i++));do
      ./release_fake_child_parent.sh
      ./fake_parent_helper --device_class=$class --application_id=$app_id --profile_variable \
         >> fsmda_profiling.log &
      ./fake_child_helper --device_class=$class --application_id=$app_id\
         >> fsmda_profiling.log
      ./release_fake_child_parent.sh
    done
    echo -n "$class parent average="
    grep "fsmda_parent profile_variable $class" < fsmda_profiling.log \
      |awk '{ SUM += $4; N += 1} END { printf "%s\n",SUM/N }'
done

### profile_bufferd_command  ########################################
echo "### Running $n times profile_bufferd_command ###"
for class in "active";do
    for ((i=1; i<=$n; i++));do
      ./release_fake_child_parent.sh
      ./fake_parent_helper --device_class=$class --application_id=$app_id --profile_bufferd_command \
         >> fsmda_profiling.log &
      ./fake_child_helper --device_class=$class --application_id=$app_id --profile_bufferd_command \
         >> fsmda_profiling.log
      ./release_fake_child_parent.sh
    done
    echo -n "$class child average="
    grep "fsmda_child profile_bufferd_command $class" < fsmda_profiling.log \
      |awk '{ SUM += $4; N += 1} END { printf "%s\n",SUM/N}'
    echo -n "$class parent average="
    grep "fsmda_parent profile_bufferd_command $class" < fsmda_profiling.log \
      |awk '{ SUM += $4; N += 1} END { printf "%s\n",SUM/N }'
done




