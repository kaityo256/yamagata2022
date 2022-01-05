set term pngcairo
set out "revolving.png"

set xlabel "Month"
set ylabel "Number of Payment Times"
unset key
p "revolving.dat" w linespoints pt 6
