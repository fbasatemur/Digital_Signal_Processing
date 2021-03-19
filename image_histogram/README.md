# Image Histogram & Statistics
Grayscale (8 bits) image is read. Histogram graph, mean and variance are calculated with image values.

### Mean & Standard Deviation
The histogram can be used to efficiently calculate the mean and standard deviation of very large data sets. This is especially important for images, which can contain millions of samples. 
The histogram groups samples together that have the same value. This allows the statistics to be calculated by working with a few groups, rather than a large number of individual samples. 
Using this approach, the mean and standard deviation are calculated from the histogram by the equations:

![mean](http://www.dspguide.com/graphics/E_2_6.gif)  
![var](http://www.dspguide.com/graphics/E_2_7.gif)

More detailed source for -> [dspguide](http://www.dspguide.com/ch2/4.htm)

## Compile
```
$ g++ main.cpp -o main.exe
```

## Run
The program get grayscale (8 bits) image name argument.
```
$ main image_name
```

for example grayscale lena image:
```
./main.exe lena.bmp
```

## Output
Histogram graph is given in vertical format and each histogram value is expressed at the end of the line.
The mean and variance values of the image are print in the last line.