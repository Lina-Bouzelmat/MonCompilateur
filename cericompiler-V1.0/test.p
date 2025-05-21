VAR 
    x : DOUBLE;
    i, j, k : INTEGER;
    c : CHAR.

BEGIN
    // Test des boucles FOR imbriquées avec STEP
    FOR i := 1 TO 3 DO
    BEGIN
        DISPLAY i;
        FOR j := 10 DOWNTO 6 STEP 2 DO
        BEGIN
            DISPLAY j;
            k := i * j;
            DISPLAY k
        END;
        
        // Test CASE dans FOR
        CASE i OF
            1: k := 100;
            2: k := 200;
            3: k := 300
        END;
        DISPLAY k
    END;

    // Test WHILE dans FOR
    i := 0;
    FOR j := 1 TO 3 DO
    BEGIN
        WHILE i < 3 DO
        BEGIN
            DISPLAY i;
            i := i + 1;
            // Test CASE dans WHILE
            CASE i OF
                1: DISPLAY 11;
                2: DISPLAY 22;
                3: DISPLAY 33
            END
        END;
        DISPLAY j
    END;

    // Test caractère dans WHILE avec CASE
    c := 'A';
    WHILE c <= 'C' DO
    BEGIN
        DISPLAY c;
        CASE c OF
            'A': DISPLAY 65;
            'B': DISPLAY 66;
            'C': DISPLAY 67
        END;
        c := c + 'B' - 'A'
    END;

    // Test final avec conversion INTEGER vers DOUBLE
    x := 3.14;
    i := 2;
    x := x * i;     // Conversion automatique
    DISPLAY x;      // Devrait afficher 6.28
    
    x := 2.5;
    i := 3;
    x := x + i;     // Autre conversion
    DISPLAY x       // Devrait afficher 5.5
END.