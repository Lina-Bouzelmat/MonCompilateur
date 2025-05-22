VAR
    x : DOUBLE;
    y : DOUBLE.

BEGIN
    // Test avec une seule soustraction
    x := 3.14;
    x := 0.0 - x;    // Autre façon d'obtenir -3.14
    DISPLAY x;       // Devrait afficher -3.14
    
    // Test avec une constante
    y := 2.5;
    y := 0.0 - y;    // Autre façon d'obtenir -2.5
    DISPLAY y        // Pas de point-virgule avant END
END.