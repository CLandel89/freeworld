class Gui < GuiElement

  attr_accessor :menu, :shown

  def initialize player
	super()
	#we don't need all the space left and right
	self.sx = 3/8
	self.center
	# add a vertical menu as a child to self
    @menu = GuiMenuV.new
    self << @menu
    # some content
    @menu << GuiButton.new
    @menu << GuiButton.new
    @menu << GuiButton.new
    @menu.vp_align_span
    # -> Gui.control_hook
    player.control << self
    # other parameters
    @player = player
    @shown = false
  end

  def draw_impl
    self.fill_rect 0,0,1,1, 200,180,160
    dm = -10
    self.decorate dm,dm,dm,dm, 255,0,0, 5
  end

  def control_hook ci_t, ci_v
    if ci_t==CiType::AXIS_Y && self.shown
      if ci_v==-1
		menu.selected -= 1
      elsif ci_v==1
        menu.selected += 1
	  end
    end
    if ci_t==CiType::PRESS
      case ci_v
      when CiButton::JUMP
        menu.enter_sel if self.shown
      when CiButton::ESCAPE
        self.shown = !self.shown
      end
    end
  end

  def graphics
    @player.graphics
  end

end
