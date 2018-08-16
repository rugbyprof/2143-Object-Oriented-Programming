{
	Billiard Simulation Program
	To demonstrate features of OOP in Object Pascal
	Written by Tim Budd, September 1995
}
Program billiards;

USES
  Windows;

type
	Ball = object
			{ data values maintained by balls }
		link : Ball;
		region : Rect;
		filler : integer;
		direction : real;
		energy : real;
		
				{ initialization routine }
		procedure initialize (x, y : integer);

			{ common methods }
		procedure draw;
		procedure erase;
		procedure update;
		procedure hitBy (aBall : Ball);
		procedure setCenter (newx, newy : integer);

			{ return x, y coordinate center of ball }
		function x : integer;
		function y :integer;
	end;

	Wall = object 
				{ data fields }
			link : Wall;
			region : Rect;
				{ factor used to reflect striking balls }
			convertFactor : real;
			
				{ initialization function }
			procedure initialize (left, top, right, bottom : integer; cf : real);

				{ draw wall }
			procedure draw;

				{ notify wall that a ball has struck }
			procedure hitBy (aBall : Ball);
		end;

	Hole = object
				{ data fields }
			link : Hole;
			region : Rect;
			
				{ initialize location of hole }
			procedure initialize (x, y : integer);

				{ draw the hole }
			procedure draw;

				{ notify hole that it has received a ball }
			procedure hitBy (aBall : Ball);
		end;

	var
		cueBall : Ball;
		saveRack : integer;
		ballMoved : boolean;
		listOfHoles : Hole;
		listOfWalls : Wall;
		listOfBalls: Ball;

		theWindow : windowPtr;
		
procedure Wall.initialize (left, top, right, bottom : integer; cf : real);
begin
		{ initialize convertion factor }
	convertFactor := cf;
	
		{ set up region for wall }
	SetRect (region, left, top, right, bottom);
end;

procedure Wall.draw;
begin
	PaintRect (region);
end;

procedure Wall.hitBy (aBall : Ball);
begin
		{ bounce the ball off the wall }
	aBall.direction := convertFactor - aBall.direction;
end;

procedure Hole.initialize (x, y : integer);
var left, top, bottom, right : integer;
begin
		{ identify region centered around x, y }
	left := x - 5;
	top := y - 5;
	right := x + 5;
	bottom := y + 5;
	SetRect (region, left, top, right, bottom);
end;

procedure Hole.draw;
begin
	PaintOval (region);
end;

procedure Hole.hitBy (aBall : Ball);
begin
		{ drain enery from ball }
	aBall.energy := 0.0;
	aBall.erase;

		{ move ball }
	if aBall = CueBall then
		aBall.setCenter(50, 100)
	else begin
		saveRack := saveRack + 1;
		aBall.setCenter (10 + saveRack * 15, 250);
	end;

	{ redraw ball }
	aBall.draw;
end;

procedure Ball.setCenter (newx, newy : integer);
var left, top, bottom, right : integer;
begin
		{ identify region centered around x, y }
	left := newx - 5;
	top := newy - 5;
	right := newx + 5;
	bottom := newy + 5;
	SetRect (region, left, top, right, bottom);
end;

procedure Ball.initialize (x, y : integer);
begin
	setCenter(x, y);
	direction := 0.0;
	energy := 0.0;
end;

procedure Ball.erase;
begin
	EraseRect (region);
end;

procedure Ball.draw;
begin
	if self = CueBall then
		FrameOval (region)
	else
		PaintOval (region)
end;

procedure Ball.update;
var
	hptr : Hole;
	wptr : Wall;
	bptr : Ball;
	dx, dy : integer;
	theIntersection : Rect;
	i : integer;
begin
	if energy > 0.5 then begin
		ballMoved := true;
			{ erase ball }
		erase;
			{ decrease energy }
		energy := energy - 0.05;
			{ move ball }
		dx := trunc(5.0 * cos(direction));
		dy := trunc(5.0 * sin(direction));
		offsetRect(region, dx, dy);
			{ redraw ball }
		for i := 1 to 25 do
		draw;
		
			{ see if we hit a hole }
		hptr := listOfHoles;
		while (hptr <> nil) do
			if SectRect(region, hptr.region, theIntersection) then begin
				hptr.hitBy(self);
				hptr := nil;
			end
			else
				hptr := hptr.link;

			{ see if we hit a wall }
		wptr := listOfWalls;
		while (wptr <> nil) do
			if SectRect(region, wptr.region, theIntersection) then begin
				wptr.hitBy(self);
				wptr := nil;
			end
			else
				wptr := wptr.link;

			{ see if we hit a ball }
		bptr := listOfBalls;
		while (bptr <> nil) do
			if (bptr <> self) and SectRect(region, bptr.region, theIntersection) then begin
				bptr.hitBy(self);
				bptr := nil;
			end
			else
				bptr := bptr.link;
	end;
end;

function Ball.x :integer;
begin
	x := (region.left + region.right) div 2;
end;

function Ball.y : integer;
begin
	y := (region.top + region.bottom) div 2;
