--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   20:35:54 11/24/2014
-- Design Name:   
-- Module Name:   C:/Users/shvyas/270/temp/ones_counter_tb.vhd
-- Project Name:  temp
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: ones_counter
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY pattern_decoder_tb IS
END pattern_decoder_tb ;
 
ARCHITECTURE behavior OF pattern_decoder_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT pattern_decoder
    PORT(
         clk : IN  std_logic;
         reset : IN  std_logic;
         ain : IN  STD_LOGIC_vector(1 downto 0);
         flag : OUT  std_logic
        
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal reset : std_logic := '0';
  
 	--Outputs
   signal flag : std_logic;
  signal ain: std_logic_vector(1 downto 0):="00";

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: pattern_decoder PORT MAP (
          clk => clk,
          reset => reset,
          ain => ain,
          flag => flag
          
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      reset<='1';
      ain<="00";
      wait for 20 ns;	
  reset<='0';
     

      -- insert stimulus here 
       
      wait for clk_period*2;
           ain<="00";
         wait for clk_period*2;
               ain<="11";
         wait for clk_period*1;
                   ain<="10";
         wait for clk_period*1;
                  ain<="00";
          wait for clk_period*2;
              ain<="10";
           wait for clk_period*1;
               ain<="00";
           wait for clk_period*1;
               ain<="11";
           wait for clk_period*1;
               ain<="00";         
          wait for clk_period*1;
              ain<="01";
          wait for clk_period*1;
              ain<="00";
        wait for clk_period*1;
                ain<="10";         
           wait for clk_period*1;
               ain<="11";
           wait for clk_period*1;
               ain<="00";                                   
              
      

      wait;
   end process;

END;
