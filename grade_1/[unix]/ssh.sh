#!/usr/bin/env bash

declare -a v
v=($@)
USR=''
PSS=''
LST=''
UP=''
FILE=''

for (( i = 0; i < $#; i++ ))
do
    LINE=${v[i]}

    if [[ $LINE == '--user' ]]
    then
        i=$(expr $i + 1)
        USR=${v[i]}
        continue
    fi

    if [[ $LINE == '--password' ]]
    then
        i=$(expr $i + 1)
        PSS=${v[i]}
        continue
    fi

    if [[ $LINE == '--list' ]]
    then
        i=$(expr $i + 1)
        LST=${v[i]}
        continue
    fi

    if [[ $LINE == '--upgrade' ]]
    then
        i=$(expr $i + 1)
        UP=${v[i]}
        continue
    fi

    FILE=$LINE
done

if [[ $USR == '' && $PSS != '' ]]
then
    echo 'No username'
    exit 1
fi

if [[ $USR != '' && $PSS == '' ]]
then
    echo 'No password'
    exit 1
fi

echo $USR
echo $PSS

if [[ $LST != '' ]]
then
    while read LINE
    do
        if [[ $USR != '' ]]
        then
            sshpass -p $PSS ssh $USR'@'$LINE dpkg -l | tail --lines=+6 | grep $LST | awk '{print $2" "$3;}'
        else
            ssh $LINE dpkg -l | tail --lines=+6 | grep $LST | awk '{print $2" "$3;}'
        fi
    done < $FILE
fi

if [[ $UP != '' ]]
then
    while read LINE
    do
        if [[ $USR != '' ]]
        then
            sshpass -p $PSS ssh $USR'@'$LINE apt-get install $UP
        else
            ssh $LINE apt-get install $UP
        fi
    done < $FILE
fi