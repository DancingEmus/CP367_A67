isFound=1
if [ $# -gt 0 ]
then
    for args in $@
    do
	
     
    count=$(ls -l | grep -c ^d)
   
    if [ "$count" -ne 0 ]
       then
       dirs=(*/)
    fi
    for d in "${dirs[@]}"
    do
	cd "$d"
	
	val=$(find -name $args)
	
	if [ -z "$val" ]
	then
	    isFound=0
	    
	    cd ..
	    
	else
	    ls -li $val
	    isFound=1
	   
	    cd ..
	    break 1
	    
	fi
	
    done
    if [ $isFound -eq 0 ]
       then
	
	ls -li $args 
    fi
    
        
        
done
else
    echo No arguments given

fi
