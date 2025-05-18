VAR 
    a, b, c : INTEGER;
    x, y : DOUBLE;
    ch1, ch2 : CHAR;
    bool1, bool2 : BOOLEAN.

BEGIN
    // Test des affectations simples
    a := 42;
    x := 3.14;
    ch1 := 'A';
    bool1 := 1;
    
    // Test des opérations arithmétiques simples
    b := 10;
    c := a + b;
    
    // Test des opérations sur les flottants
    y := x;
    
    // Test de la boucle FOR
    FOR a := 1 TO 5 DO
        DISPLAY a;
    
    // Test des affichages
    DISPLAY x;
    DISPLAY ch1;
    DISPLAY bool1
END.