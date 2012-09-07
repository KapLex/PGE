if not pge.require("pge.font") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end

-- Create some colors
red = pge.gfx.createcolor(255, 0, 0)
green = pge.gfx.createcolor(0, 255, 0)
blue = pge.gfx.createcolor(0, 0, 255)
white = pge.gfx.createcolor(255, 255, 255)
black = pge.gfx.createcolor(0, 0, 0)

-- Load a font, 16 pixels in height, to VRAM
verdana16 = pge.font.load("lucida.ttf", 16, PGE_VRAM)

-- Check the font loaded correctly
if not verdana16 then
	error("Failed to load font: verdana.ttf")
end

-- Load a font, 20 pixels in height, to RAM
impact20 = pge.font.load("verdana.ttf", 20, PGE_RAM)

-- Check the font loaded correctly
if not impact20 then
	error("Failed to load font: impact.ttf")
end

-- Loop with exit requested
while pge.running() do
	
	-- Update controls
	pge.controls.update()
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- End drawing
	pge.gfx.clearscreen(black)
	
	-- Activate the font for drawing
	verdana16:activate();
	
	verdana16:print(100, 50, red, " .,!?:;0123456789")
	verdana16:print(100, 70, green, "ABCDEFGHIJKLMNOPQRSTUVWXYZ")
	verdana16:print(100, 90, blue, "abcdefghijklmnopqrstuvwxyz")
	verdana16:print(100, 110, white, "@#\"£$%%^&*()[]{}<>/\\|~`+-=_~'")
	
	-- Activate the second font for drawing
	impact20:activate();
	
	impact20:print(100, 150, red, " .,!?:;0123456789")
	impact20:print(100, 170, green, "ABCDEFGHIJKLMNOPQRSTUVWXYZ")
	impact20:print(100, 190, blue, "abcdefghijklmnopqrstuvwxyz")
	impact20:print(100, 210, white, "@#\"£$%%^&*()[]{}<>/\\|~`+-=_~'")
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	-- If START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end
	
end

verdana16 = nil
impact20 = nil