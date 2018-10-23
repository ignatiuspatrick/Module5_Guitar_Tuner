sudo apt-get install gtk+2.0
gcc GUI/GUIview.c -o GUIview `pkg-config --cflags --libs gtk+-2.0`