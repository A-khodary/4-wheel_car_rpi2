#! /bin/sh
g++ -o test motor.cpp GPIO.cpp -lwiringPi -lpthread
echo "done building"
echo running 
sudo ./test
