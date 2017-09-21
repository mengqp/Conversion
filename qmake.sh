# !/bin/sh
make distclean
echo "./em770.sh [type] type = cd/dd/cr(cross debug/desk debug/cross releas), other default is cr"


if [ $# -ne 1 ];
then
	echo "param is default"
	exit
# else
	# echo $1
fi

if [ "$1"x = "cd"x ];
then
	echo "cross debug project"
	QMAKE=/opt/qt-everywhere-opensource-src-4.7.3/bin/qmake
	CONFIG="CONFIG+=Debug"
elif [ "$1"x = "dd"x ];
then
	echo "desk debug project"
	QMAKE=/home/mengqp/app/qtsdk-2010.05/qt/bin/qmake
	CONFIG="CONFIG+=Debug"
elif [ "$1"x = "cr"x ];
then
	echo "cross release project"
	QMAKE=/opt/qt-everywhere-opensource-src-4.7.3/bin/qmake
	CONFIG="CONFIG+=release"
else
	echo "cross release project"
	QMAKE=/opt/qt-everywhere-opensource-src-4.7.3/bin/qmake
	CONFIG="CONFIG+=release"
fi

$QMAKE -project -Wall  -o  ./Convert.pro -after "QT += core gui widgets" "TARGET=./Debug/Convert" $CONFIG  "OBJECTS_DIR = ./Debug/OBJ/" "MOC_DIR = Debug/moc/" "UI_DIR=Debug/ui"
$QMAKE -makefile ./Convert.pro  -o ./Makefile

make
