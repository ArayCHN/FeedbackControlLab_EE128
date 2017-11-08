clear
% Kp = 100;
KD = 10;

qc_build_model;
qc_connect_model;
qc_start_model;

pause(20)
% plot(time,simout);
xss = simout(end);
xr1=find(simout>0.1*xss,1);
xr2=find(simout>0.9*xss,1);
Tr = time(xr2)-time(xr1)
Overshoot = ((norm(simout,inf)-simout(end,1))/simout(end,1))*100

save simout simout
save time time

