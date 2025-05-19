VAR 
    i : INTEGER.
BEGIN
    // Test TO avec STEP
    FOR i := 0 TO 10 STEP 2 DO
        DISPLAY i;
        
    // Test DOWNTO
    FOR i := 5 DOWNTO 1 DO
        DISPLAY i;
        
    // Test DOWNTO avec STEP
    FOR i := 100 DOWNTO 0 STEP 25 DO
        DISPLAY i
END.