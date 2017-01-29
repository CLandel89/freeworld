class Player < AbstractEntity

  attr_accessor :button
  attr_reader :graphics

  def initialize instance
    super()
    @instance = instance
    @graphics = Graphics.new
    @control = Control.new self
    @sprite_id = sprite "std", "test"
  end

  def action
    @x = x + @control.axis_x*10
    @y = y + @control.axis_y*10
  end

end