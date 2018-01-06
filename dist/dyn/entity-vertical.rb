#Utilizes EntityPhysics and EntityMoving
#to provide "jump'n'run like" dynamics, with
#Entitys using this module falling down
#along the vertical axis of the screen.
#Requires an accessible @control object.
module EntityVertical

  #the speed with which the entity falls at free fall
  attr_accessor :ev_fallspeed, :ev_runspeed
  attr_accessor :ev_jumpheight

  #for module inter-dependencies, see:
  #https://stackoverflow.com/questions/4914913/how-do-i-include-a-module-into-another-module-refactor-aasm-code-and-custom-sta
  def self.included klass
    klass.class_eval do
      include EntityPhysics
    end
  end

  def ev_initialize
    ep_initialize
    @ev_fallspeed = 100
    @ev_runspeed = 50
    @ev_jumpheight = 500
    @jumpheight_remaining = 0
    @jumped = false
  end

  #returns true if entity is stuck
  def ev_action
	# on ground or mid-air?
    ds,us,de,ue = $instance.space_DU self
    if ds<=2
      # on ground
      if self.control.b[CiButton::JUMP] && !@jumped
        # start a jump
        @jumped = true
        @jumpheight_remaining = @ev_jumpheight
	  end
    else
      # mid-air
      #fall
	  self.ep_fy += @ev_fallspeed
	end
    # other jump stuff
	if @jumpheight_remaining>0
	  # perfom one frame of a jump
      #determine force for one frame
	  jh_p = (@jumpheight_remaining/4).ceil.to_i
	  #provide force to EntityPhysics module, cancel the fall
	  self.ep_fy -= jh_p + @ev_fallspeed
	  @jumpheight_remaining -= jh_p
	end
	#cancel jump (on button release)
	if !self.control.b[CiButton::JUMP]
	  @jumpheight_remaining = 0
	  @jumped = false
	end
    # run/fly
    self.ep_fx += @ev_runspeed * self.control.x
    result = ep_action
    return result
  end

end
