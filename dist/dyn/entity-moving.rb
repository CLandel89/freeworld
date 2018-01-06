#Lets you specify a speed for an Entity and
#handles movement according to the specified
#speed and collision with surrounding Entitys.
module EntityMoving

  # the speed on each axis
  attr_accessor :em_sx, :em_sy
  # has the entity bumped into an object?
  attr_accessor :em_bumpl, :em_bumpr, :em_bumpu, :em_bumpd

  def em_initialize
    #the speed
    @em_sx = @em_sy = 0
    @em_bumpl = @em_bumpr = @em_bumpu = @em_bumpd = nil
  end

  #returns true if entity is stuck
  def em_action
    @em_bumpl = @em_bumpr = @em_bumpu = @em_bumpd = nil
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
        @x += @em_sx
      else
        @x += rs - 1
        @em_sx = 0
        @em_bumpr = re
      end
    end
    if @em_sx < 0
      if -@em_sx < ls
        @x += @em_sx
      else
        @x -= ls - 1
        @em_sx = 0
        @em_bumpl = le
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
        @em_bumpd = de
      end
    end
    if @em_sy < 0
      if -@em_sy < us
        @y += @em_sy
      else
        @y -= us - 1
        @em_sy = 0
        @em_bumpu = ue
      end
    end
    return false
  end

end
