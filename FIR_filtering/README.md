# FIR Filtering
The FIR Filtering application has been carried out.
8 KHz sampling frequency and Low Pass filter coefficients for 400 Hz cut frequency are in "coeff.txt"
You can review the report for the details.( only Turkish :) )

More detailed source for -> [dspguide](http://www.dspguide.com/ch6/2.htm)

### Compile:
```
g++ ./main.cpp ./wave.h -o ./main.exe
```

### Run
```
./main.exe wave_file number_of_filter_coeff coeff.txt

./main.exe 1KHz_400HzSin.wav 11 coeff.txt
```

