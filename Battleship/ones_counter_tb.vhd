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
 
ENTITY ones_counter_tb IS
END ones_counter_tb;
 
ARCHITECTURE behavior OF ones_counter_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT ones_counter
    PORT(
         clk : IN  std_logic;
         reset : IN  std_logic;
         input_ext : IN  std_logic;
         flag : OUT  std_logic
        
        );
    END COMPONENT;
    

   --Inputs
   signal clk : std_logic := '0';
   signal reset : std_logic := '0';
   signal input_ext : std_logic := '0';

 	--Outputs
   signal flag : std_logic;
   

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: ones_counter PORT MAP (
          clk => clk,
          reset => reset,
          input_ext => input_ext,
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
      wait for 100 ns;	
  reset<='0';
      wait for clk_period*10;

      -- insert stimulus here 
      input_ext<='1';
      wait for clk_period*10;
            input_ext<='1';
            wait for clk_period*10;
                        input_ext<='0';
                  wait for clk_period*10;
                                    input_ext<='1';
                        wait for clk_period*10;
                                                input_ext<='0';
                              wait for clk_period*10;
                                                            input_ext<='0';
                                    wait for clk_period*10;
                                                                        input_ext<='1';
                                          wait for clk_period*10;
      

      wait;
   end process;

END;
