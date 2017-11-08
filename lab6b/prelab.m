%% 3.1 Controllability & Observability
A = [0 1 0 0; 0 -6.81 -1.5 0; 0 0 0 1; 0 15.47 25.66 0];
B = [0; 1.52; 0; -3.46];
C = [1 0 0 0; 0 0 1 0];
Co = ctrb(A, B);
rCo = rank(Co);
Ob = obsv(A, C);
rOb = rank(Ob);

%% 3.2
p = [-10+15i -10-15i -12+17i -12-17i];
LT = place(A', C', p);
L = LT';

%% 3.3 plot
plot(tout, X(:, 1));hold on; plot(tout, Xest(:, 1));legend('x','x_{observer}');title('x-t VS x_{obsv}-t');
fig('2');
plot(tout, X(:, 2));hold on; plot(tout, Xest(:, 2));legend('xdot','xdot_{observer}');title('xdot-t VS xdot_{obsv}-t');
fig('3');
plot(tout, X(:, 3));hold on; plot(tout, Xest(:, 3));legend('\theta','\theta_{observer}');title('\theta-t VS \theta_{obsv}-t');
fig('4');
plot(tout, X(:, 4));hold on; plot(tout, Xest(:, 4));legend('\omega','\omega_{observer}');title('\omega-t VS \omega_{obsv}-t');

hold off
Xerr = Xest-X;
plot(tout, Xerr(:, 1));title('x error - t');
fig('2');
plot(tout, Xerr(:, 2));title('xdot error - t');
fig('3');
plot(tout, Xerr(:, 3));title('\theta error - t');
fig('4');
plot(tout, Xerr(:, 4));title('\omega error - t');