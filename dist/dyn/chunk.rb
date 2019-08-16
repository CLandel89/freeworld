module BinUtils; end #empty definition to avoid NameError

class Chunk
  include BinUtils

  attr_accessor :x, :y, :z
  attr_accessor :entities

  def initialize x,y,z
    super()
    @entities = []
    @x,@y,@z = x,y,z
    @last_read = ''
    @last_read_index = 0
  end

  #incrementally create entities from a binary stream
  def read bin
    @last_read = @last_read[@last_read_index .. -1] + bin
    while @last_read.length - @last_read_index >= 24
      #ed: "entity data", a flexible chunk of binary data for every entity
      ed_l = decode_s32 @last_read, @last_read_index+20
      return if @last_read.length - @last_read_index < 24 + ed_l
      eti = decode_s32 @last_read, @last_read_index
      ex,ey,ew,eh =
        (decode_s32 @last_read, @last_read_index+4),
        (decode_s32 @last_read, @last_read_index+8),
        (decode_s32 @last_read, @last_read_index+12),
        (decode_s32 @last_read, @last_read_index+16)
      ed_ind = @last_read_index + 24
      ed = @last_read[ed_ind .. ed_ind+ed_l-1]
      @last_read_index += 24 + ed_l
      if @last_read_index == @last_read.length-1
        @last_read = ''
        @last_read_index = 0
      end
      entityClass = $entity_type_manager[eti]
      if entityClass==nil
        puts "Fatal error: #{eti} is not a known entity type identifier."
      end
      entity = entityClass.new ex,ey,@z,ew,eh, ed
      debug "created #{entity} at #{ex},#{ey},#{@z};#{ew},#{eh} #{ed.length}"
      @entities << entity
    end
  end

  def persist
    #WIP
  end

  def << entity
    @entities << entity
  end
  def delete entity
    @entities.delete entity
  end

  #check if the chunk has an intersection with the
  #given rectangle and is in "z"
  def in? instance, x1,y1,x2,y2,z
    return false if @z!=z
    csize = instance.option_manager['chunk size'].to_i
    if @x+csize>=x1  and
        @x<=x2       and
        @y+csize>=y1 and
        @y<=y2
      return true
    else
      return false
    end
  end

  #when a chunk gets out of scope the program is terminated
  #and it needs to persist in the db
  def persist
  end
end