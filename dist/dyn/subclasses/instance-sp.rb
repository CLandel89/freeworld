class InstanceSp < Instance
  attr_reader :players
  def initialize
    super
    player = Player.new self
    @players = [player]
  end
end

def start_instance_sp save
  instance_sp = InstanceSp.new
  p = instance_sp.players[0]
  g = p.graphics
  #blue sky
  g.fill_rect_raw 0,0,g.res_w,g.res_h, 0,255,255
  #draw test sprite
  g.draw p
  #draw test walls
  #send to sp implementation
  g.complete_frame
  CoreUtils.sleep 2
end