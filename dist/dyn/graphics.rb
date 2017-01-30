CoreUtils.add_enum 'Mi', 'enums/mi.enum'

class Graphics

  #the screen center coordinates, set by the player
  attr_accessor :cam_x, :cam_y

  attr_reader :res_w, :res_h

  def initialize
    @mi = ''
    @cam_x, @cam_y = 0, 0
    #this will be the testing res until
    #it is read from the world db
    set_resolution 3200, 1800
  end

  def set_bg_color r,g,b
    @mi += (encode_i32 Mi::BACKGROUND_COLOR)
      + (encode_u8 r) + (encode_u8 g) + (encode_u8 b)
  end
  def unset_bg_color
    @mi += encode_i32 Mi::UNSET_BACKGROUND_COLOR
  end

  #functions that generate media instructions (MI)

  def draw entity
    if entity.respond_to? :draw
      entity.draw self
      return
    end
    x,y,w,h = (x_to_screen entity.x), (y_to_screen entity.y), entity.w, entity.h
    wall_id = entity.wall_id
    if wall_id!=nil
      draw_wall_raw wall_id, x,y,w,h, entity.offset_x,entity.offset_y
    end
    sprite_id = entity.sprite_id
    if sprite_id!=nil
      draw_sprite_raw sprite_id, x, y, w, h
    end
  end

  #set the virtual resolution here and in the client or sp
  #implementation; higher res means smaller sprites
  def set_resolution w, h
    @res_w, @res_h = w, h
    @res_w_2, @res_h_2 = w/2, h/2
    @mi += (encode_i32 Mi::SET_RESOLUTION) +
      (encode_i32 w) + (encode_i32 h)
    parse_mi @mi
    @mi = ''
  end

  def complete_frame
    @mi += (encode_i32 Mi::FRAME_COMPLETED)
    parse_mi @mi
    @mi = ''
  end

  def fill_rect_raw x, y, w, h, r, g, b
    return if x+w<0 || y+h<0 || x>@res_w || y>@res_h
    @mi += (encode_i32 Mi::FILL_RECT) +
      (encode_i32 x) + (encode_i32 y) +
      (encode_i32 w) + (encode_i32 h) +
      (encode_u8 r) + (encode_u8 g) + (encode_u8 b)
  end

  def draw_sprite_raw sprite_id, x, y, w, h
    return if x+w<0 || y+h<0 || x>@res_w || y>@res_h
    @mi += (encode_i32 Mi::SPRITE)
    @mi += (encode_i32 sprite_id)
    @mi += (encode_i32 x)
    @mi += (encode_i32 y)
  end

  def draw_wall_raw wall_id, x, y, w, h, offset_x, offset_y
    return if x+w<0 || y+h<0 || x>@res_w || y>@res_h
    @mi += (encode_i32 Mi::WALL) +
      (encode_i32 wall_id) +
      (encode_i32 x) + (encode_i32 y) +
      (encode_i32 w) + (encode_i32 h) +
      (encode_i32 offset_x) + (encode_i32 offset_y)
  end

  #helper functions

  def x_to_screen x
    # determine relative world x coordinate
    result = x - @cam_x
    # result=0 at this point would mean the middle of the screen
    result += @res_w_2
    return result
  end

  def y_to_screen y
    y - @cam_y + @res_h_2
  end

  def encode_i32 num
    num = num.to_i
    result = '    '
    result[0] = (num & 0xff).chr
    result[1] = ((num >> 8) & 0xff).chr
    result[2] = ((num >> 16) & 0xff).chr
    result[3] = ((num >> 24) & 0xff).chr
    return result
  end

  def encode_u8 num
    return '' + (num & 0xff).chr
  end

end