class Instance

  attr_accessor :players
  attr_reader :entity_layer_list

  def initialize
    @players = []
    @chunks = []
    @entity_layer_list
    #reference globally
    $instance = self
  end

  def action
#    @players.each do |p|
#      p.action
#    end
  end

  def foreach_entity func
  end

end