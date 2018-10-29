LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY guitar_tuner IS
PORT (	clk : IN std_logic; 
	ADC_DOUT : IN std_logic; -- stream of bits 0 000 000000000000
	ADC_SCLK : OUT std_logic; -- 10 kHz (min) or 20 MHz (max) on falling edge bit it sends one bit 
	CS_n : OUT std_logic; -- on falling edge of not chip select, start the sample 
	ADC_IN : OUT std_logic; -- settings 10-000110-01 
	reset : IN std_logic;
	pi_clk : IN std_logic; 
	LED1, LED0 : OUT std_logic; 
	D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15 : OUT std_logic
); 
END guitar_tuner; 

ARCHITECTURE bhv_guitar_tuner OF guitar_tuner IS
SIGNAL V : integer; 
SIGNAL freq : integer; 
BEGIN 
adc : entity work.ADConverter port map (
clk => clk,
reset => reset, 
ADC_DOUT => ADC_DOUT,
ADC_IN => ADC_IN, 
ADC_SCLK => ADC_SCLK, 
CS_n => CS_n, 
voltage => V 
); 

comm : entity work.GPIO_communication port map (
pi_clk => pi_clk, 
reset => reset, 
clk => clk, 
LED1 => LED1,
LED0 => LED0,
D0 => D0,
D1 => D1, 
D2 => D2, 
D3 => D3,
D4 => D4, 
D5 => D5,
D6 => D6, 
D7 => D7, 
D8 => D8,
D9 => D9,
D10 => D10,
D11 => D11, 
D12 => D12, 
D13 => D13,
D14 => D14,
D15 => D15,
frequency => freq
); 

freq_cal : entity work.freq_calculator port map (
pi_clk => pi_clk,
reset => reset, 
frequency => freq,
voltage => V
); 

END bhv_guitar_tuner; 