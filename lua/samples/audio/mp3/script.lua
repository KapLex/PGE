if not pge.require("pge.font") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.mp3") then
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

-- Looping flag
looping = false

-- Volume value
volume = 32768

-- Start playing the MP3
pge.mp3.play("test.mp3")

-- Table for our vertices
vertices = {}

-- Create the color white
white = pge.gfx.createcolor(255, 255, 255)

-- Loop until exit requested
while pge.running() do

	-- Get the ID3 info for the MP3
	mp3info = pge.mp3.getinfo();

	-- Update controls
	pge.controls.update()
	
	-- if CROSS pressed, play MP3
	if pge.controls.pressed(PGE_CTRL_CROSS) then
		pge.mp3.play("test.mp3")
	end
	
	-- if CIRCLE pressed, stop MP3
	if pge.controls.pressed(PGE_CTRL_CIRCLE) then
		pge.mp3.stop()
	end
	
	-- if START pressed, pause MP3
	if pge.controls.pressed(PGE_CTRL_SELECT) then
		pge.mp3.pause()
	end
	
	-- if TRIANGLE pressed, switch loop setting
	if pge.controls.pressed(PGE_CTRL_TRIANGLE) then
		
		if looping == false then
			looping = true
		else
			looping = false
		end
		
		pge.mp3.loop(looping)
	end
	
	-- if RTRIGGER held, increase volume by 1
	if pge.controls.held(PGE_CTRL_RTRIGGER) then
		volume = volume + 100
		pge.mp3.volume(volume) -- Apply the new volume
	end
	
	-- if LTRIGGER held, decrease volume by 1
	if pge.controls.held(PGE_CTRL_LTRIGGER) then
		volume = volume - 100
		pge.mp3.volume(volume) -- Apply the new volume
	end
	
	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Get the audio data and create a vertex from it
	for index = 1, 400 do
		audiodata = pge.mp3.getaudiodata(index * 2)
		vertices[index] = {pge.gfx.createcolor(68, 255, 255), 40 + index, ((audiodata + 32767) * 0.002) + 130.0, 0}
	end
	
	-- Draw the 'visualiser' effect
	pge.gfx.drawcustom(PGE_PRIM_LINE_STRIP, PGE_VERT_CV, vertices)
	
	-- Activate the font
	verdana14:activate()
	
	-- Draw the ID3 info text
	verdana14:print(30, 30, white, "Title: " .. mp3info:title())
	verdana14:print(30, 45, white, "Artist: " .. mp3info:artist())
	verdana14:print(30, 60, white, "Album: " .. mp3info:album())
	verdana14:print(30, 75, white, "Year: " .. mp3info:year())
	verdana14:print(30, 90, white, "Comment: " .. mp3info:comment())
	verdana14:print(30, 105, white, "Genre: " .. mp3info:genre())
	verdana14:print(30, 120, white, "ID3 Version: " .. mp3info:id3version())
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	-- if START pressed, end
	if pge.controls.pressed(PGE_CTRL_START) then
		pge.mp3.stop()
		break
	end
	
end

verdana14 = nil