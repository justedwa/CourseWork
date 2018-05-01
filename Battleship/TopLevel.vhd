----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    23:02:02 04/29/2017 
-- Design Name: 
-- Module Name:    TopLevel - Behavioral 
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

entity TopLevel is
	Port( CLK : IN std_logic;
			RST : IN std_logic;
			EndTurn: IN std_logic;
			turnIN : IN std_logic;
			HM : IN std_logic;
			HMEnable : IN std_logic;
			Ytrigger: IN std_logic;
			Xtrigger: IN std_logic;
			ardin: IN std_logic;
			seg1 : OUT std_logic_vector(6 downto 0);
			seg2 : OUT std_logic_vector(6 downto 0);
			statusout : OUT std_logic;
			X : OUT std_logic_vector(1 downto 0);
			Y : OUT std_logic_vector(1 downto 0);
			HMLED : OUT std_logic_vector(1 downto 0);
			TurnLED : OUT std_logic_vector(1 downto 0)
		);
end TopLevel;

architecture Behavioral of TopLevel is

COMPONENT countx
PORT
(
	clk1 : IN std_logic;
	countx : OUT STD_LOGIC_vector(1 downto 0)
);
end COMPONENT;
COMPONENT county
PORT
(
	clk2 : IN std_logic;
	county : OUT STD_LOGIC_vector(1 downto 0)
);
end COMPONENT;
COMPONENT decodex
PORT
(
x : IN STD_LOGIC_vector(1 downto 0);
out1 : OUT STD_LOGIC_vector(6 downto 0)
);
end COMPONENT;
COMPONENT decodey
PORT
(
	y : IN STD_LOGIC_vector(1 downto 0);
	out2 : OUT STD_LOGIC_vector(6 downto 0)
);
end COMPONENT;
COMPONENT turn_state
PORT
(
        clk : IN std_logic;
        reset : IN std_logic;
        instat : IN STD_LOGIC_vector(1 downto 0);
        outstat : OUT std_logic
);
end COMPONENT;
COMPONENT HitMiss
PORT
(
	hit : IN std_logic;
	hmEN : IN std_logic;
	HMIO : OUT std_logic_vector(1 downto 0)
);
end COMPONENT;
COMPONENT TurnIO
PORT
(
	turnState : IN std_logic;
	turnIO : OUT std_logic_vector(1 downto 0)
);
end COMPONENT;
signal s_countx, s_county : std_logic_vector(1 downto 0);
begin

C1 : countx
PORT MAP(
clk1 => Xtrigger,
countx => s_countx
);

C2 : county
PORT MAP(
clk2 => Ytrigger,
county => s_county
);

D1 : decodex
PORT MAP(
x => s_countx,
out1 => seg1
);

D2 : decodey
PORT MAP(
y => s_county,
out2 => seg2
);

S1 : turn_state
PORT MAP(
clk => CLK,
reset => RST,
instat(1) => ardin,
instat(0) => EndTurn,
outstat => statusout 
);
IO1 : HitMiss
PORT MAP(
hit => HM,
hmEN => HMEnable,
HMIO(0) => HMLED(0),
HMIO(1) => HMLED(1)
);
IO2 : TurnIO
PORT MAP(
turnState => turnIN,
turnIO(0) => TurnLED(0),
turnIO(1) => TurnLED(1)
);


X <= s_countx;
Y <= s_county;

end Behavioral;

