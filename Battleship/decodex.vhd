library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

library UNISIM;
use UNISIM.VComponents.all;

entity decodex is
Port
(
	x : IN STD_LOGIC_vector(1 downto 0);
	out1 : OUT STD_LOGIC_vector(6 downto 0)
	
);
end decodex;

architecture Behavioral of decodex is 
begin

out1(0) <= x(1) or not x(0);
out1(1) <= '1';

out1(2) <= not x(1) or x(0);
out1(3) <= x(1) or not x(0);

out1(4) <= not x(0);
out1(5) <= (not x(1) and not x(0));

out1(6) <= x(1);

end Behavioral;