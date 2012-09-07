if not pge.require("pge.font") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.utils") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end

if not pge.require("pge.net") then
	error("Error loading module.")
end

if not pge.require("pge.math") then
	error("Error loading module.")
end

-- Load a font, 16 pixels in height, to RAM
verdana16 = pge.font.load("verdana.ttf", 16, PGE_RAM)

-- Check font loaded correctly
if not verdana16 then
	error("Failed to load font.")
end

-- Init net and check success
if not pge.net.init() then
	error("Error on net init.")
end

-- Init browser and check success
if not pge.utils.browserinit("http://www.google.com/") then
	error("Error on browser init.")
end

-- Create two colors
white = pge.gfx.createcolor(255, 255, 255)
red = pge.gfx.createcolor(255, 0, 0)

enabled = true
state = -1
text = ""
x = 0
y = 0
counter = 0

-- Loop until exit requested
while pge.running() do

	-- Update controls
	pge.controls.update()

	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Draw a rectangle
	pge.gfx.drawrect(x, y, 100, 60, red)
	
	-- If browser not shown, draw some text
	if not enabled then
		verdana16:activate()
		verdana16:printcenter(130, white, text)
	end
	
	-- End drawing
	pge.gfx.enddrawing()
	
	if enabled then
		-- pge.utils.browserupdate() must be called after pge.gfx.enddrawing(), but before pge.gfx.swapbuffers()
		state = pge.utils.browserupdate()
	
		if state == 0 then
			text = "Browser exited successfully."
			pge.net.shutdown()
			enabled = false
		elseif state == 1 then
			text = "Browser exited via cancellation."
			enabled = false
			pge.net.shutdown()
		elseif state ~= PGE_UTILS_DIALOG_RUNNING then
			text = "Internal error."
			enabled = false
			pge.net.shutdown()
		end
	end
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	-- Increment counter
	counter = counter + 1
	
	-- Give the rectangle a random position on screen
	if counter >= 60 then
		counter = 0
		x = pge.math.randfloat(0, 380)
		y = pge.math.randfloat(0, 212)
	end
	
	-- If START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end
	
end

verdana16 = nil