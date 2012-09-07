if not pge.require("pge.font") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.wav") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end

-- Load a font, 14 pixels high, in RAM
verdana14 = pge.font.load("verdana.ttf", 14, PGE_RAM)

-- Check font loaded correctly
if not verdana14 then
	error("Failed to load font.")
end

white = pge.gfx.createcolor(255, 255, 255)

-- Load a 8-bit mono WAV file
eightbitmono = pge.wav.load("8bitmono.wav")

-- Check the WAV loaded correctly
if not eightbitmono then
	error("Failed to load 8bitmono.wav.")
end

-- Load a 8-bit stereo WAV file
eightbitstereo = pge.wav.load("8bitstereo.wav")

-- Check the WAV loaded correctly
if not eightbitstereo then
	error("Failed to load 8bitstereo.wav.")
end

-- Load a 16-bit mono WAV file
sixteenbitmono = pge.wav.load("16bitmono.wav")

-- Check the WAV loaded correctly
if not sixteenbitmono then
	error("Failed to load 16bitmono.wav.")
end

-- Load a 16-bit stereo WAV file
sixteenbitstereo = pge.wav.load("16bitstereo.wav")

-- Check the WAV loaded correctly
if not sixteenbitstereo then
	error("Failed to load 16bitstereo.wav.")
end

-- Loop until exit requested
while pge.running() do
	
	-- Update controls
	pge.controls.update()
	
	-- if CROSS and LEFT TRIGGER pressed, stop playing 8 bit mono sample
	if pge.controls.pressed(PGE_CTRL_LTRIGGER + PGE_CTRL_CROSS) then
		eightbitmono:stop()
		
	-- if CROSS and RIGHT TRIGGER pressed, switch loop for 8 bit mono sample
	elseif pge.controls.pressed(PGE_CTRL_RTRIGGER + PGE_CTRL_CROSS) then
		eightbitmono:loop()
		
	-- if CROSS pressed, play 8 bit mono sample
	elseif pge.controls.pressed(PGE_CTRL_CROSS) then
		eightbitmono:play()
	end
	
	-- if CIRCLE and LEFT TRIGGER pressed, stop playing 8 bit stereo sample
	if pge.controls.pressed(PGE_CTRL_LTRIGGER + PGE_CTRL_CIRCLE) then
		eightbitstereo:stop()
		
	-- if CIRCLE and RIGHT TRIGGER pressed, switch loop for 8 bit stereo sample
	elseif pge.controls.pressed(PGE_CTRL_RTRIGGER + PGE_CTRL_CIRCLE) then
		eightbitstereo:loop()
		
	-- if CIRCLE pressed, play 8 bit stereo sample
	elseif pge.controls.pressed(PGE_CTRL_CIRCLE) then
		eightbitstereo:play()
	end
	
	-- if TRIANGLE and LEFT TRIGGER pressed, stop playing 16 bit mono sample
	if pge.controls.pressed(PGE_CTRL_LTRIGGER + PGE_CTRL_TRIANGLE) then
		sixteenbitmono:stop()
		
	-- if TRIANGLE and RIGHT TRIGGER pressed, switch loop for 16 bit mono sample
	elseif pge.controls.pressed(PGE_CTRL_RTRIGGER + PGE_CTRL_TRIANGLE) then
		sixteenbitmono:loop()
		
	-- if TRIANGLE pressed, play 16 bit mono sample
	elseif pge.controls.pressed(PGE_CTRL_TRIANGLE) then
		sixteenbitmono:play()
	end
	
	-- if SQUARE and LEFT TRIGGER pressed, stop playing 16 bit stereo sample
	if pge.controls.pressed(PGE_CTRL_LTRIGGER + PGE_CTRL_SQUARE) then
		sixteenbitstereo:stop()
		
	-- if SQUARE and RIGHT TRIGGER pressed, switch loop for 16 bit stereo sample
	elseif pge.controls.pressed(PGE_CTRL_RTRIGGER + PGE_CTRL_SQUARE) then
		sixteenbitstereo:loop()
		
	-- if SQUARE pressed, play 16 bit stereo sample
	elseif pge.controls.pressed(PGE_CTRL_SQUARE) then
		sixteenbitstereo:play()
	end
	
	-- if SELECT pressed, stop playing all samples
	if pge.controls.pressed(PGE_CTRL_SELECT) then
		pge.wav.stopall()
	end
	
	-- if START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		break
	end
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Activate the font, ready for drawing
	verdana14:activate()
	
	verdana14:print(20, 20, white, "Press CROSS to play 8-bit mono sample.")
	verdana14:print(20, 35, white, "Press CIRCLE to play 8-bit stereo sample.")
	verdana14:print(20, 50, white, "Press TRIANGLE to play 16-bit mono sample.")
	verdana14:print(20, 65, white, "Press SQUARE to play 16-bit stereo sample.")
	
	verdana14:print(20, 95, white, "Press LTRIGGER and a play button to stop playing the sample.")
	verdana14:print(20, 110, white, "Press RTRIGGER and a play button to toggle the loop.")
	verdana14:print(20, 125, white, "Press SELECT to stop playing all samples.")
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
end

eightbitmono = nil
eightbitstereo = nil
sixteenbitmono = nil
sixteenbitstereo = nil