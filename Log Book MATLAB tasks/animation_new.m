% this software models the motion of a ball as it is free falling
% Assumptions:
    % there are no (neglegible) resistive forces
    % the cor, between the ball ground, is constant for each collision

%
% fixed constants
g = -9.81; % (metres per second, squared) acceleration due to gravity
end_time = 10; % (seconds) time to stop the motion
t_step = 0.01; % (seconds) the interval between each time value

%
% user-inputted constants
cor = input("What coefficient of restitution would you like?\n"); % (between 0 and 1) this is the coefficient of restitution
initial_height = input("What initial height would you like?\n"); % (metres) this is the height at time = 0
initial_velocity = input("What initial velocity would you like?\n"); % (metres per second) this is the velocity at time = 0

%
% main code
tArray = []; % (seconds) this is an array containing all the time values since the start of the motion
sArray = []; % (metres) this is an array containing all the displacement values since the start of the motion
vArray = []; % (metres per second) this is an array containing all the velocity values since the start of the motion

v = initial_velocity; % (metres per second) the velocity at each loop cycle
s = initial_height; % (metres) the displacement at each loop cycle

tArray(1) = 0;
sArray(1) = s;
vArray(1) = v;

count = 2; % this is a count, storing the loop count as an integer

% runs the loop for every time interval in the range
for t = 0:t_step:end_time
    tic;

    % finds the next velocity and displacement
    v = v + g*t_step;
    s = s + t_step * ((vArray(end) + v) / 2);

    % if the displacement is below the ground, BOUNCE!!!
    if s <= 0
        v = -cor * v;
        s = 0;
    end

    % puts each of the values into its array, for this loop iteration
    tArray(count) = t;
    sArray(count) = s;
    vArray(count) = v;

    % plots the motion so far, then the ball
    plot(tArray, sArray)
    hold on;
    plot(t, s, "r o","MarkerSize", 5)
    hold off;

    axis([0 end_time 0 initial_height]);
    title(strcat("Displacement-Time; COR = ", num2str(cor), "; g = ", num2str(g)));
    xlabel("Time (seconds)");
    ylabel("Displacement from ground (metres)");
    legend("Motion so far", "Current position");

    %increments the count, then pauses for a period
    count = count + 1;
    pause_time = t_step - toc;
    pause_time = max(0,pause_time)
    pause(pause_time);
end