for i = 80:300
    K = i / 10.0;
    sim('Lab3Pre');
    xfinal = x(end);
    upper = xfinal*1.04;
    if max(x) >= upper
        continue
    end
    left = find(x > 0.1*xfinal, 1);
    right = find(x > 0.9*xfinal, 1);
    if t(right) - t(left) < 1.5
        answer = K
        break
    end
end