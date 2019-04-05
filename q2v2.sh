#!/usr/bin/env bash

user=$(whoami)
echo "Hello $user. Please enter your birthday."
read -p "Enter day: " bday
read -p "Enter month: " bmonth

year=$(date +%Y)
month=$(date +%m)
day=$(date +%d)


echo "The current date is $day/$month/$year"

array=(31 28 31 30 31 30 31 31 30 31 30 31)

if [ $bday -eq $day ] && [ $bmonth -eq $month ];then
   echo "Happy Birthday!"
elif [ $month -gt $bmonth ] || [ $month -eq $bmonth ] && [ $day -gt $bday ];then
    flag=-1
else
    flag=1
fi


nextYear=$(($year+1))

thisLeap=isLeap $year
nextLeap=isLeap $nextYear


if [[ $flag -eq 1 ]];then
    if [[ $month -eq $bmonth ]];then
	days=$(($bday-$day))
    else
	x=$(($month-1))
	days=$((array[$x]-$day))
	i=$month
	while [[ $i -lt $(($bmonth-1)) ]]
	do
	      days=$(($days+array[$i]))
	      i=$(($i+1))
	done
	days=$(($days+$bday))
    fi

    if [[ $thisLeap -eq 1 ]] && [ $month -le 2 ] && [ $bmonth -gt 2 ];then
	days=$(($days+1))
    fi

elif [ $flag -eq -1 ];then
    if [ $month -eq $bmonth ];then
	days=$((365-day-bday))
    else
	days=$day
	i=$((month-2))
	while [ $i -gt $(($bmonth)) ]
	do
	    days=$(($days+array[$i]))
	    i=$(($i-1))
	done
	days=$((array[$(($bmonth-1))]-$bday))
	days=$((365-$days))
    fi

    if [ $nextLeap -eq 1 ] && [ $bmonth -gt 2 ];then
	days=$((days+1))
    fi
fi

echo "There are $days to your bday"

exit 0
	    
	
	 

