class Player < Entity

  include EntityVertical

  attr_reader :graphics, :control, :gui, :frame_counter

  def initialize x,y,z,w,h
    super x,y,z,w,h
    @graphics = Graphics.new
    @control = Control.new self
    @gui = Gui.new self
    @sprite_id = sprite "std", "test"
    @frame_counter = 0
    @la_x, @la_y = 0,0
    @cx, @cy = x + w/2, y + h/2
    @squashed = false
  end

  def action instance
    @control.action
    #in case you want to test the squashing effect
#    @x += @control.x
#    @y += @control.y
    @squashed = ev_action instance
    @frame_counter += 1
    #smooth look-ahead and player in center approximation
    @la_x = (@la_x*7 + @em_sx*8) / 8
    @la_y = (@la_y*7 + @em_sy*8) / 8
    @cx = (@cx*3 + @x + @w/2) / 4
    @cy = (@cy*3 + @y + @h/2) / 4
    @graphics.cam_x = @cx + @la_x
    @graphics.cam_y = @cy + @la_y
  end

  def draw g
    a,b = (g.x_to_screen @x), (g.y_to_screen @y)
    g.draw_sprite_raw @sprite_id,a,b,@w,@h
    if @squashed and @frame_counter % 4 == 2
      #"Ouch!"
      g.fill_rect_raw 0,0,(g.res_w),(g.res_h), 255,0,0
    end
    gui.draw
  end

end
