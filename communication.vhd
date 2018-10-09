LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY GPIO_communication IS
PORT 	(	
	pi_clk : IN std_logic; 
	D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, D13, D14, D15 : OUT std_logic;
	reset, clk : IN std_logic
	);
END GPIO_communication; 

ARCHITECTURE bhv_communication of GPIO_communication IS 
BEGIN 
PROCESS (pi_clk, reset, clk)
	VARIABLE frequency : integer; 
	VARIABLE freq_unsigned : unsigned(15 DOWNTO 0);
BEGIN 
	IF (reset = '0') THEN
	D0 <= '0';
	D1 <= '0';
 	D2 <= '0';
	D3 <= '0';
	D4 <= '0';
	D5 <= '0';
	D6 <= '0';
	D7 <= '0';
	D8 <= '0';
	D9 <= '0';
	D10 <= '0';
	D11 <= '0';
	D12 <= '0';
	D13 <= '0';
	D14 <= '0';
	D15 <= '0';
	ELSIF (rising_edge(pi_clk)) THEN 
		frequency := 24586; 
		freq_unsigned := to_unsigned(frequency, freq_unsigned'LENGTH); 
 		D0 <= freq_unsigned(15); 
		D1 <= freq_unsigned(14); 
		D2 <= freq_unsigned(13);
		D3 <= freq_unsigned(12);
		D4 <= freq_unsigned(11);
		D5 <= freq_unsigned(10);
		D6 <= freq_unsigned(9);
		D7 <= freq_unsigned(8);
		D8 <= freq_unsigned(7);
		D9 <= freq_unsigned(6);
		D10 <= freq_unsigned(5);
		D11 <= freq_unsigned(4);
		D12 <= freq_unsigned(3);
		D13 <= freq_unsigned(2);
		D14 <= freq_unsigned(1);
		D15 <= freq_unsigned(0);
	END IF; 
END PROCESS; 

END bhv_communication; 




