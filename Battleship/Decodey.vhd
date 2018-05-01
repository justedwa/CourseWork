library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

library UNISIM;
use UNISIM.VComponents.all;

entity decodey is
Port(
	y : IN STD_LOGIC_vector(1 downto 0);
	out2 : OUT STD_LOGIC_vector(6 downto 0)
	);
end decodey;

architecture Behavioral of decodey is 

begin

out2(0) <= '1';
out2(1) <= (not y(1)) or y(0);

out2(2) <= (not y(1)) or y(0);
out2(3) <= y(1) or y(0);

out2(4) <= '1';
out2(5) <= '1';

out2(6) <= not y(1);

end Behavioral;