1. enter the command: ```sudo mbed compile --source . --source ~/ee2405/mbed-os-build/ -m B_L4S5I_IOT01A -t GCC_ARM -f```
2. push the button (A1 is used to decrease the pre_freq, A3 is used to increase the pre_freq)(note that each change is 10 frequencies.)
3. push the A2 to confirm the frequency of the wave (then the /dev/ttyACM\* will output the sampled data)
4. enter the command: ```sudo python3 FFT.py```
5. the code FFT.py will output a figure which has two subplots
