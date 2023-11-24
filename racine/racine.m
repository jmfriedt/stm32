close all
format long

function sol=trace(x0)
  x=[x0-7:0.1:x0+8];
  fx0=100-x0*x0;
  fpx0=-2*x0;
  plot(x,fx0+fpx0*(x-x0)) % commence en x1=5 : solution 
  sol=x0-fx0/fpx0;
end

subplot(121)
x=[-1:0.1:19];
plot(x,100-x.^2) 
hold on          

xn=5; 
for k=1:4
   xn=trace(xn)
end
grid on
axis tight
xlabel('x')
ylabel('y')
xlim([-1 19])
