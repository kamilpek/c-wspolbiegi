#!/bin/bash

var=1

echo $$

until [$var -ge 5] do
"$0"
var=$((var+1))
done

exit


