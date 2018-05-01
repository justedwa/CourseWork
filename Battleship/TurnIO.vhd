----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    10:05:30 04/30/2017 
-- Design Name: 
-- Module Name:    TurnIO - Behavioral 
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

entity TurnIO is
port
(
	turnState : IN std_logic;
	turnIO : OUT std_logic_vector(1 downto 0)
);
end TurnIO;

architecture Behavioral of TurnIO is

begin

turnIO(0) <= turnState;
turnIO(1) <= not turnState;

end Behavioral;

