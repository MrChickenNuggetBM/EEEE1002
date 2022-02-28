%the variables included are (initial) displacement, constant acceleration and time (s = ut + 0.5at^2)

s0 = 0; %metres
u = 0; %metres per second
a = 2; %metres per second^2

t = linspace(0,10,101); %seconds
s = u*t + 0.5*a.*t.*t + s0; %metres

plot(t,s,"r") %plots the graph, in red
title("Displacement vs Time"); %adds a title to the graph
xlabel("Time"); %labels the horizontal axis with "Time"
ylabel("Displacement"); % labels the vertical axis with "Displacement"
tmin = 0; % defines the minimum time
tmax = max(t); % defines the maximum time, using the greatest value in t
smin = min(s); % defines the minimum velocity
smax = max(s); % defines the maximum velocity, using the greatest value in v
axis([tmin tmax smin smax]) % defines the horizontal and vertical axes