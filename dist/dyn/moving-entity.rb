module MovingEntity

  # the speed on each axis
  attr_accessor :me_sx, :me_sy

  def me_initialize
    @me_sx = @me_sy = 0
  end

  #returns true if entity is stuck
  def me_action
    ds,us,de,ue = $instance.space_DU self
    if ds<0 or us<0
      return true
    end
    rs,ls,re,le = $instance.space_RL self
    if rs<0 or ls<0
      return true
    end
    if @me_sx > 0
      if @me_sx < rs
        #no problem, we can go as fast
        @x += @me_sx
      else
        #bump!
        @x += rs - 1
        @me_sx = 0
      end
    end
    if @me_sx < 0
      if -@me_sx < ls
        @x += @me_sx
      else
        @x -= ls - 1
        @me_sx = 0
      end
    end
    #we need to calculate this again, because moving on the x axis might have changed the situation
    ds,us,de,ue = $instance.space_DU self
    if @me_sy > 0
      if @me_sy < ds
        @y += @me_sy
      else
        @y += ds - 1
        @me_sy = 0
      end
    end
    if @me_sy < 0
      if -@me_sy < us
        @y += @me_sy
      else
        @y -= us - 1
        @me_sy = 0
      end
    end
    return false
  end

end