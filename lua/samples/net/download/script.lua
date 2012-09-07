if not pge.require("pge.font") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.net") then
	error("Error loading module.")
end

if not pge.require("pge.utils") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end


-- Load the font, 16 pixels in height, to RAM
verdana16 = pge.font.load("verdana.ttf", 16, PGE_RAM)

-- Check the font loaded correctly
if not verdana16 then
	error("Failed to load font.")
end

-- Init net and check success
if not pge.net.init() then
	error("Error on net init.")
end

-- Init net dialog and check success
if not pge.utils.netinit() then
	error("Error on net dialog init.")
end

-- Create a color
white = pge.gfx.createcolor(255, 255, 255)

-- Set an initial state for the net dialog
state = -1

-- Loop until exit requested
while pge.running() do

	-- Update controls
	pge.controls.update()

	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- pge.utils.netupdate() must be called after pge.gfx.enddrawing(), but before pge.gfx.swapbuffers()
	state = pge.utils.netupdate()
	
	-- Check state of net dialog
	if state == 0 then
		-- Connected
		break
	elseif state == 1 then
		-- User cancelled
		-- Shutdown net
		pge.net.shutdown()
		break
	elseif state ~= PGE_UTILS_DIALOG_RUNNING then
		-- Internal error
		-- Shutdown net
		pge.net.shutdown()
		break
	end
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
end

while pge.running() do

	-- Update controls
	pge.controls.update()
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Activate the font
	verdana16:activate()
	
	-- Print some text
	if pge.net.isconnected() then
		verdana16:printcenter(130, white, "Downloading file...")
	else
		verdana16:printcenter(130, white, "Not connected - Unable to download")
	end
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	if pge.net.isconnected() then
	
		-- Download a file
		pge.net.getfile("http://luaplayer.org/downloads/lp20/LuaPlayer_v0.20_firmware15.zip", "LuaPlayer_v0.20_firmware15.zip")
	
		-- Shutdown net
		pge.net.shutdown()
	
		-- Start drawing
		pge.gfx.startdrawing()
	
		-- Clear screen (to black)
		pge.gfx.clearscreen()
	
		-- Activate the font
		verdana16:activate()
	
		-- Print some text
		verdana16:printcenter(130, white, "Finished downloading")
	
		-- End drawing
		pge.gfx.enddrawing()
	
		-- Swap buffers
		pge.gfx.swapbuffers()
	
		-- Loop until START pressed
		while not pge.controls.pressed(PGE_CTRL_START) do
			pge.controls.update()
		end
		
		break
		
	end
	
	-- If START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end
	
end

verdana16 = nil