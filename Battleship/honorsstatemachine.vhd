----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    21:25:32 04/29/2017 
-- Design Name: 
-- Module Name:    test - Behavioral 
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
use IEEE.NUMERIC_STD.ALL;

library UNISIM;
use UNISIM.VComponents.all;


entity turn_state is
Port (
        clk : IN std_logic;
        reset : IN std_logic;
        instat : IN STD_LOGIC_vector(1 downto 0);
        outstat : OUT std_logic );
end turn_state;


architecture Behavioral of turn_state is
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

OUTPUT_DECODE : process (state)
begin
case (state) is
        when S0 =>
                outstat <= '0';
        when S1 =>
                outstat <= '0';
        when S2 =>
                outstat <= '1';
        when others =>
                outstat <= '0';
end case;
end process;


NEXT_STATE_DECODE : process (state, instat)
begin
next_state <= S0;
case (state) is

        when S0 =>
        if (instat = "00" or instat = "01") then
            next_state <= S0;
        else next_state <= S1;
        end if;

        when S1 =>
        if (instat = "00" or instat = "10") then
            next_state <= S1;
        elsif(instat = "11") then
        next_state <= S0;
        else next_state <= S2;
        end if;

        when S2 =>
        if(instat = "00" or instat = "01") then
            next_state<= S2;
        else next_state <= S1;
        end if;
                
        when others =>  
            next_state <= S0;

end case;
end process;
end Behavioral;



