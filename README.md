# Lax

Operations:
    
    add     (adds value to cell)
    sub     (subtracts value from cell)
    movr    (shift active cell to the right)
    movl    (shift active cell to the left)
    set     (set cell to a value)
    print   (print current value of cell)
    get     (get input and save to cell)
    while   (loop while cell current cell is not 0)
    end     (end loop)
    ret     (end function)
    inc     (increment cell by 1)
    dec     (decrament cell by 1)
    write   (write chunk of memory)
    call    (call function)

Constants:
    
    Either direct values (such as 2) or character values (such as 'b' with the single quotes)

Math:
    
    Allows addition, subtraction, mutliplication, and devision
    Example:
        12 + 'a'
        'b' - 1
        5 * 3
        6 / 2
        7 * 2 + 3
    Note:
        There is NO ORDER OF OPERATIONS
        Statements are evaluated from left to right
        Example:
            7 + 3 * 4 is 40 NOT 19
        Negatives are RECOMMENDED only to be used alone
        Example:
            add -5          [works]
            add -5 * 3      [works]
            add 3 * -5 + 2  [fails]

Strings:
    
    Used by the write operation
    There are long string using ""
    Characters using ''
    And direct values using just the number
    There are seperated by ','
    The only excape is \" used in long string
    Example:
        write "Hello \"world\"", '!', 10
        Creates this c style string "Hello \"world\"!\n"

Functions:
    
    Definition is done with "def name"
    Non-recursive (think of it more like an inline or macro)
    Example:
        def hello:
            write "Hello world!", 10
            while:
                print;
                movr 1;
            end;
        ret;

        call hello;
