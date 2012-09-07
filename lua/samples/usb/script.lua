if not pge.require("pge.font") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.usb") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end


-- Create two colors
white = pge.gfx.createcolor(255, 255, 255)
green = pge.gfx.createcolor(0, 255, 0)

-- Load a font, 16 pixels in height, to RAM
verdana16 = pge.font.load("verdana.ttf", 16, PGE_RAM)

-- Check the font loaded correctly
if not verdana16 then
	error("Failed to load font.")
end

-- Init USB and check it was successful
if not pge.usb.init() then
	error("Failed to init USB.")
end

-- Loop until exit requested
while pge.running() do

	-- Update controls
	pge.controls.update()
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Activate the font, ready for drawing
	verdana16:activate()
	
	-- Draw some text
	verdana16:print(20, 20, white, "Press X to activate USB")
	verdana16:print(20, 40, white, "Press O to deactivate USB")
	
	if pge.usb.activated() then
		verdana16:print(20, 60, green, "USB activated")
	end
	
	if pge.usb.cable() then
		verdana16:print(20, 80, green, "Cable connected")
	end
	
	if pge.usb.established() then
		verdana16:print(20, 100, green, "Connection established")
	end
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	-- If CROSS pressed, activate USB
	if pge.controls.pressed(PGE_CTRL_CROSS) then
		pge.usb.activate()
	end
	
	-- If CIRCLE pressed, deactivate USB
	if pge.controls.pressed(PGE_CTRL_CIRCLE) then
		pge.usb.deactivate()
	end
	
	-- If START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end
	
end

-- Deactivate USB
pge.usb.deactivate()

-- Shutdown USB
pge.usb.shutdown()

verdana16 = nil