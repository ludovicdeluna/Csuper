% CSUPER-CLI(1) Csuper-cli User Manuals
% Rémi BERTHO
% July 9, 2015

# NAME

csuper-cli - Universal points counter allowing a dispense with reflection

# SYNOPSIS

csuper-cli [*options*]

# DESCRIPTION

This software allow you to count points easily with a computer. It is a CLI of csuper.

If an instruction is set, a input filename is needed.

If a "to" instruction is set, an output filename is needed.

You can use only one instruction at once.

The software can only open csu file.

# OPTIONS

-i *input-file*, \--input *input-file*
:   Set the input filename

-o *output-file*, \--output *output-file*
:   Set the output filename

-r , \--read
:   Read directly a file in csuper-cli.

-e , \--open
:   Open directly a file in csuper-cli.

-p , \--to-pdf
:   Convert the *input-file* into the PDF file named *output-file*.

-c, \--to-csv
:   Convert the *input-file* into the CSV file named *output-file*.

-g , \--to-gnuplot
:   Convert the *input-file* into the gnuplot files named *output-file*.plt and *output-file*.dat.

-m , \--to-matlab 
:   Convert the *input-file* into the m file (octave/matlab file) named *output-file*.

-n , \--to-png
:   Convert the *input-file* into the PNG file named *output-file*.

-s , \--to-svg
:   Convert the *input-file* into the SVG file named *output-file*.

-h, \--help
:   Display the help of csuper-cli

# SEE ALSO

`csuper-gui` (1)

The source code of in available on <https://git.framasoft.org/Dalan94/Csuper>.

The executable in available on <http://www.dalan.rd-h.fr/wordpress/>