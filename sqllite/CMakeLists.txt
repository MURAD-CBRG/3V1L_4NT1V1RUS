set(sqlfiles
        shell.c
        sqlite3.c
        sqlite3.h
        sqlite3ext.h
        )
add_library(sqlib ${sqlfiles})