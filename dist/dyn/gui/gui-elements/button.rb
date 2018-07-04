module GuiElements

	class Button < GuiElement

		attr_accessor :br, :bg, :bb
		attr_accessor :dr, :dg, :db
		attr_accessor :dm, :dt

		def initialize
			super
			@hooks = Array.new
			#grey background
			self.br = self.bg = self.bb = 0x80
			#black decoration
			self.dr = self.dg = self.db = 0
			#decoration margin
			self.dm = 25
			#decoration thickness
			self.dt = 5
		end

		def draw_impl
			self.fill_rect 0,0,1,1, self.br,self.bg,self.bb
			self.decorate self.dm,self.dm,self.dm,self.dm, self.dr,self.dg,self.db, self.dt
		end

		def enter
			@hooks.each do |hook|
				if !hook.respond_to? :button_hook
					debug "#{self}: Warning: #{hook} does not respond to #{:button_hook}!"
				else
					hook.button_hook self
				end
			end
		end

		#it usually makes no sense to add further child UI elements
		#as children to a button, so we're overriding:
		def << hook
			@hooks << hook
		end
		def delete hook
			@hooks.delete hook
		end

	end

end
