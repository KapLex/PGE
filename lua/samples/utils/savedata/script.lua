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

-- Create two colors
white = pge.gfx.createcolor(255, 255, 255)
red = pge.gfx.createcolor(255, 0, 0)

enabled = true
state = -1
text = ""
x = 0
y = 0
counter = 0
dialogcounter = 0
nextdialogflag = false

-- Change directory back to where the EBOOT.PBP is located
pge.dir.chdir("../../../")

-- Init the various savedata dialogs (one at a time, each call to the function)
function nextdialog()
	
	if dialogcounter == 0 then
		-- Initial creation of the savedata. We'll set the score to 10.
		if not pge.utils.saveinit("score = 10", "GAME00000", "Title", "Sub Title", "Score I got was 10") then
			error("Error on save dialog init.")
		end
	end
	
	if dialogcounter == 1 then
		-- Let's load the savedata back. There's no need to do this except for showing the usage in a sample.
		if not pge.utils.loadinit(10, "GAME00000") then
			error("Error on load dialog init.")
		end
	end
	
	if dialogcounter == 2 then
		-- Auto save the new score of 11. No dialog is actually shown, but we still need to process it as such.
		if not pge.utils.autosaveinit("score = 11", "GAME00000", "Title", "Sub Title", "Score I got was 11") then
			error("Error on auto save dialog init.")
		end
	end
	
	if dialogcounter == 3 then
		-- Init the delete option for the savedata
		if not pge.utils.deleteinit("GAME00000") then
			error("Error on delete dialog init.")
		end
	end
	
	dialogcounter = dialogcounter + 1
	
end

-- Init the first savedata dialog
nextdialog()

-- Loop until exit requested
while pge.running() do

	-- Update controls
	pge.controls.update()

	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Draw a rectable
	pge.gfx.drawrect(x, y, 100, 60, red)
	
	-- If net dialog not displayed draw some text
	if not enabled then
		verdana16:activate()
		verdana16:printcenter(130, white, text)
	end
	
	-- End drawing
	pge.gfx.enddrawing()
	
	if enabled then
		-- pge.utils.savedataupdate() must be called after pge.gfx.enddrawing(), but before pge.gfx.swapbuffers()
		state = pge.utils.savedataupdate()
	
		if state == 0 then
			nextdialogflag = true
		elseif state == 1 then
			text = "Save dialog exited via cancellation."
			enabled = false
		elseif state ~= PGE_UTILS_DIALOG_RUNNING then
			text = "Internal error."
			enabled = false
		end
	end
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	-- The next dialog can only be initialised after pge.gfx.swapbuffers()
	if nextdialogflag then
		nextdialog()
		nextdialogflag = false
	end
	
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
text = nil
x = nil
y = nil
counter = nil
dialogcounter = nil
nextdialogflag = nil