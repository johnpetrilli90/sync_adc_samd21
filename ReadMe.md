# Extracting Acceptable Performance from the Atmel On-Chip ADC
Configures the ADC and performs synchronous round-robin reads on a hardware timer.

Microchip Studio Version: 7.0.2594

## ADC Configuration
Using the Atmel Start GUI...
1. Driver: HAL:Driver:ADC_Sync
2. Clock: Generic clock generator 0 (8MHz)
3. Component Signals: Select all AIN signals you want to measure
4. Conversion Resoluation: 16-bit (averaging must be enabled)
5. Reference Selection: Anything EXCEPT 1.0 voltage reference <- Do NOT use this option
6. Enable Advanced Configuration
7. Number of Samples to be Collected: 256 samples
8. Sampling Time Lengh: 20 (This is on half clock cycles, so choose a value that will result in full clocks)

## Timer Configuration
Using the Atmel Start GUI...
1. Driver: HAL:Driver:Timer
2. Instance: TC3 (Any TC or TCC will be fine)
3. Clock: Generic clock generator 0 (8MHz)
4. Prescaler: Divide by 8
5. Length of one timer tick in uS: 1000

## Caveats
- This ADC can output good full-scale results at lower frequencies up to ~3kHz (only 1 channel). If you need faster sampling w/ good performance my suggestion would be to choose an external ADC. 
- Here is a nice calculator to play around with: https://blog.thea.codes/getting-the-most-out-of-the-samd21-adc/
- Beware that the faster you make the ADC, the lower the input impedance will be. The source impedance seen by the ADC input should be buffered for best and consistent performance. s