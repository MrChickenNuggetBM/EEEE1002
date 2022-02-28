%the variables included are (initial) displacement, constant acceleration and time (s = ut + 0.5at^2)

s0 = 0; %metres
u = 0; %metres per second
a = 2; %metres per second^2
v = a*0.5; %this the velocity when time = 0.5 (when linear velocity begins)
smax = 5; %the maximum displacement we are modelling for
tincrement = 0.1; %the time increment from which we are measuring

t = linspace(0,0.5,6); %generates the the first set of t values, for the acceleration part
s = u*t + 0.5*a.*t.*t; %generates the displacement for these first set of values

slin0 = s(end); %the displacment achieved at the end of linear acceleration

for m = 6:(10/tincrement)
    t(end + 1) = m*tincrement; %seconds %generates a time at the increment
    s(end + 1) = v*t(end) - slin0; %metres % finds the displacement at that time (considering the displacement already travelled)

    if max(s) >= smax %breaks the loop when the maximum displacement is achieved
        break
    end
end

%plots the graphs
plot(t,s,"r")
title("Displacement vs Time");
xlabel("Time");
ylabel("Displacement");
tmin = min(t);
tmax = max(t);
smin = min(s);
axis([tmin tmax smin smax])