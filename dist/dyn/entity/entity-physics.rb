#Utilizes EntityMoving and provides
#semi-realistic movement according to force
#specified for Entity's using this module.
#The force (ep_fx,ep_fy) corresponds to the
#distance effectively passed over multiple frames.
#To get a certain speed, add the desired value to
#the force each frame, e.g.:
#self.ep_fx += @runspeed
module EntityPhysics

  #you can specify the force with which the speed is manipulated
  attr_accessor :ep_fx, :ep_fy

  #for module inter-dependencies, see:
  #https://stackoverflow.com/questions/4914913/how-do-i-include-a-module-into-another-module-refactor-aasm-code-and-custom-sta
  def self.included klass
    klass.class_eval do
      include EntityMoving
    end
  end

  def initialize x,y,z,w,h
    super
    @ep_fx = 0
    @ep_fy = 0
  end

  #returns true if entity is stuck
  def ep_action instance
    # apply force
    self.em_sx = (@ep_fx/4).to_i
    self.em_sy = (@ep_fy/4).to_i
    # reduce force
    @ep_fx -= self.em_sx
    @ep_fy -= self.em_sy
    # delegate to lower layer
    result = em_action instance
    # bump
    if @ep_fx > 0 && self.em_bumpr != nil
      @ep_fx = 0
    end
    if @ep_fx < 0 && self.em_bumpl != nil
      @ep_fx = 0
    end
    if @ep_fy > 0 && self.em_bumpd != nil
      @ep_fy  = 0
    end
    if @ep_fy < 0 && self.em_bumpu != nil
      @ep_fy  = 0
    end
    return result
  end

end
