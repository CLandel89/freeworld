# Draws text on a Graphics. Create another Text object if you wish to use another font.
# List the known characters with <<, unknown characters will be treated like space(" ")!
class Text

	# graphics: The Graphics object
	# pkg: the package name, e.g. 'std'
	# path: the folder path in pkg+'sprites/fonts' with the letter sprites, e.g.: 'clip-art-blue'
	# width, heigth: the dimensions of each character (make these smaller than the actual image files if they should overlap)
	def initialize graphics, pkg, path, width, height
		@graphics = graphics
		@pkg = pkg
		@path = path
		@width = width
		@height = height
		@sprites = Hash.new
	end

	# chars: A list of unicode codes (as fixnums) that are present as image files in the font, e.g.: 'a'.ord..'z'.ord
	# Note that this is the only way for Text to know which image files are actually present in the font!
	def << chars
		chars.each do |char|
			fn = 'packages/' + @pkg + '/sprites/fonts/' + @path + '/' +
				(sprintf '%0.8X', char) + '.png'
			@sprites[char] = CoreUtils.string_hash fn
			puts fn
		end
		return self
	end

	# Draw text with the absolute (0...{w,h}) coordinates as the center of the first character.
	def draw x,y, str
		start_x = x
		str.chars.each do |char|
			if char=="\n"
				y += @height
				x = start_x
				next
			end
			id = @sprites[char.ord]
			if id != nil
				@graphics.draw_sprite_raw id, x,y,@width,@height
			end
			x += @width
		end
	end

	# Draw text with the relative (0...1) coordinates as the center of the first character.
	def draw_frac x,y, str
		draw x*graphics.res_w, y*graphics.res_h, str
	end

end
