library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

library UNISIM;
use UNISIM.VComponents.all;

entity countx is
Port
(
	clk1 : IN std_logic;
	countx : OUT STD_LOGIC_vector(1 downto 0)
);
end countx;

architecture behavior of countx is
Signal count_int : STD_LOGIC_vector(1 downto 0);

begin 

	countx <= count_int;
	
	process (clk1)
	begin
		if rising_edge(clk1) then
			case (count_int) is
				when "00" => count_int <= "01";
				when "01" => count_int <= "10";
				when "10" => count_int <= "11";
				when "11" => count_int <= "00";
				when others => count_int <= "00";
			end case;
		else 
			count_int <= count_int;
		end if;
	end process;
end behavior;
		
			
				