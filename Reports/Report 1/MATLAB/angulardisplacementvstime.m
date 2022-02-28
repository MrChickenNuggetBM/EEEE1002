%the variables included are (initial) displacement, constant acceleration and time (s = ut + 0.5at^2)

s0 = 0; %metres
u = 0;
a = 0.5; %metres per second^2
smax = 90;
tincrement = 0.1;

t = [0]; %seconds
s = [0]; %metres

for m = 1:(360/tincrement)
    t(end + 1) = m*tincrement; %seconds
    s(end + 1) = u*t(end) + 0.5*a*t(end)*t(end) + s0; %metres
    if max(s) >= smax
        break
    end
end

%s=mod(s,360);

plot(t,s,"r")
title("Angular Displacement vs Time");
xlabel("Time");
ylabel("Angular Displacement");
tmin = min(t);
tmax = max(t);
smin = min(s);
axis([tmin tmax smin smax])