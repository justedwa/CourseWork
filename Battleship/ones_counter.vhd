

library IEEE;

use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using

-- arithmetic functions with Signed or Unsigned values

--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating

-- any Xilinx leaf cells in this code.

--library UNISIM;

--use UNISIM.VComponents.all;

entity ones_counter is

Port (

	clk : IN std_logic;

	reset : IN std_logic;

	input_ext : IN std_logic;

	flag : OUT std_logic );

end ones_counter;


architecture Behavioral of ones_counter is


type state_type is (S0, S1, S2);

signal state, next_state : state_type;

begin

SYNC_PROC : process (clk)

begin


	if rising_edge(clk) then

		if (reset = '1') then	
			state <= S0;
		else
			state <= next_state;
		end if;
	end if;
end process;

OUTPUT_DECODE : process (state, input_ext)

begin

	flag <= '0';
	case (state) is
	when S0 =>
		if (input_ext = '1') then
			flag <= '0';
		else flag <= '1';
		end if;


	when S1 =>
	flag <= '0';

	when S2 =>
		if(input_ext = '1') then
			flag <= '1';
		else flag <= '0';
		end if;


	when others =>
	flag <= '0';

end case;
end process;


NEXT_STATE_DECODE : process (state, input_ext)


begin
next_state <= S0;
case (state) is

	when S0 =>

	if (input_ext = '1') then
		next_state <= S1;
	else 
		next_state <= S0;
	end if;


	when S1 =>

	if (input_ext = '0') then
		next_state <= S1;
	else 
		next_state <= S2;
	end if;


	when S2 =>

	if (input_ext = '0') then
		next_state <= S2;
	else 
		next_state <= S0;
	end if;


	when others =>
	next_state <= S0;


end case;


end process;
end behavior;