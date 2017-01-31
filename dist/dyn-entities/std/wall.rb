class Wall < PersistentEntity
  attr_accessor :offset_x, :offset_y

  def initialize x,y,w,h, pkg,name
    super x,y,w,h
    @wall_id = wall pkg,name
    @offset_x,@offset_y = 0,0
  end

  def initialize x,y,w,h
    super x,y,w,h
    @offset_x,@offset_y = 0,0
  end

  def self.new_jpg x,y,w,h, pkg,name
    result = Wall.new x,y,w,h
    result.wall_id = wall_jpg pkg,name
    return result
  end

end