# LPC1768_EEPROM
In this project I use LPC1768  with EEPROM IC as AT24Cxx.
But it is necessary to say that I didn't write all of code myself and just I modified somewhere in codes that I downloaded from other websites.
The AT24Cxx are eeprom IC family that could connect to other devices by I2C protocol. Here is the soft I2C source code to connect At24Cxx to LPC1768.
Frequency of SCL = 100KHZ


                                                
                      LPC1768                               ATC24xx
                  |------------|                        |------------|    
                  |            |                   +3.3v|8          1|GND    
                  |            |                     GND|7          2|GND                 
                  |        P2.1|----------SCL-----------|6          3|GND                               
                  |        P2.0|----------SDA-----------|5          4|GND                                                  
                  |            |                        |------------|                           
                  |            |                                            
                  |------------|                                          
