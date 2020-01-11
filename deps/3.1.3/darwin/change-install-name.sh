#!/bin/sh

OLD_FOLDER=/Users/kusti8/Downloads/wxWidgets-3.1.3/build-release/lib

libnames=`cd lib ; ls -1 | grep '\.[0-9][0-9]*\.dylib$'`
changes=''
for dep in ${libnames} ; do
    changes="${changes} -change ${OLD_FOLDER}/${dep} lib/${dep}"
done
for i in ${libnames} ; do
    install_name_tool ${changes} -id lib/${i} lib/${i}
done
#install_name_tool ${changes} lib/wxrc-3.1