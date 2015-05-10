% CSUPER-CLI(1) Csuper-cli User Manuals
% Rémi BERTHO
% April 25, 2015

# NAME

csuper-cli - Universal points counter allowing a dispense with reflection

# SYNOPSIS

csuper-cli [*options*] [*input-file*]

# DESCRIPTION

This software allow you to count points easily with a computer. It is a CLI of csuper.

If no *input-file* or no *options* is specified, the software open with a menu.

You can only use on option.

The software can only use csu file.

# OPTIONS

-o *input-file*, \--open *input-file*
:   Open directly a file in csuper-cli.

-r *input-file*, \--read *input-file*
:   Read directly a file in csuper-cli.

-p *input-file* *output-file*, \--to-pdf *input-file* *output-file*
:   Convert the *input-file* into the pdf file named *output-file*.

-c *input-file* *output-file*, \--to-csv *input-file* *output-file*
:   Convert the *input-file* into the csv file named *output-file*.

-h, \--help
:   Display the help of csuper-cli

# SEE ALSO

`csuper-gui` (1)

The source code of in available on <https://git.framasoft.org/Dalan94/Csuper>.
The executable in available on <http://www.dalan.rd-h.fr/wordpress/>