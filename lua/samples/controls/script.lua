if not pge.require("pge.controls") then
	error("Failed to load module.")
end

if not pge.require("pge.gfx") then
	error("Failed to load module.")
end

if not pge.require("pge.font") then
	error("Failed to load module.")
end

-- Create color 'white', RGB 255, 255, 255
white = pge.gfx.createcolor(255, 255, 255)

-- Load a font, 12 pixels high, in VRAM
verdana12 = pge.font.load("verdana.ttf", 12, PGE_VRAM)

-- Check font loaded correctly
if not verdana12 then
	error("Failed to load font.")
end

pressedenabled = false
pressedcounter = 255
pressedtext = ""

releasedenabled = false
releasedcounter = 255
releasedtext = ""

function setpressed()
	pressedenabled = true
	pressedcounter = 255
end

function setreleased()
	releasedenabled = true
	releasedcounter = 255
end

-- Loop until exit requested
while pge.running() do
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Update controls
	pge.controls.update()
	
	-- Activate font for drawing
	verdana12:activate();
	
	-- Analog controls	
	verdana12:print(20, 15, white, "Analog X: " .. pge.controls.analogx())	
	verdana12:print(20, 30, white, "Analog Y: " .. pge.controls.analogy())
	verdana12:print(150, 15, white, "Analog Magnitude: " .. pge.controls.analogmag())
	verdana12:print(150, 30, white, "Analog Angle: " .. pge.controls.analogangle())
	
	-- Held buttons	
	if pge.controls.held(PGE_CTRL_UP) then
		verdana12:print(20, 45, white, "Up held")
	end
	
	if pge.controls.held(PGE_CTRL_DOWN) then
		verdana12:print(20, 60, white, "Down held")
	end
	
	if pge.controls.held(PGE_CTRL_LEFT) then
		verdana12:print(20, 75, white, "Left held")
	end
	
	if pge.controls.held(PGE_CTRL_RIGHT) then
		verdana12:print(20, 90, white, "Right held")
	end
	
	if pge.controls.held(PGE_CTRL_TRIANGLE) then
		verdana12:print(20, 105, white, "Triangle held")
	end
	
	if pge.controls.held(PGE_CTRL_CROSS) then
		verdana12:print(20, 120, white, "Cross held")
	end
	
	if pge.controls.held(PGE_CTRL_SQUARE) then
		verdana12:print(20, 135, white, "Square held")
	end
	
	if pge.controls.held(PGE_CTRL_CIRCLE) then
		verdana12:print(20, 150, white, "Circle held")
	end
	
	if pge.controls.held(PGE_CTRL_RTRIGGER) then
		verdana12:print(20, 165, white, "Right trigger held")
	end
	
	if pge.controls.held(PGE_CTRL_LTRIGGER) then
		verdana12:print(20, 180, white, "Left trigger held")
	end
	
	if pge.controls.held(PGE_CTRL_START) then
		verdana12:print(20, 195, white, "Start held")
	end
	
	if pge.controls.held(PGE_CTRL_SELECT) then
		verdana12:print(20, 210, white, "Select held")
	end
	
	-- Pressed buttons	
	if pge.controls.pressed(PGE_CTRL_UP) then
		pressedtext = "Up pressed"
		setpressed()
	end
	
	if pge.controls.pressed(PGE_CTRL_DOWN) then
		pressedtext = "Down pressed"
		setpressed()
	end
	
	if pge.controls.pressed(PGE_CTRL_LEFT) then
		pressedtext = "Left pressed"
		setpressed()
	end
	
	if pge.controls.pressed(PGE_CTRL_RIGHT) then
		pressedtext = "Right pressed"
		setpressed()
	end
	
	if pge.controls.pressed(PGE_CTRL_TRIANGLE) then
		pressedtext = "Triangle pressed"
		setpressed()
	end
	
	if pge.controls.pressed(PGE_CTRL_CROSS) then
		pressedtext = "Cross pressed"
		setpressed()
	end
	
	if pge.controls.pressed(PGE_CTRL_SQUARE) then
		pressedtext = "Square pressed"
		setpressed()
	end
	
	if pge.controls.pressed(PGE_CTRL_CIRCLE) then
		pressedtext = "Circle pressed"
		setpressed()
	end
	
	if pge.controls.pressed(PGE_CTRL_RTRIGGER) then
		pressedtext = "Right trigger pressed"
		setpressed()
	end
	
	if pge.controls.pressed(PGE_CTRL_LTRIGGER) then
		pressedtext = "Left trigger pressed"
		setpressed()
	end
	
	if pge.controls.pressed(PGE_CTRL_START) then
		pressedtext = "Start pressed"
		setpressed()
		break
	end
	
	if pge.controls.pressed(PGE_CTRL_SELECT) then
		pressedtext = "Select pressed"
		setpressed()
	end
	
	-- Released buttons	
	if pge.controls.released(PGE_CTRL_UP) then
		releasedtext = "Up released"
		setreleased()
	end
	
	if pge.controls.released(PGE_CTRL_DOWN) then
		releasedtext = "Down released"
		setreleased()
	end
	
	if pge.controls.released(PGE_CTRL_LEFT) then
		releasedtext = "Left released"
		setreleased()
	end
	
	if pge.controls.released(PGE_CTRL_RIGHT) then
		releasedtext = "Right released"
		setreleased()
	end
	
	if pge.controls.released(PGE_CTRL_TRIANGLE) then
		releasedtext = "Triangle released"
		setreleased()
	end
	
	if pge.controls.released(PGE_CTRL_CROSS) then
		releasedtext = "Cross released"
		setreleased()
	end
	
	if pge.controls.released(PGE_CTRL_SQUARE) then
		releasedtext = "Square released"
		setreleased()
	end
	
	if pge.controls.released(PGE_CTRL_CIRCLE) then
		releasedtext = "Circle released"
		setreleased()
	end
	
	if pge.controls.released(PGE_CTRL_RTRIGGER) then
		releasedtext = "Right trigger released"
		setreleased()
	end
	
	if pge.controls.released(PGE_CTRL_LTRIGGER) then
		releasedtext = "Left trigger released"
		setreleased()
	end
	
	if pge.controls.released(PGE_CTRL_START) then
		releasedtext = "Start released"
		setreleased()
	end
	
	if pge.controls.released(PGE_CTRL_SELECT) then
		releasedtext = "Select released"
		setreleased()
	end
	
	if releasedenabled then
		releasedcounter = releasedcounter - 5
		
		verdana12:print(460 - verdana12:measure(releasedtext), 250, pge.gfx.createcolor(255, 0, 0, releasedcounter), releasedtext)
		
		if releasedcounter == 0 then
			releasedcounter = 255
			releasedenabled = false
		end
	end
	
	if pressedenabled then
		pressedcounter = pressedcounter - 5
		
		verdana12:print(20, 250, pge.gfx.createcolor(0, 255, 0, pressedcounter), pressedtext)
		
		if pressedcounter == 0 then
			pressedcounter = 255
			pressedenabled = false
		end
	end
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
		
end

verdana12 = nil