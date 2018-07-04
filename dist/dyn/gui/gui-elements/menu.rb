module GuiElements

	class Menu < GuiElement

		def initialize
			super
			@selected = 0
		end

		def draw
			super #draw children, then paint over them
			#selected element
			se = self.children[selected]
			return if se==nil
			dm = -12
			se.decorate dm,dm,dm,dm, 0xff,0x80,0x80, -dm
		end

		def enter_sel
			se = self.children[selected]
			return if se==nil
			se.enter if se.respond_to? :enter
		end

		def selected
			@selected
		end
		def selected= s
			@selected = s
			bumped = false
			if s<0
				@selected=0
				bumped = true
			end
			l = self.children.length
			if s>=l
				@selected=l-1
				bumped = true
			end
			return @selected, bumped
		end

	end

	class MenuV < Menu

		include GuiVPanel

		def initialize
			super
			#Control axes (don't spam when using a joypad with sticks)
			@last_ax = 0
			@last_ay = 0
		end

		def control_hook ci_t, ci_v
			super
			case ci_t
			when CiType::AXIS_Y
				if ci_v<=-0.5 && @last_ay!=-1
					self.selected -= 1
					@last_ay = -1
				elsif ci_v>=0.5 && @last_ay!=1
					self.selected += 1
					@last_ay = 1
				elsif ci_v<=1/4 && ci_v>=-1/4
					@last_ay = 0 #axis "release"
				end
			end
		end

	end

end
