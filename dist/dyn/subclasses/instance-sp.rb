class InstanceSp < Instance
  attr_reader :players
  def initialize
    super
    player = Player.new 0,0,100,200
    @players = [player]
  end
end

def start_instance_sp save
  InstanceSp.new
  p = $instance.players[0]
  g = p.graphics
  #blue sky
  g.fill_rect_raw 0,0,g.res_w,g.res_h, 0,255,255
  #draw test sprite
  g.draw p
  #draw test walls
  wp = 'std'
  wn = 'nonexistent'
  w1 = Wall.new_jpg(-50,-50,20,300, wp,wn)
  w2 = Wall.new_jpg(-50,250,200,20, wp,wn)
  w3 = Wall.new_jpg(130,-50,20,300, wp,wn)
  g.draw w1; g.draw w2; g.draw w3
  #send to sp implementation
  g.complete_frame
  CoreUtils.sleep 2
end