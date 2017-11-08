  A = [0, -1/L; 1/C, -1/R/C]; B = [1/L; 0]; C = [0, 1]; D = 0;
  % parameter configuration
  RLCss = ss(A, B, C, D);
  step(RLCss);