$EXTRACTRC `find . -name \*.ui` >> rc.cpp
$XGETTEXT *.cpp css/*.cpp -o $podir/kcmkonqhtml.pot
