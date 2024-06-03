@echo off

g++ -o mon_executable main.cpp Sensors.cpp FeaturesCalculator.cpp Features.cpp

mon_executable data_to_put_in_cpp/laura_01052024-12-17-15-830_escalator_cut_0.txt output_cpp/laura_01052024-12-17-15-830_escalator_cut_0.txt
