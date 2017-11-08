  x0 = [0; 0]; tspan = [0, 0.02]; % initial setting
  [t, x] = ode45(@RLCdynamics, tspan, x0); % solve function
  [hAx, hLine1, hLine2] = plotyy(t, x(:, 1), t, x(:, 2));
  hLine2.LineStyle = '--'; % change line style
  title('Graph of x - t') % title, label, legend
  xlabel('t / s')
  ylabel(hAx(1),'i / A') % left y-axis 
  ylabel(hAx(2),'v_c / V') % right y-axis
  legend('i','v_c')