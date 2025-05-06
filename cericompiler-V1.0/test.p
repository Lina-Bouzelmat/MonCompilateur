[a, b, c]

a := 0;
b := 3;
c := 0;

IF b > a THEN
    a := b + 1;
ELSE
    a := 1;

BEGIN
    WHILE a < 6 DO
        a := a + 1;

    FOR c := 1 TO 3 DO
        b := b + 1
END.
