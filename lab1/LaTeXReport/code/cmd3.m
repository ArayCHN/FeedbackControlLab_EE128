  L = 0.001; C = 0.001; R = 2;
  num = [1]; den = [L*C, L/R, 1];
  sys = tf(num, den);
  step(sys)