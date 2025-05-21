CONST
    PI = 3.14159;     // Test constante flottante
    MAX = 100;        // Test constante entière
    VRAI = TRUE;      // Test constante booléenne
    FAUX = FALSE;     // Test constante booléenne
    CH = 'A';         // Test constante caractère.

VAR
    i, j, k : INTEGER;
    x, y : DOUBLE;
    b : BOOLEAN;
    c : CHAR.

BEGIN
    i := 5;          
    DISPLAY i;        // Affiche 5
    
    x := PI;         
    DISPLAY x;        // Affiche 3.14159
    
    b := VRAI;    
    DISPLAY b;        // Affiche -1 (TRUE)
    
    c := CH;
    DISPLAY c;        // Affiche 'A'

    FOR i := 1 TO 3 DO
    BEGIN
        DISPLAY i     // Affiche 1, 2, 3
    END;

    i := 2;
    CASE i OF
        1: x := 1.5;
        2: x := 2.5;
        3: x := 3.5
    END;
    DISPLAY x         // Affiche 2.5
END.