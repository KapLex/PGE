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

if not pge.require("pge.math") then
	error("Error loading module.")
end

-- Load the font, 16 pixels in height, to RAM
verdana16 = pge.font.load("verdana.ttf", 16, PGE_RAM)

-- Check the font loaded correctly
if not verdana16 then
	error("Failed to load font.")
end

-- Init OSK with description, initial text and check success
if not pge.utils.oskinit("Test Description", "Initial Text") then
	error("Error on osk init.")
end

-- Create two colors
white = pge.gfx.createcolor(255, 255, 255)
red = pge.gfx.createcolor(255, 0, 0)

enabled = true
done = false
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
	
	-- If OSK not being drawn, draw some text
	if not enabled then
		verdana16:activate()
		verdana16:printcenter(130, white, text)
	end
	
	-- End drawing
	pge.gfx.enddrawing()
	
	if enabled then
		-- pge.utils.oskupdate() must be called after pge.gfx.enddrawing(), but before pge.gfx.swapbuffers()
		done, text = pge.utils.oskupdate()
		
		if done then
			if text == "" then
				text = "User cancelled."
				enabled = false
			else
				text = "User entered: " .. text
				enabled = false
			end
		end
	end
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	-- Increment counter
	counter = counter + 1
	
	-- Set the rectangle to a random screen position
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

white = nil
red = nil
state = nil
enabled = nil
done = nil
text = nil
x = nil
y = nil
counter = nil