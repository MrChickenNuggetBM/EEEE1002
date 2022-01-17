%the variables included are (initial) velocity, constant acceleration and time (v = u + at)

u = 0; %metres per second
a = 2; %metres per second^2

t = linspace(0,10,101); %seconds
v = u + a*t; %metres per second

plot(t,v,"r") %plots the graph, in red
title("Velocity vs Time"); %adds a title to the graph
xlabel("Time"); %labels the horizontal axis with "Time"
ylabel("Velocity"); % labels the vertical axis with "Velocity"
tmin = 0; % defines the minimum time
tmax = max(t); % defines the maximum time, using the greatest value in t
vmin = 0; % defines the minimum velocity
vmax = max(v); % defines the maximum velocity, using the greatest value in v
axis([tmin tmax vmin vmax]) % defines the horizontal and vertical axes using the above 4 variables