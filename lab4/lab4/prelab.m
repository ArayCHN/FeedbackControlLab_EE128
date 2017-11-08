s1=[];s2=[];
for i = 10:500
    Kd = i/10.0;
    sim('Pre4');
    xfinal = x(end);
    upper = xfinal*1.08;
    if max(x) >= upper
        continue
    end
    left = find(x > 0.1*xfinal, 1);
    right = find(x > 0.9*xfinal, 1);
    if t(right) - t(left) <= 0.2
        answer = [answer Kd];
        %break
    end
%     delta = sqrt(8.097^2-4.512*(0.9886+1.8097*K));
%     s1 = [s1, (delta-8.1)/2.26];
%     s2 = [s2, (-delta-8.1)/2.26];
end