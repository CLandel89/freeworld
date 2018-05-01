class ChunkManager
  attr_accessor :chunks

  def initialize instance
    option_manager = instance.option_manager
    @chunks = []
    # chunk distances:
    #Whenever there are chunks missing in the
    #"chunk min distance", all chunks in the
    #"chunk load distance" are ensured loaded.
    #When a chunk is outside the "chunk max distance"
    #of every player, it is unloaded.
    @min_d = option_manager['chunk min distance'].to_i
    @load_d = option_manager['chunk load distance'].to_i
    @max_d = option_manager['chunk max distance'].to_i
    @csize = option_manager['chunk size'].to_i
  end

  def action instance
    @chunks.each do |chunk|
      in_max_d = false
      instance.players.each do |player|
        z = player.z
        x1 = player.x - @max_d
        y1 = player.y - @max_d
        x2 = player.x + player.w + @max_d
        y2 = player.y + player.h + @max_d
        if chunk.in? instance, x1,y1,x2,y2,z
          in_max_d = true
          break
        end
      end
      if ! in_max_d
        chunk.persist
        @chunks.delete chunks
      end
    end
    players_load_d = []
    instance.players.each do |player|
      start_x = x = c_coor(player.x - @min_d)
      end_x = c_coor(x + 2*@min_d + @csize)
      y = c_coor(player.y - @min_d)
      end_y = c_coor(y + 2*@min_d + @csize)
      z = player.z
      found = false
      while y<=end_y
        @chunks.each do |c|
          if c.x==x and c.y==y and c.z==z
            found = true
            break
          end
        end
        if ! found
          #the space of @min_d around the player is not
          #filled with chunks => marking player; continue
          #the check with the next player
          players_load_d << player
          break #while-loop => end of players' each-do-loop
        end
        x += @csize
        if x>end_x
          y += @csize
          x = start_x
        end
      end
    end
    #the space of @load_d around the marked players is now
    #loaded
    players_load_d.each do |player|
      start_x = x = c_coor(player.x - @load_d)
      end_x = c_coor(x + 2*@load_d + @csize)
      y = c_coor(player.y - @load_d)
      end_y = c_coor(y + 2*@load_d + @csize)
      z = player.z
      while y<=end_y
        load x,y,z
        x += @csize
        if x>end_x
          y += @csize
          x = start_x
        end
      end
    end
  end

  #determine a coordinate (x,y) of the chunk of
  #an entity in the chunk; e.g. to be used like this:
  #chunk_x = c_coor(entity.x)
  def c_coor coor
    coor - (coor % @csize)
  end

  def load x,y,z
    #check if that chunk isn't already loaded
    @chunks.each do |c|
      return if c.x==x and c.y==y and c.z==z
    end
    debug "loading chunk at #{x},#{y},#{z}"
    chunk = Chunk.new x,y,z
    Database.open_chunk x,y,z
    begin
      bin = Database.read_chunk
      chunk.read bin
    end while bin!=''
    @chunks << chunk
    debug "done loading chunk"
  end

  #find the chunk for this entity, and add the
  #entity to the chunk
  def << entity
    cx = c_coor entity.x
    cy = c_coor entity.y
    cz = entity.z
    debug "arranging #{entity} at #{entity.x},#{entity.y},#{entity.z} to chunk at #{cx},#{cy},#{cz}"
    @chunks.each do |c|
      if cz==c.z and cx==c.x and cy==c.y
        c << entity
        debug "done arranging entity"
        return self
      end
    end
    #not returned => chunk is not currently initialized
    load cx,cy,cz
    return self << entity
  end

  def each_entity func
    @chunks.each do |chunk|
      chunk.entities.each do |e|
        func.call e
      end
    end
  end
end