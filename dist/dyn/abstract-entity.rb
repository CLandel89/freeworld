class AbstractEntity

  attr_accessor :sprite_id, :wall_id
  attr_accessor :x, :y, :w, :h

  def initialize x,y,w,h
    @sprite_id = nil
    @wall_id = nil
    @x,@y,@w,@h = x,y,w,h
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