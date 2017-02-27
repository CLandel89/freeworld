class Entity

  attr_accessor :sprite_id, :wall_id
  attr_accessor :x, :y, :w, :h

  MAXNUM = (2**30 - 1)
  MINNUM = (- 2**30)

  def initialize x,y,w,h
    @sprite_id = nil
    @wall_id = nil
    @x,@y,@w,@h = x,y,w,h
  end

  #entities are solid by default
  def solid
    true
  end

  def self.sprite pkg, fn
    CoreUtils.string_hash 'packages/' + pkg + '/sprites/' + fn + '.png'
  end
  def sprite pkg,fn; Entity.sprite pkg,fn; end

  def self.wall pkg, fn
    CoreUtils.string_hash 'packages/' + pkg + '/walls/' + fn + '.png'
  end
  def wall pkg,fn; Entity.wall pkg,fn; end

  def self.wall_jpg pkg, fn
    CoreUtils.string_hash 'packages/' + pkg + '/walls/' + fn + '.jpg'
  end
  def wall_jpg pkg,fn; Entity.wall_jpg pkg,fn; end

  def distance_RL e2
    if @y > e2.y + e2.h
      return MAXNUM,MAXNUM
    end
    if @y + @h < e2.y
      return MAXNUM,MAXNUM
    end
    if @x < e2.x + e2.w
      r = e2.x - (@x + @w)
    else
      r = MAXNUM
    end
    if @x + @w > e2.x
      l = @x - (e2.x + e2.w)
    else
      l = MAXNUM
    end
    return r,l
  end

  def distance_DU e2
    if @x > e2.x + e2.w
      return MAXNUM,MAXNUM
    end
    if @x + @w < e2.x
      return MAXNUM,MAXNUM
    end
    if @y < e2.y + e2.h
      d = e2.y - (@y + @h)
    else
      d = MAXNUM
    end
    if @y + @h > e2.y
      u = @y - (e2.y + e2.h)
    else
      u = MAXNUM
    end
    return d,u
  end

end