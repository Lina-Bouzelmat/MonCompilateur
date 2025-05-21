VAR 
    i : INTEGER;
    c : CHAR.
BEGIN
    // Test CASE avec entiers
    i := 2;
    CASE i OF
        1: DISPLAY 10;
        2: DISPLAY 20;
        3: DISPLAY 30
    END;

    // Test CASE avec caractères
    c := 'B';
    CASE c OF
        'A': DISPLAY 'X';
        'B': DISPLAY 'Y';
        'C': DISPLAY 'Z'
    END;

    // Test CASE imbriqué
    i := 1;
    CASE i OF
        1: BEGIN
            DISPLAY i;
            CASE c OF
                'B': DISPLAY 'Y'
            END
           END;
        2: DISPLAY 2
    END
END.