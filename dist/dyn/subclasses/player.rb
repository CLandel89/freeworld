class Player < Entity

  include MovingEntity

  attr_accessor :button
  attr_reader :graphics

  def initialize x,y,w,h
    super x,y,w,h
    me_initialize
    @graphics = Graphics.new
    @control = Control.new self
    @sprite_id = sprite "std", "test"
    @frame_counter = 0
    @la_x, @la_y = 0,0
    @cx, @cy = x + w/2, y + h/2
  end

  def action
    @control.action
    @me_sx = @control.a_x * 30
    @me_sy = @control.a_y * 30
    #in case you want to test the squashing effect
#    @x += @control.a_x
#    @y += @control.a_y
    @squashed = me_action
    @frame_counter += 1
    #smooth look-ahead and player in center approximation
    @la_x = (@la_x*7 + @me_sx*8) / 8
    @la_y = (@la_y*7 + @me_sy*8) / 8
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
  end

end