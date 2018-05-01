----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    09:59:49 04/30/2017 
-- Design Name: 
-- Module Name:    HitMiss - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity HitMiss is
port
(
	hit : in std_logic;
	hmEN : in std_logic;
	HMIO : out std_logic_vector(1 downto 0)
);
end HitMiss;

architecture Behavioral of HitMiss is
begin

HMIO(0) <= hit;
HMIO(1) <= not hit and hmEN;

end Behavioral;

