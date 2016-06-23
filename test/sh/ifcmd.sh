


if [ -n `which svn` ]; then
    echo "svn exist"
else
    echo "svn no exist"
fi



if [ -d ".svn" ]; then
    echo "ok"
else 
    echo "no"
fi
