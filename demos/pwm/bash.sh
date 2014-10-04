#!/bin/bash
## test script for pcduino PWM sysfs interface, by liaods 2014.02
## /sys/devices/virtual/misc/pwmtimer/freq/pwmX       (r/w min_freq to max_freq )
## /sys/devices/virtual/misc/pwmtimer/freq_range/pwmX (read only: freq range)
## /sys/devices/virtual/misc/pwmtimer/level/pwmX      (r/w 0 to max_level )
## /sys/devices/virtual/misc/pwmtimer/enable/pwmX     (r/w 1: enable, 0:disable)
## /sys/devices/virtual/misc/pwmtimer/max_level/pwmX  (read only)
##            ( X should be one of 5/6/3/9/10/11 )
## Note: need to update your pwm driver to latest version(2014.02)
##  /lib/modules/3.4.29+/kernel/drivers/hardwarelib/pwm.ko
##
## following these steps to config pwm via sysfs interface
## 1) set pin mode function to pwm mode
##    PWM5/6  
##          echo 2 > /sys/devices/virtual/misc/gpio/mode/gpio5
##          echo 2 > /sys/devices/virtual/misc/gpio/mode/gpio6
##    PWM3/9/10/11
##          echo 1 > /sys/devices/virtual/misc/gpio/mode/gpio9
##          echo 1 > /sys/devices/virtual/misc/gpio/mode/gpio10
##          echo 1 > /sys/devices/virtual/misc/gpio/mode/gpio11
##          echo 1 > /sys/devices/virtual/misc/gpio/mode/gpio12
## 2) disable pwm before changing freq 
##   echo 0 >  /sys/devices/virtual/misc/pwmtimer/enable/pwmX 
## 3) set freq ( min_freq <= freq <= max_freq )
##   echo FREQ >  /sys/devices/virtual/misc/pwmtimer/enable/pwmX 
##   you can get freq first: cat /sys/devices/virtual/misc/pwmtimer/freq_range/pwmX
## example:
##   cat /sys/devices/virtual/misc/pwmtimer/freq_range/pwmX
##   max_freq:66700
##   min_freq:2
## 4) set duty cycle
##   duty_cycle = level / max_level
##   get max_level: 
##       cat /sys/devices/virtual/misc/pwmtimer/enable/pwmX 
##   set level ( 0 <= level <= max_level ):
##       echo LEVEL > /sys/devices/virtual/misc/pwmtimer/level/pwmX 
## 5) enable it
##   echo 1 >  /sys/devices/virtual/misc/pwmtimer/enable/pwmX 

PWM=6
DELAY_US=5000000

PWM_SYSFS_DIR=/sys/devices/virtual/misc/pwmtimer
ENABLE=${PWM_SYSFS_DIR}/enable
FREQ_RANGE=${PWM_SYSFS_DIR}/freq_range
FREQ=${PWM_SYSFS_DIR}/freq
MAX_LEVEL=${PWM_SYSFS_DIR}/max_level
LEVEL=${PWM_SYSFS_DIR}/level

_MAX_LEVEL=0
_MAX_FREQ=0
_FREQ=0
_LEVEL=0

# arg: pwmid
pwm_get_min_freq()
{
    node=${FREQ_RANGE}/${1}
    ret=`cat $node | grep "min_freq" | cut -d':' -f2`
    return $ret
}

# arg: pwmid
pwm_get_max_freq()
{
    node=${FREQ_RANGE}/${1}
    _MAX_FREQ=`cat $node | grep "max_freq" | cut -d':' -f2`
}

# arg: pwmid, freq
pwm_set_freq()
{
    node=${FREQ}/${1}
    echo $2 > $node
}

# arg: pwmid
pwm_get_freq()
{
    node=${FREQ}/${1}
    _FREQ=`cat $node`
}

# arg: pwmid
pwm_get_max_level()
{
    node=${MAX_LEVEL}/${1}
    _MAX_LEVEL=`cat $node`
}

# arg: pwmid, level
pwm_set_level()
{
    node=${LEVEL}/${1}
    echo $2 > $node
}

# arg: pwmid
pwm_get_level()
{
    node=${LEVEL}/${1}
    _LEVEL=`cat $node`
}

# arg: pwmid
is_pwm_enable()
{
    node=${ENABLE}/${1}
    ret=`cat $node`
    return $ret
}

# arg: pwmid
pwm_enable()
{
    node=${ENABLE}/${1}
    echo 1 > $node
}

# arg: pwmid
pwm_disable()
{
    node=${ENABLE}/${1}
    echo 0 > $node
}

# arg: id
pwm_pin_mode()
{
    pin=$1
    mode_if=/sys/devices/virtual/misc/gpio/mode/gpio${pin}
    if [ $pin -eq 5 ] || [ $pin -eq 6 ]; then
        echo 2 > $mode_if
    elif [ $pin -eq 3 ] || [ $pin -eq 9 ] || [ $pin -eq 10 ] || [ $pin -eq 11 ]; then
        echo 1 > $mode_if   
    fi
}

main()
{
    echo "test script for pcduino PWM sysfs interface"
    if [ $# -ne 2 ]; then
        echo "Usage: $0 PWM_ID DELAY_US"
        echo "       PWM_ID (3/5/6/9/10/11)"
        echo "example: $0 5 3000000"
        exit 1
    fi
    PWM=$1
    DELAY_US=$2    
    pwmid=pwm${PWM}
    
    if ! [ -d /sys/devices/virtual/misc/pwmtimer/level ]; then
    	echo "please load/update pwm driver first"
    	exit 2
    fi
    
    # set pin mode to pwm function
    pwm_pin_mode $PWM
    
    pwm_get_min_freq $pwmid
    freq=$?
    
    pwm_get_max_freq $pwmid
    max_freq=$_MAX_FREQ

    while [ 1 ]; do 
        if [ $freq -gt $max_freq ]; then
            break 1
        fi      
        #busybox usleep $DELAY_US
        
        # disable 
        pwm_disable $pwmid
        
        # set freq
        pwm_set_freq $pwmid $freq
        
        # get real freq
        pwm_get_freq $pwmid
        real_freq=$_FREQ
        
        # get max level
        pwm_get_max_level $pwmid
        max_level=$_MAX_LEVEL
        
        # set level
        pwm_set_level $pwmid 1
        
        # enable
        pwm_enable $pwmid
        busybox usleep $DELAY_US

        # update level
        level=1
        while [ 1 ]; do
            if [ $level -gt $max_level ]; then
                break 1
            fi
            echo "====$pwmid test, freq=$real_freq(required:$freq) HZ, level = $level/$max_level ===="
            pwm_set_level $pwmid $level
            busybox usleep $DELAY_US    
            level=`expr $level + $level`
        done
                
        freq=`expr $freq + $freq`
    done
}

main $@
