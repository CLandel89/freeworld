class InstanceSp < Instance
  attr_reader :players
  def initialize
    super
    player = Player.new 0,0,0,100,200
    @players = [player]
  end
end

def start_instance_sp world
  InstanceSp.new
  Database.open_world world
  wp = 'std'
  wn = 'fence_grey_ugly'
  #w1-w3: U-shaped thin wall around the player
#  w1 = Wall.new_jpg(-50,-50,20,300, wp,wn)
#  w2 = Wall.new_jpg(-50,250,200,20, wp,wn)
#  w3 = Wall.new_jpg 130,-50,20,300, wp,wn
  #somewhat lower than that, some other blocks
#  w4 = Wall.new_jpg(-100,300,280,250, wp,wn)
  #horizontal gap of 20
#  w5 = Wall.new_jpg 200,200,1200,1200, wp,wn
#  puts "#{w1} #{w2} #{w3} #{w4} #{w5}"
#  $chunk_manager << w1 << w2 << w3 << w4 << w5
  #$chunk_manager << w5
#  $chunk_manager.load 0,0,0
  # Here be dragons!
  $instance.main
end