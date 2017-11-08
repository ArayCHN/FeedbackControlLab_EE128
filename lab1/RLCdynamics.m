function xdot = RLCdynamics(t, x)
  L = 0.001;
  C = 0.001;
  R = 2;
  xdot = [0, -1/L; 1/C, -1/R/C] * x + [1/L, 0]'*1;
end