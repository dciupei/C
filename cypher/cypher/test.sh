#!/bin/bash

#
# test script for cypher program.
# W. Cochran (wcochran@vancouver.wsu.edu)
#

KEY="'Roses are red'"

if [ ! -x cypher ]; then
    echo "no cypher program!" >& 2
    exit 1
fi

SECRET=test$$
CMD="./cypher e $KEY < test.sh > $SECRET"
echo "encrypting..."
echo $CMD

if ! eval $CMD; then
    rm $SECRET
    echo "fail to encrypt" >& 2
    exit 2
fi

ORIG=orig$$
CMD="./cypher d "$KEY" < $SECRET > $ORIG"
echo "decrypting..."
echo $CMD

if ! eval $CMD; then
    rm $SECRET $ORIG
    echo "fail to decrypt"
    exit 2
fi

echo "Comparing original with encrypted/decrypted original..."

if diff test.sh $ORIG; then
    echo "OK"
else
    echo "fail!"
fi

rm $SECRET $ORIG
exit 0
