#/bin/sh

let x=0
let n=$1
for i in `seq $n`; do
    make clean &> /dev/null
    make &> /dev/null
    ./decrypt 10 &> /dev/null
    printf "Test $i: "
    if make check &> /dev/null; then
        echo "✅"
    else
        echo "❌"
        let "x=x+1";
    fi
done

echo;
let "n=n-x"
echo $x ❌ \| $n ✅
