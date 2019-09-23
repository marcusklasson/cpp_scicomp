fun = @(x) 1 + sin(exp(3*x));
I = integral(fun, -1, 1);
fprintf('Integral of f(x) = 1 + sin(exp(3*x)): %2.6f \n', I)
