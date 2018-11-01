sudo apt-get install gtk+2.0
sudo apt-get install libcanberra-gtk-module

gcc controller.c -o controllerUI `pkg-config --cflags --libs gtk+-2.0` -lpthread -lm -lwiringPi
gcc GUIview.c -o GUIview `pkg-config --cflags --libs gtk+-2.0` -lpthread
gcc tuningUtils.c -o TUItest `pkg-config --cflags --libs gtk+-2.0` -lpthread -lm

