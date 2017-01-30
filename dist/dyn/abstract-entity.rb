class AbstractEntity

  attr_reader :sprite_id, :wall_id
  attr_reader :x, :y, :w, :h

  def initialize
    @sprite_id = nil
    @wall_id = nil
    @x, @y, @w, @h = 0, 0, 100, 100
  end

  def sprite pkg, fn
    CoreUtils.string_hash 'packages/' + pkg + '/sprites/' + fn + '.png'
  end

  def wall pkg, fn
    CoreUtils.string_hash 'packages/' + pkg + '/walls/' + fn + '.jpg'
  end

  def wall_png pkg, fn
    CoreUtils.string_hash 'packages/' + pkg + '/walls/' + fn + '.png'
  end

end