if [ $# -gt 0 ]
then
    for args in $@
    do
	
    echo "proceeding $args"

    count=$(ls -l | grep -c ^d)
    echo "count: $count"
    if [ "$count" -ne 0 ]
       then
       dirs=(*/)
    
    for d in "${dirs[@]}"
    do
	cd "$d"
	
	val=$(find -name $args)
	echo $val
	if [ -z "$val" ]
	then
	    echo not found
	    cd ..
	    
	else
	    ls -i $val
	    
	    echo found
	    cd ..
	    break 1
	    
	fi
	
    done
    else
	ls -l | grep 
    fi    
        
        
done
else
    echo HI



fi
