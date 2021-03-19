# Running Statistic
In instant data entry, the average and standard deviation are calculated.

### Mean and Standard Deviation
The mean, indicated by μ (a lower case Greek mu), is the statistician's jargon for the average value of a signal. 
It is found just as you would expect: add all of the samples together, and divide by N. It looks like this in mathematical form:

![mean](http://www.dspguide.com/graphics/E_2_1.gif)  

The standard deviation is similar to the average deviation, except the averaging is done with power instead of amplitude. 
This is achieved by squaring each of the deviations before taking the average (remember, power ∝ voltage2). 
To finish, the square root is taken to compensate for the initial squaring. In equation form, the standard deviation is calculated:

![var](http://www.dspguide.com/graphics/E_2_2.gif)

This method of calculating the mean and standard deviation is adequate for many applications; however, it has two limitations. 
First, if the mean is much larger than the standard deviation, Eq. 2-2 involves subtracting two numbers that are very close in value. 
This can result in excessive round-off error in the calculations, a topic discussed in more detail in Chapter 4. Second, it is often desirable to recalculate the mean and standard deviation as new samples are acquired and added to the signal. 
We will call this type of calculation: running statistics. While the method of Eqs. 2-1 and 2-2 can be used for running statistics, it requires that all of the samples be involved in each new calculation. 
This is a very inefficient use of computational power and memory.

A solution to these problems can be found by manipulating Eqs. 2-1 and 2-2 to provide another equation for calculating the standard deviation:

![result](http://www.dspguide.com/graphics/E_2_3.gif)

While moving through the signal, a running tally is kept of three parameters: (1) the number of samples already processed, (2) the sum of these samples, and (3) the sum of the squares of the samples (that is, square the value of each sample and add the result to the accumulated value). 
After any number of samples have been processed, the mean and standard deviation can be efficiently calculated using only the current value of the three parameters. Table 2-2 shows a program that reports the mean and standard deviation in this manner as each new sample is taken into account. 
This is the method used in hand calculators to find the statistics of a sequence of numbers. Every time you enter a number and press the Σ (summation) key, the three parameters are updated. 
The mean and standard deviation can then be found whenever desired, without having to recalculate the entire sequence.  

More detailed source for -> [dspguide](http://www.dspguide.com/ch2/2.htm)

## Compile
```
$ g++ main.cpp -o main.exe
```

## Run
The program get type of signal and number of sampling.
<pre>
$ main signal_type N

  <b>signal_type </b>: 2 types of signals can be generated to test the running statistics.  
	  0: Time dependent Sinusoidal signal is generated  
	  1: At the level of 1 - + 0.5 noisy signal is generated
  <b>N </b>: Number of samples must be > 1
</pre>

Number of Sampling = 10 while commands for 2 signal types too:
```
./main.exe 0 10
./main.exe 1 10
```

## Output

For example 'main.exe 1 3' outputs:
```
t: 0 Signal: 1.4                                -> Signal value 1.4 at time t0
t: 1 Signal: 1.3 Mean: 1.35 SD: 0.0707107	-> Signal generated and running statistics values at time t1
t: 2 Signal: 0.6 Mean: 1.1 SD: 0.43589		-> Signal generated and running statistics values at time t2
```
