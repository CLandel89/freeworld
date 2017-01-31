class Player < AbstractEntity

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