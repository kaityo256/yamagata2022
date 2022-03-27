set term pngcairo
set out "simple.png"

set xlabel "K"
set ylabel "U"

V=10*10
f(x) = -2*V*exp(x)/(2*V*exp(x) + V*(V-5)/2)
unset key
p [0:10] f(x), "simple.dat" u 1:2:4 w e 
