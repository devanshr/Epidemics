#clear; rm Epidemics.bin; g++ -O3 -o Epidemics.bin main.cpp `pkg-config --cflags --libs gtk+-3.0` -export-dynamic;./Epidemics.bin
rm ~/Documents/test/*;
clear; rm Epidemics.bin; g++ -O0 -mavx -mfma -o Epidemics.bin main.cpp `pkg-config --cflags --libs gtk+-3.0` -export-dynamic;./Epidemics.bin
