# Calculating the square root using fixed point arithmetics

The racine.m function will illustrate the successive steps of the calculation
by plotting the parabolic function to be solved as $y-x^2=0$ leading to $x=\sqrt{y}$.
This series calculation is implemented as fixed point arithmetic in racine.c relying
on the fixed.{c,h} library.
