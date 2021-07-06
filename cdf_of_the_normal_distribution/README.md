# Cumulative distribution function of the Normal Distribution
Signals formed from random processes usually have a bell shaped pdf. This is called a normal distribution, a Gauss distribution, or a Gaussian, after the great German mathematician, Karl Friedrich Gauss (1777-1855). The reason why this curve occurs so frequently in nature will be discussed shortly in conjunction with digital noise generation. The basic shape of the curve is generated from a negative squared exponent:

![formula](https://render.githubusercontent.com/render/math?math=\huge\color{Red}y(x)=e^{-x^{2}})

This raw curve can be converted into the complete Gaussian by adding an adjustable mean, ?, and standard deviation, σ. In addition, the equation must be normalized so that the total area under the curve is equal to one, a requirement of all probability distribution functions. This results in the general form of the normal distribution, one of the most important relations in statistics and probability:

![var](http://www.dspguide.com/graphics/E_2_8.gif)

Figure 2-8 shows several examples of Gaussian curves with various means and standard deviations. The mean centers the curve over a particular value, while the standard deviation controls the width of the bell shape.

More detailed source for -> [dspguide](http://www.dspguide.com/ch2/5.htm)

Program calculates CDF of the normal distribution (mean = 0 and standard deviation = 1)

Compile:
```
gcc main.c -lm -o main.exe
```

takes three parameters:
```
$ ./main low_bound upper_bound number_of_sampling
```

## Run
```
low bound => 0, upper bound => 1 and number of sampling => 6:
./main.exe 0 1 6
```
