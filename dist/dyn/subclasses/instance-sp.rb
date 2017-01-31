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
  wp = 'std'
  wn = 'nonexistent'
  w1 = Wall.new_jpg(-50,-50,20,300, wp,wn)
  w2 = Wall.new_jpg(-50,250,200,20, wp,wn)
  w3 = Wall.new_jpg(130,-50,20,300, wp,wn)
  $instance << w1 << w2 << w3
  # Here be dragons!
  $instance.main
end