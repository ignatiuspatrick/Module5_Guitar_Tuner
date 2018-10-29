LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY freq_calculator IS
PORT 	(	
	pi_clk : IN std_logic; 
	reset : IN std_logic;
	frequency : OUT integer; 
	voltage : IN integer
	);
END freq_calculator; 

ARCHITECTURE bhv_freq_calculator of freq_calculator IS
BEGIN
PROCESS (reset, pi_clk)
BEGIN
IF reset = '0' THEN
frequency <= 0; 
ELSIF rising_edge(pi_clk) THEN
frequency <= voltage;
END IF; 
END PROCESS; 
END bhv_freq_calculator; 