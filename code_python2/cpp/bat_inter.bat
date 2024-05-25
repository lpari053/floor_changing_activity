@echo off

g++ -o mon_executable main.cpp Sensors.cpp FeaturesCalculator.cpp Features.cpp fft.cpp

mon_executable data_to_put_in_cpp/laura_01052024-12-17-15-830_escalator.txt output_cpp/test.txt 320

