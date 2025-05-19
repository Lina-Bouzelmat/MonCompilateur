VAR 
    i, j, k : INTEGER;      // Pour les boucles FOR
    x : DOUBLE;             // Pour les calculs flottants
    c : CHAR.               // Pour les caractères

BEGIN
    // Test FOR externe avec entiers
    FOR i := 1 TO 3 DO
    BEGIN
        DISPLAY i;          // Affiche 1, 2, 3

        // FOR imbriqué avec entiers
        FOR j := 1 TO 2 DO
        BEGIN
            DISPLAY j;      // Affiche 1, 2 pour chaque i
            k := i * j;     // Calcul avec entiers uniquement
            DISPLAY k       // Affiche les produits
        END;

        // FOR imbriqué avec caractères (sans mélanger les types)
        FOR k := 1 TO 2 DO
        BEGIN
            c := 'A';       // Initialisation du caractère
            DISPLAY c;      // Affiche A
            c := 'B';       // Nouveau caractère
            DISPLAY c       // Affiche B
        END
    END;

    // Test avec flottants (sans mélange)
    x := 1.5;
    DISPLAY x;             // Affiche 1.500000
    x := x + 1.0;
    DISPLAY x              // Affiche 2.500000
END.