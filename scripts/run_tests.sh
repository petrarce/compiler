#!/bin/bash
echo "compiling test units"
echo "======="
make CONFIG_TEST=y 2>/dev/null 1>/dev/null
if [ "$?" != "0" ]; then
	echo compilation of test failed...
	exit
fi

echo "running test units"
echo "======="
for i in `find ${PWD} -name test_unit`; do
	${i}
done