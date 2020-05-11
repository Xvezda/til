# SELinux

## Policy Rules

Define label on process and file system object by its type.

`ALLOW process_label file_system_object_lable JOB `

SELinux system deny everything by default.


## MCS Enforcement

MCS: Multi Category Security

Creating new types for every process is such a mess. That's where MCS comes in.

`Type enforcement == OK && MCS Label == MATCH  # ALLOWED`


## MLS Enforcement

MLS: Multi Level Security

Control processes based on level. Can make some level to dominates other label.


## Reference
 - The SELinux coloring book - Dan Walsh
