if not pge.require("pge.font") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end


-- Load a font, 12 pixels high, in VRAM
verdana12 = pge.font.load("verdana.ttf", 12, PGE_VRAM)

-- Check font loaded correctly
if not verdana12 then
	error("Failed to load font.")
end

color = pge.gfx.createcolor(255, 255, 255)
green = pge.gfx.createcolor(0, 255, 0)
white = pge.gfx.createcolor(255, 255, 255)

selection = 1

function getdrawcolor(current)
	if current == selection then
		return green
	else
		return white
	end
end

function coloradd(current)
	if current == 1 then
		color:red(color:red() + 1)
	elseif current == 2 then
		color:green(color:green() + 1)
	elseif current == 3 then
		color:blue(color:blue() + 1)
	else
		color:alpha(color:alpha() + 1)
	end
end

function colorminus(current)
	if current == 1 then
		color:red(color:red() - 1)
	elseif current == 2 then
		color:green(color:green() - 1)
	elseif current == 3 then
		color:blue(color:blue() - 1)
	else
		color:alpha(color:alpha() - 1)
	end
end

-- Loop while exit requested
while pge.running() do

	-- Update controls
	pge.controls.update()
	
	if pge.controls.pressed(PGE_CTRL_UP) then
		if selection > 1 then
			selection = selection - 1
		end
	end
	
	if pge.controls.pressed(PGE_CTRL_DOWN) then
		if selection < 4 then
			selection = selection + 1
		end
	end
	
	if pge.controls.held(PGE_CTRL_LEFT) then
		colorminus(selection)
	end
	
	if pge.controls.held(PGE_CTRL_RIGHT) then
		coloradd(selection)
	end
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	pge.gfx.drawrect(10, 10, 460, 150, color)
	
	verdana12:activate()
	
	verdana12:print(20, 170, getdrawcolor(1), "Red: " .. color:red())
	verdana12:print(20, 185, getdrawcolor(2), "Green: " .. color:green())
	verdana12:print(20, 200, getdrawcolor(3), "Blue: " .. color:blue())
	verdana12:print(20, 215, getdrawcolor(4), "Alpha: " .. color:alpha())
	verdana12:print(20, 240, green, "Press UP or DOWN to select a color value\nPress LEFT or RIGHT to manipulate that value")
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Dwap buffers
	pge.gfx.swapbuffers()
	
	-- If START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end

end
