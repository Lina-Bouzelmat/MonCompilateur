[a, b, x, y, z]

a := 5;
b := 10;
x := 0;
y := 1;

BEGIN
    x := x + 1;
    y := y + 2;
    IF x < 10 THEN
        BEGIN
            z := x + y;
        END;
    ELSE
        BEGIN
            z := x - y;
        END;
    WHILE x < 10 DO
        BEGIN
            x := x + 1;
            y := y + 1;
        END;
    FOR i := 1 TO 5 DO
        BEGIN
            z := z + i;
        END;
    z := x + y;
END.
