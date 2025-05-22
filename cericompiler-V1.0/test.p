VAR
     c, b, a, x, y, z : DOUBLE.

BEGIN
    // Tests avec des entiers
    a := 10.0;
    b := 15.0;
    c := a - b;        // Obtenir -5 par soustraction
    DISPLAY c;         // Devrait afficher -5
    
    // Tests avec des flottants
    x := 3.14;
    y := 5.0;
    z := x - y;        // Obtenir -1.86 par soustraction
    DISPLAY z;         // Devrait afficher -1.86
    
    // Test avec une chaîne d'opérations
    x := 10.5;
    y := 7.3;
    z := x - (y + 5.0);  // Soustraction complexe : 10.5 - (7.3 + 5.0) = -1.8
    DISPLAY z;           // Devrait afficher -1.8
    
    // Test avec multiplication et soustraction
    a := 2.0;
    b := 3.0;
    c := a * (b - 5);   // 2 * (3-5) = 2 * (-2) = -4
    DISPLAY c           // Devrait afficher -4
END.