end;

function hitAngle (dx, dy : real) : real;
	const
		PI = 3.14159;
	var
		na : real;
begin
	if (abs(dx) < 0.05) then
		na := PI / 2
	else
		na := arctan (abs(dy / dx));
	if (dx < 0) then
		na := PI - na;
	if (dy < 0) then
		na := - na;
	hitAngle := na;
end;

procedure Ball.hitBy (aBall : Ball);
var
	da : real;
begin
		{ cut the energy of the hitting ball in half }
	aBall.energy := aBall.energy / 2.0;

		{ and add it to our own }
	energy := energy + aBall.energy;

		{ set our new direction }
	direction := hitAngle(self.x - aBall.x, self.y - aBall.y);

		{ and set the hitting balls direction }
	da := aBall.direction - direction;
	aBall.direction := aBall.direction + da;
	
		{ continue our update }
	update;
end;

procedure mouseButtonDown (x, y : integer);
var
	bptr : Ball;
begin
		{ give the cue ball some energy }
	cueBall.energy := 20.0;
		{ and a direction }
	cueBall.direction := hitAngle (cueBall.x - x, cueBall.y - y);

		{ then loop as long as called for }
	ballMoved := true;
	while ballMoved do begin
		ballMoved := false;
		bptr := listOfBalls;
		while bptr <> nil do begin
			bptr.update;
			bptr := bptr.link;
			end;
		end;
end;

procedure createGlobals;
var
	i, j : integer;
	newBall : Ball;
	newWall : Wall;
	newHole : Hole;
begin
	saveRack := 0;
	listOfWalls := nil;
	listOfHoles := nil;
	listOfBalls := nil;
		
			{ create walls }
	new (newWall);
	newWall.initialize(10, 10, 300, 15, 0.0);
	newWall.link := listOfWalls;
	listOfWalls := newWall;
	new (newWall);
	newWall.initialize(10, 200, 300, 205, 0.0);
	newWall.link := listOfWalls;
	listOfWalls := newWall;
	new (newWall);
	newWall.initialize(10, 10, 15, 200, 3.14159);
	newWall.link := listOfWalls;
	listOfWalls := newWall;
	new (newWall);
	newWall.initialize(300, 10, 305, 205, 3.14159);
	newWall.link := listOfWalls;
	listOfWalls := newWall;
	
			{ creat holes }
	new(newHole);
	newHole.initialize(15, 15);
	newHole.link := listOfHoles;
	listOfHoles := newHole;
	new(newHole);
	newHole.initialize(15, 200);
	newHole.link := listOfHoles;
	listOfHoles := newHole;
	new(newHole);
	newHole.initialize(300, 15);
	newHole.link := listOfHoles;
	listOfHoles := newHole;
	new(newHole);
	newHole.initialize(300, 200);
	newHole.link := listOfHoles;
	listOfHoles := newHole;
	
			{ create balls }
	new (cueBall);
	cueBall.initialize(50, 96);
	listOfBalls := cueBall;
	
	for i := 1 to 5 do
		for j := 1 to i do
			begin
				new(newBall);
				newBall.initialize(190 + i * 8,
					100 + 16 * j - 8 * i);
				newBall.link := listOfBalls;
				listOfBalls := newBall;
			end;
end;

procedure drawBoard;
var
	aWall : Wall;
	aBall : Ball;
	aHole : Hole;
begin
	SetPort (theWindow);
	
	aWall := listOfWalls;
	while (aWall <> nil) do begin
		aWall.draw;
		aWall := aWall.link;
	end;
	
	aHole := listOfHoles;
	while (aHole <> nil) do begin
		aHole.draw;
		aHole := aHole.link;
	end;
	
	aBall := listOfBalls;
	while (aBall <> nil) do begin
		aBall.draw;
		aBall := aBall.link;
	end;
	
	cueBall.draw;
	
end;

procedure createWindow;
var
	name : STR255;
	winType : integer;
	windowRect : Rect;
begin
	name := 'billiards game';
	SetRect (windowRect, 50, 70, 500, 400);
	winType := DocumentProc;
	theWindow := NewWindow(nil, windowRect, name, TRUE, winType, WindowPtr(-1),
		True, LongInt(09));
	SelectWindow(theWindow);
	showWindow(theWindow);
end;

procedure eventLoop;
var
	ignore : boolean;
	event : eventRecord;
	localPoint : Point;
	done : boolean;
begin
	done := false;
	while not done do begin
		systemTask;
		ignore := GetNextEvent(everyEvent, event);
		case event.what of
			keyDown:
				done := true; { return and quit }
			mouseDown:
				begin
					localPoint := event.where;
					GlobalToLocal(localPoint);
					mouseButtonDown(localPoint.h, localPoint.v);
				end;
			updateEvt:
				drawBoard;
		end;
	end;
end;

begin
	MaxApplZone; 
 	InitGraf(@qd.thePort);
	InitWindows;
	InitCursor;

	createGlobals;
	createWindow;
	
	eventLoop;	
end.