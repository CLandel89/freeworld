module GuiElements

	class Main < GuiElement

		attr_accessor :menu, :shown

		def initialize player
			super()
			@player = player
			#we don't need all the space left and right
			self.sx = 3/8
			self.center
			# add a vertical menu as a child to self
			@menu = GuiElements::MenuV.new
			self << @menu
			# some content
			@menu << GuiElements::Button.new
			@menu << GuiElements::Button.new
			@menu << GuiElements::Button.new
			@menu.vp_align_span
			# -> Gui[MenuV].control_hook
			player.control << self
			player.control << @menu
			# other parameters
			@player = player
			@shown = false
			@cross_id = player.sprite "std", "cross"
			@pointer_timeout = 0
			@pointer_x,@pointer_y = 0.5,0.5
		end

		def draw_impl
			self.fill_rect 0,0,1,1, 200,180,160
			dm = -10
			self.decorate dm,dm,dm,dm, 255,0,0, 5
		end

		def draw
			super #draw children, then paint over them
			# The cursor is part of "the UI".
			if @player.editor_mode || @player.frame_counter < @pointer_timeout
				graphics.draw_sprite_frac_c @cross_id, @pointer_x,@pointer_y,100,100
			end
		end

		def control_hook ci_t, ci_v
			super
			# as the root of the menu tree, work with these cases:
			if ci_t==CiType::PRESS && ci_v==CiButton::ESCAPE
				self.shown = !self.shown
				self.each_element proc { |e|
					e.focussed = false
				}
				#give focus to @menu, or remove it all together
				@menu.focussed = self.shown
			end
			if ci_t == CiType::MOUSE && self.shown
				@pointer_timeout = @player.frame_counter+12
				@pointer_x = ci_v[0]
				@pointer_y = ci_v[1]
			end
		end

		def graphics
			@player.graphics
		end

	end

end
