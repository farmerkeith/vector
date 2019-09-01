# vector
vector container similar to std::vector with access checking compatible with the Arduino environment.
The Arduino environment does not support the try-throw-catch model used by std::vector for handling errors. Hence a different method is needed.
Two access methods are provided (the same as std::vector): unchecked access using [], and checked access using at(). In the case of checked access with at(), if the index is out of range a default object is returned. In the case of a read access, it has a default value (typically zero or an empty string). In the case of a write access, the value is written into a designated place in the vector object (called "extra"). 
The value in that field, and the (out of range) index used to write to it, can be obtained with functions get_extra() and out_of_range(). get_extra() also clears the value back to default (eg 0 for numbers, empty for String). This data may be useful in investigating the source of out of range access.
In addition, the function at() provides for a second, optional parameter, which if provided is written with a 0 for in-range access and a 1 for out-of-range access.

During development I used a lot of "Serial.print" statements which can be controlled using a set of flags included in the vector definition. My intention is to provide compile-time logic to optionally remove these, so they can be available to developers but absent in delivered, working projects. 

The examples folder contains a simple example, and also the complete test suite that I have used to verify the correct operation of the vector.

This software has been tested with a WeMos D1 mini pro (ESP8266 processor)

References are to "Programming" by Bjarne Stroustrup, 2nd edition, Addison Wesley 2014.
See page 601, page 630, 677, 691, ...
Thanks to Zac Staples whose version of a vector got me going on this.



