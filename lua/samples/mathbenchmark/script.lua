if not pge.require("pge.font") then
	error("Error loading module.")
end

if not pge.require("pge.gfx") then
	error("Error loading module.")
end

if not pge.require("pge.timer") then
	error("Error loading module.")
end

if not pge.require("pge.math") then
	error("Error loading module.")
end

if not pge.require("pge.controls") then
	error("Error loading module.")
end

-- Create a color
white = pge.gfx.createcolor(255, 255, 255)

-- Load a font, 9 pixels in height, to VRAM
monaco8 = pge.font.load("monaco.ttf", 9, PGE_VRAM)

-- Check the font loaded correctly
if not monaco8 then
	error("Failed to load font.")
end

-- Create a mytimer
mytimer = pge.timer.create()

print(tostring(mytimer))

-- Check the mytimer was created correctly
if not mytimer then
	error("Failed to create mytimer.")
end

-- Set the number of iterations
iterations = 10000

result = 0.0

-- Loop until exit requested
while pge.running() do

	-- Start drawing
	pge.gfx.startdrawing()
	
	-- Clear screen (to black)
	pge.gfx.clearscreen()
	
	-- Activate the font, ready for drawing
	monaco8:activate()
	
	-- Print some centered text
	monaco8:printcenter(130, white, "Please wait...")
	
	-- End drawing
	pge.gfx.enddrawing()
	
	-- Swap buffers
	pge.gfx.swapbuffers()
	
	-- Update the mytimer to get an initial value
	mytimer:update()
	
	-- Sin
	
	for i = 1, iterations do
		result = math.sin(i)
	end
	
	sinlmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Sin
	
	for i = 1, iterations do
		result = pge.math.sin(i)
	end
	
	sinpgetime = mytimer:peekdelta()
	
	-- Sinh
	
	for i = 1, iterations do
		result = math.sinh(i)
	end
	
	sinhlmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Sinh
	
	for i = 1, iterations do
		result = pge.math.sinh(i)
	end
	
	sinhpgetime = mytimer:peekdelta()
	
	-- Asin
	
	for i = 1, iterations do
		result = math.asin(i)
	end
	
	asinlmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Asin
	
	for i = 1, iterations do
		result = pge.math.asin(i)
	end
	
	asinpgetime = mytimer:peekdelta()
	
	-- Cos
	
	for i = 1, iterations do
		result = math.cos(i)
	end
	
	coslmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Cos
	
	for i = 1, iterations do
		result = pge.math.cos(i)
	end
	
	cospgetime = mytimer:peekdelta()
	
	-- Cosh
	
	for i = 1, iterations do
		result = math.cosh(i)
	end
	
	coshlmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Cosh
	
	for i = 1, iterations do
		result = pge.math.cosh(i)
	end
	
	coshpgetime = mytimer:peekdelta()
	
	-- Acos
	
	for i = 1, iterations do
		result = math.acos(i)
	end
	
	acoslmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Acos
	
	for i = 1, iterations do
		result = pge.math.acos(i)
	end
	
	acospgetime = mytimer:peekdelta()
	
	-- Tan
	
	for i = 1, iterations do
		result = math.tan(i)
	end
	
	tanlmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Tan
	
	for i = 1, iterations do
		result = pge.math.tan(i)
	end
	
	tanpgetime = mytimer:peekdelta()
	
	-- Tanh
	
	for i = 1, iterations do
		result = math.tanh(i)
	end
	
	tanhlmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Tanh
	
	for i = 1, iterations do
		result = pge.math.tanh(i)
	end
	
	tanhpgetime = mytimer:peekdelta()
	
	-- Atan
	
	for i = 1, iterations do
		result = math.atan(i)
	end
	
	atanlmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Atan
	
	for i = 1, iterations do
		result = pge.math.atan(i)
	end
	
	atanpgetime = mytimer:peekdelta()
	
	-- AcAtanos
	
	for i = 1, iterations do
		result = math.atan2(i, 1.337)
	end
	
	atan2lmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Atan2
	
	for i = 1, iterations do
		result = pge.math.atan2(i, 1.337)
	end
	
	atan2pgetime = mytimer:peekdelta()
	
	-- Pow
	
	for i = 1, iterations do
		result = math.pow(i, i)
	end
	
	powlmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Pow
	
	for i = 1, iterations do
		result = pge.math.pow(i, i)
	end
	
	powpgetime = mytimer:peekdelta()
	
	-- Exp
	
	for i = 1, iterations do
		result = math.exp(i)
	end
	
	explmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Exp
	
	for i = 1, iterations do
		result = pge.math.exp(i)
	end
	
	exppgetime = mytimer:peekdelta()
	
	-- sqrt
	
	for i = 1, iterations do
		result = math.sqrt(i)
	end
	
	sqrtlmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Sqrt
	
	for i = 1, iterations do
		result = pge.math.sqrt(i)
	end
	
	sqrtpgetime = mytimer:peekdelta()
	
	-- Fmod
	
	for i = 1, iterations do
		result = math.fmod(i, 1.337)
	end
	
	fmodlmtime = mytimer:peekdelta()
	
	mytimer:update()
	
	-- VFPU Fmod
	
	for i = 1, iterations do
		result = pge.math.fmod(i, 1.337)
	end
	
	fmodpgetime = mytimer:peekdelta()
	
	-- Loop until exit requested
	while pge.running() do
	
		-- Update controls
		pge.controls.update()
		
		-- Start drawing
		pge.gfx.startdrawing()
	
		-- Clear screen (to black)
		pge.gfx.clearscreen()
	
		-- Activate the font ready for drawing
		monaco8:activate();
		
		-- Print the results
		monaco8:print(20, 5, white, "Sin   LM   Time = " .. sinlmtime)
		monaco8:print(20, 13+1, white, "Sin   VFPU Time = " .. sinpgetime)
		monaco8:print(20, 21+2, white, "Cos   LM   Time = " .. coslmtime)
		monaco8:print(20, 29+3, white, "Cos   VFPU Time = " .. cospgetime)
		monaco8:print(20, 37+4, white, "Sinh  LM   Time = " .. sinhlmtime)
		monaco8:print(20, 45+5, white, "Sinh  VFPU Time = " .. sinhpgetime)
		monaco8:print(20, 53+6, white, "Cosh  LM   Time = " .. coshlmtime)
		monaco8:print(20, 61+7, white, "Cosh  VFPU Time = " .. coshpgetime)
		monaco8:print(20, 69+8, white, "Asin  LM   Time = " .. asinlmtime)
		monaco8:print(20, 77+9, white, "Asin  VFPU Time = " .. asinpgetime)
		monaco8:print(20, 85+10, white, "Acos  LM   Time = " .. acoslmtime)
		monaco8:print(20, 93+11, white, "Acos  VFPU Time = " .. acospgetime)
		monaco8:print(20, 101+12, white, "Tan   LM   Time = " .. tanlmtime)
		monaco8:print(20, 109+13, white, "Tan   VFPU Time = " .. tanpgetime)
		monaco8:print(20, 117+14, white, "Tanh  LM   Time = " .. tanhlmtime)
		monaco8:print(20, 125+15, white, "Tanh  VFPU Time = " .. tanhpgetime)
		monaco8:print(20, 133+16, white, "Atan  LM   Time = " .. atanlmtime)
		monaco8:print(20, 141+17, white, "Atan  VFPU Time = " .. atanpgetime)
		monaco8:print(20, 149+18, white, "Atan2 LM   Time = " .. atan2lmtime)
		monaco8:print(20, 157+19, white, "Atan2 VFPU Time = " .. atan2pgetime)
		monaco8:print(20, 165+20, white, "Pow   LM   Time = " .. powlmtime)
		monaco8:print(20, 173+21, white, "Pow   VFPU Time = " .. powpgetime)
		monaco8:print(20, 181+22, white, "Exp   LM   Time = " .. powlmtime)
		monaco8:print(20, 189+23, white, "Exp   VFPU Time = " .. powpgetime)
		monaco8:print(20, 197+24, white, "Sqrt  LM   Time = " .. sqrtlmtime)
		monaco8:print(20, 205+25, white, "Sqrt  VFPU Time = " .. sqrtpgetime)
		monaco8:print(20, 213+26, white, "Fmod  LM   Time = " .. fmodlmtime)
		monaco8:print(20, 221+27, white, "Fmod  VFPU Time = " .. fmodpgetime)
	
		-- End drawing
		pge.gfx.enddrawing()
	
		-- Swap buffers
		pge.gfx.swapbuffers()
		
		-- If START pressed, end
		if pge.controls.pressed(PGE_CTRL_START) then
			break
		end
		
	end

	break
	
end

monaco8 = nil
mytimer = nil