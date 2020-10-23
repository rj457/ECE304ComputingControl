For this week's lab, the objectives were transferring a simulation of nulling filter from MATLAB into Arduino timer interrupt. The 16MHz in 256 persecular and 500 Hz per interrupt is enough to compute the filter function similar in MATLAB. The computatianl formats of the numbers were all converted from either float or integer into fixed formats (aka Q format or binary forms). The simulations coming out of the Arduino should looks the same from MATLAB results using same filter functions without converting floats into fixed formats. 

For Building FixedPoint Library, Please Download them from Arduino Library first. 
https://github.com/Pharap/FixedPointsArduino
