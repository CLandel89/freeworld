def debug str
  puts str
end

class Instance

  attr_accessor :players
  attr_accessor :option_manager, :chunk_manager
  attr_reader :entity_layer_list

  FPS = 35.0
  MAXNUM = (2**30 - 1)
  MINNUM = (- 2**30)

  def initialize
    @players = []
    @option_manager = OptionManager.new
    @chunk_manager = ChunkManager.new self
  end

  def main
    frame_time = 1.0 / FPS
    while !CoreUtils.finished
      @players.each do |p|
        chunk_manager.action self
        p.action self
        g = p.graphics
        #draw blue sky
        g.fill_rect_raw 0,0,g.res_w,g.res_h, 0,255,255
        #draw entities
        chunk_manager.each_entity proc {|e| g.draw e}
        #draw player
        g.draw p
        #draw UI
        p.gui.draw
        #that's all, folks!
        g.complete_frame
      end
      #TODO: implement constant frame rate
      CoreUtils.sleep frame_time
    end
    debug 'Finished main loop.'
  end

  def space_RL entity
    rs,ls = MAXNUM,MAXNUM
    re,le = nil,nil
    chunk_manager.each_entity proc { |e2|
      if e2.solid
        rd,ld = entity.distance_RL e2
        if rd < rs
          rs = rd
          re = e2
        end
        if ld < ls
          ls = ld
          le = e2
        end
      end
    }
    return rs,ls,re,le
  end

  def space_DU entity
    ds,us = MAXNUM,MAXNUM
    de,ue = nil,nil
    chunk_manager.each_entity proc { |e2|
      if e2.solid
        dd,ud = entity.distance_DU e2
        if dd < ds
          ds = dd
          de = e2
        end
        if ud < us
          us = ud
          ue = e2
        end
      end
    }
    return ds,us,de,ue
  end

end
