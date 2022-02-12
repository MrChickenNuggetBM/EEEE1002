g = -9.81; %ms^-2
totaltime = 10; %s
timestep = 0.5; %s
initialdisplacement = 10;
timefloor = 0;
cycle = 0;
max = 1;
changefactor = 0.6;

for frame = 1:((totaltime/timestep)+1)
    time = (frame-1)*timestep;
    height = (0.5*g*(time-timefloor)*(time-timefloor) + initialdisplacement)*max;
    plot(time,height,'ro');
    axis equal;
    axis([0,totaltime,0,initialdisplacement*max]);
    M(frame) = getframe(gcf);
    if height <= 0
        if cycle == 0
            halfcycle = time;
        end
        halfcycles = 2*cycle + 2;
        cycle = cycle + 1;
        timefloor = halfcycles*halfcycle;
        max = changefactor*max;
    end
end