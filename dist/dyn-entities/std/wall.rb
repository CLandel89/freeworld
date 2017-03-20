class Wall < Entity
  include BinUtils
  attr_accessor :offset_x, :offset_y

  def initialize x,y,z,w,h, ed
    super x,y,z,w,h
    if ed.length != 12
      puts "Fatal error: Entity data length for Wall != 12."
    end
    @offset_x = decode_s32 ed,0
    @offset_y = decode_s32 ed,4
    @wall_id = decode_s32 ed,8
  end

  def self.type_id
    CoreUtils.string_hash 'Wall'
  end

end

$entity_type_manager << Wall