module EntityMoving

  # the speed on each axis
  attr_accessor :em_sx, :em_sy

  def em_initialize
    @em_sx = @em_sy = 0
  end

  #returns true if entity is stuck
  def em_action
    ds,us,de,ue = $instance.space_DU self
    if ds<0 or us<0
      return true
    end
    rs,ls,re,le = $instance.space_RL self
    if rs<0 or ls<0
      return true
    end
    if @em_sx > 0
      if @em_sx < rs
        #no problem, we can go as fast
        @x += @em_sx
      else
        #bump!
        @x += rs - 1
        @em_sx = 0
      end
    end
    if @em_sx < 0
      if -@em_sx < ls
        @x += @em_sx
      else
        @x -= ls - 1
        @em_sx = 0
      end
    end
    #we need to calculate this again, because moving on the x axis might have changed the situation
    ds,us,de,ue = $instance.space_DU self
    if @em_sy > 0
      if @em_sy < ds
        @y += @em_sy
      else
        @y += ds - 1
        @em_sy = 0
      end
    end
    if @em_sy < 0
      if -@em_sy < us
        @y += @em_sy
      else
        @y -= us - 1
        @em_sy = 0
      end
    end
    return false
  end

end
