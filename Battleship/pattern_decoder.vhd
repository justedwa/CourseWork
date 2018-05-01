

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

library UNISIM;
use UNISIM.VComponents.all;


entity pattern_decoder is
Port (
        clk : IN std_logic;
        reset : IN std_logic;
        ain : IN STD_LOGIC_vector(1 downto 0);
        flag : OUT std_logic );
end pattern_decoder;


architecture Behavioral of pattern_decoder is
type state_type is (S0, S1, S2, S3);
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
                flag <= '0';
        when S1 =>
                flag <= '0';
        when S2 =>
                flag <= '1';
        when S3 =>
                flag <= '1';
        when others =>
                flag <= '0';
end case;
end process;


NEXT_STATE_DECODE : process (state, ain)
begin
next_state <= S0;
case (state) is

        when S0 =>
        if (ain = "11" or ain = "10") then
            next_state <= ;
        else next_state <= ;
        end if;

        when S1 =>
        if (ain = "00") then
            next_state <= ;
        elsif(ain = "11" or ain = "10") then
        next_state <= ;
        else next_state <= ;
        end if;

        when S2 =>
        if(ain = "01" or ain = "10") then
            next_state<= ;
        else next_state <= ;
        end if;
        
        when S3 =>
        if (ain = "11") then
            next_state <= ;
        elsif (ain = "00") then
                next_state <= ;
        else next_state <= ;
        end if;
        
        when others =>  
            next_state <= S0;

end case;
end process;
end Behavioral;