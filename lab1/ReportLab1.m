%% ME C134 Lab1 Report
% Rui Wang 3033461836
%% General Problem
% Given the simple RLC circuit as shown below, we can derive its tranfer
% function as well as state space representation.
%%
% 
% <<FILENAMEofCircuit.PNG>>
%
% In this problem, we define $v(t)$ as the input, $i(t)$ and $v_c(t)$ as 
% system states, and $v_c(t)$ as the output
% Applying Kirchoff's law (specifically, KVL), we obtain the following 
% equations:
% $$\left\{
%        \begin{array}{ll}
%           L\frac{di(t)}{dt} + v_c(t) + v(t) = 0 (1)\\
%           (i(t) - C\frac{dv_c}{dt})R = v_c (2)
%        \end{array}
% \right.$$
% Differentiate both sides of (2), and we get 
% 
% $$\dot{i} = \frac{\dot{v_c}}{R} + C\ddot{v_c} (3)$$
% 
% Substitute (3) into (1), and we obtain
%
% $$L(\frac{\dot{v_c}}{R} + C\dot{v_c}) + v_c - v = 0 (4)$$
%
% Therefore, the transfer function turns out to be 
%
% $$F(s) = \frac{1}{LCs^2 + \frac{L}{R}s + 1}$$
%
% Also, rearrange the equations (1) and (4) in the form of $\dot{X} = AX +
% Bu$, with $X = [i v_c]^T$ and $u = v$, and $Y = CX + D$, with $Y = v_c$,
% we obtain the following values for parameters $A, B, C$ and $D$.
% Namely, we have
%
% $$
% \left \{
%   \begin{tabular}{cc}
%   0 & -\frac{1}{L} \\
%   \frac{1}{C} & -\frac{1}{RC}
%   \end{tabular}
% \right \}
% $$
%
% $B = [\frac{1}{L}, 0]^T$, $C = [0, 1]$, $D = 0$
%
% $$ 
% \left \{
%   \begin{tabular}{ccc}
%   1 & 5 & 8 \\
%   0 & 2 & 4 \\
%   3 & 3 & -\frac{1}{L}
%   \end{tabular}
% \right \}
% $$

x0 = [0; 0]; tspan = [0, 0.02]; % initial setting
[t, x] = ode45(@RLCdynamics, tspan, x0);
plot(t, x(:, 1));
title('Graph of x - t'); xlabel('t'); ylabel('x');
hold on
plot(t, x(:, 2));
hold off
%% Simulate by MATLAB Built-in ODE Solver
A = [0, -1/L; 1/C, -1/R/C]; B = [1/L; 0]; C = [0, 1]; D = 0;
RLCss = ss(A, B, C, D);
step(RLCss);
%%
L = 0.001; C = 0.001; R = 2;
num = [1]; den = [L*C, L/R, 1];
sys = tf(num, den)
step(sys)
%%
% 
%   for x = 1:10
%       disp(x)
%   end
% 
% <include>RLCdynamics.m</include>
