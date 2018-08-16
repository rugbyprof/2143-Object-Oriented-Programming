{
	Billiard Simulation Program
	To demonstrate features of OOP in Object Pascal
	Written by Tim Budd, September 1995
}
Program billiards;

USES
  Windows;

type
	(* Ball = object; forward; (* forward declaration *)
	
	GraphicalObject = object
			(* data fields *)
		link : GraphicalObject;
		region : Rect;
		
			(* initialization function *)
		procedure setRegion (left, top, right, bottom : integer);
		
			(* operations that graphical objects perform *)
		procedure draw;
		procedure erase;
		procedure update;
		function intersect (anObj : GraphicalObject) : boolean;
		procedure hitBy (aBall : GraphicalObject);		
	end;
	
	Ball = object (GraphicalObject)
			{ data values maintained by balls }
		direction : real;
		energy : real;
		
				{ initialization routine }
		procedure initialize (x, y : integer);

			{ common methods }
		procedure draw; override;
		procedure update; override;
		procedure hitBy (aBall : GraphicalObject); override;
		procedure setCenter (newx, newy : integer);

			{ return x, y coordinate center of ball }
		function x : integer;
		function y :integer;
	end;

	Wall = object (GraphicalObject)
				{ factor used to reflect striking balls }
			convertFactor : real;
			
				{ initialization function }
			procedure initialize (left, top, right, bottom : integer; cf : real);

				{ draw wall }
			procedure draw; override;

				{ notify wall that a ball has struck }
			procedure hitBy (aBall : GraphicalObject); override;
		end;

	Hole = object (GraphicalObject)
				{ initialize location of hole }
			procedure initialize (x, y : integer);

				{ draw the hole }
			procedure draw; override;

				{ notify hole that it has received a ball }
			procedure hitBy (aBall : GraphicalObject); override;
		end;

	var
		cueBall : Ball;
		saveRack : integer;
		ballMoved : boolean;
		listOfObjects : GraphicalObject;

		theWindow : windowPtr;
		
procedure GraphicalObject.setRegion (left, top, right, bottom : integer);
begin
	SetRect (region, left, top, right, bottom);
end;

procedure GraphicalObject.draw;
begin
end;

procedure GraphicalObject.erase;
begin
	EraseRect (region);
end;

procedure GraphicalObject.update;
begin
end;

procedure GraphicalObject.hitBy (aBall : GraphicalObject);
begin
end;

function GraphicalObject.intersect (anObject : GraphicalObject) : boolean;
var
	theIntersection : Rect;
begin
	intersect := SectRect(region, anObject.region, theIntersection);
end;
		
procedure Wall.initialize (left, top, right, bottom : integer; cf : real);
begin
		{ initialize convertion factor }
	convertFactor := cf;
	
		{ set up region for wall }
	setRegion(left, top, right, bottom);
end;

procedure Wall.draw;
begin
	PaintRect (region);
end;

procedure Wall.hitBy (anObj : GraphicalObject);
var
	aBall : Ball;
begin
	if Member(anObj, Ball) then begin
		aBall := Ball(anObj);
			{ bounce the ball off the wall }
		aBall.direction := convertFactor - aBall.direction;
	end;
end;

procedure Hole.initialize (x, y : integer);
var left, top, bottom, right : integer;
begin
		{ identify region centered around x, y }
	left := x - 5;
	top := y - 5;
	right := x + 5;
	bottom := y + 5;
	setRegion(left, top, right, bottom);
end;

procedure Hole.draw;
begin
	PaintOval (region);
end;

procedure Hole.hitBy (anObj : GraphicalObject);
var
	aBall : Ball;
begin
	if Member(anObj, Ball) then begin
		aBall := Ball(anObj);
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
end;

procedure Ball.setCenter (newx, newy : integer);
var left, top, bottom, right : integer;
begin
		{ identify region centered around x, y }
	left := newx - 5;
	top := newy - 5;
	right := newx + 5;
	bottom := newy + 5;
	setRegion (left, top, right, bottom);
end;

procedure Ball.initialize (x, y : integer);
begin
	setCenter(x, y);
	direction := 0.0;
	energy := 0.0;
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
	gptr : GraphicalObject;
	dx, dy : integer;
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
			{ see if we hit anything }
		gptr := listOfObjects;
		while gptr <> nil do begin
			if gptr <> self then 
				if self.intersect(gptr) then
					gptr.hitBy(self);
			gptr := gptr.link;
		end;
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

procedure Ball.hitBy (anObj : GraphicalObject);
var
	aBall : Ball;
	da : real;
begin
	if Member(anObj, Ball) then begin
		aBall := Ball(anObj);
			{ cut the energy of the hitting ball in half }
		aBall.energy := aBall.energy / 2.0;

			{ and add it to our own }
		energy := energy + aBall.energy;

			{ set our new direction }
		direction := hitAngle(self.x - aBall.x, self.y - aBall.y);

			{ and set the hitting balls direction }
		da := aBall.direction - direction;
		aBall.direction := aBall.direction + da;
	end;
end;

procedure mouseButtonDown (x, y : integer);
var
	gptr : GraphicalObject;
begin
		{ give the cue ball some energy }
	cueBall.energy := 20.0;
		{ and a direction }
	cueBall.direction := hitAngle (cueBall.x - x, cueBall.y - y);

		{ then loop as long as called for }
	ballMoved := true;
	while ballMoved do begin
		ballMoved := false;
		gptr := listOfObjects;
		while gptr <> nil do begin
			gptr.update;
			gptr := gptr.link;
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
	listOfObjects := nil;
		
			{ create walls }
	new (newWall);
	newWall.initialize(10, 10, 300, 15, 0.0);
	newWall.link := listOfObjects;
	listOfObjects := newWall;
	new (newWall);
	newWall.initialize(10, 200, 300, 205, 0.0);
	newWall.link := listOfObjects;
	listOfObjects := newWall;
	new (newWall);
	newWall.initialize(10, 10, 15, 200, 3.14159);
	newWall.link := listOfObjects;
	listOfObjects := newWall;
	new (newWall);
	newWall.initialize(300, 10, 305, 205, 3.14159);
	newWall.link := listOfObjects;
	listOfObjects := newWall;
	
			{ create holes }
	new(newHole);
	newHole.initialize(15, 15);
	newHole.link := listOfObjects;
	listOfObjects := newHole;
	new(newHole);
	newHole.initialize(15, 200);
	newHole.link := listOfObjects;
	listOfObjects := newHole;
	new(newHole);
	newHole.initialize(300, 15);
	newHole.link := listOfObjects;
	listOfObjects := newHole;
	new(newHole);
	newHole.initialize(300, 200);
	newHole.link := listOfObjects;
	listOfObjects := newHole;
	
			{ create balls }
	new (cueBall);
	cueBall.initialize(50, 96);
	cueBall.link := listOfObjects;
	listOfObjects := cueBall;
	
	for i := 1 to 5 do
		for j := 1 to i do
			begin
				new(newBall);
				newBall.initialize(190 + i * 8,
					100 + 16 * j - 8 * i);
				newBall.link := listOfObjects;
				listOfObjects := newBall;
			end;
end;

procedure drawBoard;
var
	gptr : GraphicalObject;
begin
	SetPort (theWindow);
		
	gptr := listOfObjects;
	while gptr <> nil do begin
		gptr.draw;
		gptr := gptr.link;
	end;	
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