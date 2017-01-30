class Player < AbstractEntity

  attr_accessor :button
  attr_reader :graphics

  def initialize x,y,w,h
    super x,y,w,h
    @graphics = Graphics.new
    @control = Control.new self
    @sprite_id = sprite "std", "test"
  end

  def action
    @x = x + @control.axis_x*10
    @y = y + @control.axis_y*10
  end

end