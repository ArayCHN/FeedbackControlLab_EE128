Q = [1/0.3^2 0 0 0; 0 0 0 0; 0 0 1/0.05^2 0; 0 0 0 0];
R=90/6^2;
A = [0 1 0 0;0 -6.81 -1.5 0; 0 0 0 1; 0 15.47 25.66 0];
B = [0;1.52;0;-3.46];
C = [1 0 0 0;0 0 1 0];D = [0; 0];
sys = ss(A,B,C,D);
K = lqr(sys, Q, R)
%%
sim('prelab')
%%
plot(time1(:), u(:));
title('u-t evolution')
%%
figure
plot(time1(:), X(:, 1));
hold on
plot(time1(:), X(:, 3));
legend('x', '\theta');
title('y-t evolution')
%%
xmax = max(abs(X(:, 1)))
thetamax = max(abs(X(:, 3)))
umax = max(u)
eig(A-B*K) % eigen values, C.L. poles