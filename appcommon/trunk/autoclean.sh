make clean
make distclean
rm -f config.log
rm -f stamp-h1
rm -f config.guess
rm -f config.status
rm -f config.h
rm -f config.sub
rm -f ltmain.sh
rm -rf autom4te.cache
rm -f configure
find . -name 'Makefile.in' -type f -print0 | xargs -0 /bin/rm -f
find . -name '*~' -type f -print0 | xargs -0 /bin/rm -f


