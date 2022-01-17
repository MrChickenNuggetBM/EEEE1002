%the variables included are (initial) displacement, constant acceleration and time (s = ut + 0.5at^2)

s0 = 0; %metres
u = 0; %metres per second
a = 2; %metres per second^2
smax = 5; % maximum displacement
tincrement = 0.1;

t = [0]; %seconds
s = [0]; %metres

for m = 1:10/tincrement
    t(end + 1) = m*tincrement; %seconds
    s(end + 1) = u*t(end) + 0.5*a*t(end)*t(end) + s0; %metres

    if max(s) >= smax
        break
    end
end

plot(t,s,"r")
title("Displacement vs Time");
xlabel("Time");
ylabel("Displacement");
tmin = min(t);
tmax = max(t);
smin = min(s);
axis([tmin tmax smin smax])