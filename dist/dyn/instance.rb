class Instance

  attr_accessor :players
  attr_reader :entity_layer_list

  FPS = 35.0

  def initialize
    @players = []
#    @chunks = []
#    @entity_layer_list
    @entities = []
    #reference globally
    $instance = self
  end

  def main
    frame_time = 1.0 / FPS
    while true
      @players.each do |p|
        p.action
        g = p.graphics
        #draw blue sky
        g.fill_rect_raw 0,0,g.res_w,g.res_h, 0,255,255
        #draw entities
        each_entity proc {|e| g.draw e}
        #draw player
        g.draw p
        g.complete_frame
      end
      #TODO: implement constant frame rate
      CoreUtils.sleep frame_time
    end
  end

  def each_entity func
    @entities.each do |e|
      func.call e
    end
  end

  def << entity
    @entities << entity
    return self
  end

end