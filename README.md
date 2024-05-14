# RayTracingInAWeekend

This is the implementation of a simple path tracer based on the book of the same name [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by Peter Shirley, Trevor David Black, Steve Hollasch.


### instructions to reproduce
1. Install any compatible c++ compiler with its command line tools (e.g minigw)
2. Compile the 'main.cpp' e.g
    ```shell
        user@pc:~$ g++ main.cpp -o main.exe
        
    ```

3. since the program outputs the file into ppm format using std::cout we output it into a ppm format
    ```shell
        user@pc:~$ main.exe > image.ppm
    ```

4. run the output in a suitable ppm viewer. (I use the online one [ppm viewer](https://www.cs.rhodes.edu/welshc/COMP141_F16/ppmReader.html))