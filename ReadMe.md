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